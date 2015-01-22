#include "SpectralClustering.h"
#include "EigenSolver.h"

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <shogun/clustering/KMeans.h>
#include <shogun/distance/EuclideanDistance.h>


SpectralClustering::~SpectralClustering(){
    if(graph_loader){
        delete graph_loader;
    }
}

void SpectralClustering::AddGraphMatrixLoader(GraphMatrixLoader *g_loader){
    graph_loader = g_loader;
}

void SpectralClustering::LoadGraphFile(std::string filename){
    graph.Load(filename);
}

void SpectralClustering::LoadFromSvmLibFormat(const char * file_name,
    shogun::SGMatrix<float64_t> &feats_matrix,
    int32_t &dim_feat, int32_t &num_samples){

    shogun::CLibSVMFile * file = new shogun::CLibSVMFile(file_name);
    //ASSERT(file != NULL);
    SG_REF(file);

    shogun::SGSparseVector<float64_t> * feats;
    file->get_sparse_matrix(feats, dim_feat, num_samples);
    feats_matrix = shogun::SGMatrix<float64_t>(dim_feat, num_samples);

    /** preparation of data for multilabel model */
    for (index_t i = 0; i < num_samples; i++)
    {
        shogun::SGSparseVector<float64_t> feat_sample = feats[i];

        for (index_t j = 0; j < dim_feat; j++){
            feats_matrix[i * dim_feat + j] = feat_sample.get_feature(j);
        }
    }

    SG_UNREF(file);
    SG_FREE(feats);
}

void SpectralClustering::LoadUnnormalizedLaplacian(shogun::SGMatrix<float64_t> &graph_matrix){
    /* now build the Degree matrix, D */
    size_t num_rows = graph_matrix.num_rows;
    float64_t* rows_sum = shogun::SGMatrix<float64_t>::get_row_sum(graph_matrix.matrix, num_rows, num_rows);
    shogun::SGMatrix<float64_t> degree_matrix(num_rows, num_rows);
    shogun::SGMatrix<float64_t>::create_diagonal_matrix(degree_matrix.matrix, rows_sum, num_rows);

    /* build the laplacian, L */
    /* subtract the matrixes, L = D - W */
    for (size_t i = 0; i < num_rows; i++){
        for (size_t j = 0; j < num_rows; j++){
            graph_matrix(i,j) = degree_matrix(i, j) - graph_matrix(i, j);
        }
    }

    delete[] rows_sum;
}

shogun::SGMatrix<float64_t> SpectralClustering::GetStandardMatrix(Graph &grapht){
    int nsize = grapht.GetSize();
    std::map<int, std::vector<int>>& graphmap = *(grapht.GetGraph());
    shogun::SGMatrix<float64_t> graph_matrix(nsize, nsize);

    int i_sum, j_sum, node_i;
    for (auto& iter : graphmap){
        node_i = iter.first;
        i_sum = iter.second.size();

        for (auto& node_j : iter.second){
            j_sum = graphmap[node_j].size();
            graph_matrix(node_i-1, node_j-1) = static_cast<float64_t>(1.0/(sqrt(i_sum)*sqrt(j_sum)));
        }
    }

    return graph_matrix;
}


// stand-alone version of Spectral Clustering
void SpectralClustering::GraphCluster(){
    shogun::SGMatrix<float64_t> graph_matrix = GetStandardMatrix(graph);

    shogun::CMulticlassLabels* result = ClusterGraph(graph_matrix);
    for (int i=0; i<result->get_num_labels(); ++i)
        std::cout << i+1 << "\t" << result->get_label(i) << std::endl;

    // clean up
    SG_UNREF(result);
}

// dirty but simple and straight-forward. TODO refactor all the code
void SpectralClustering::ClusterFeatures(std::string libsvmfile){
    if(!graph_loader){
        std::cerr << "No graph loader was defined! Aborting..." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    shogun::SGMatrix<float64_t> feats_matrix;
    int32_t dim_feat;
    int32_t num_samples;

    LoadFromSvmLibFormat(libsvmfile.c_str(),feats_matrix,dim_feat,num_samples);
    shogun::SGMatrix<float64_t> graph_matrix;

    //load either fully connected graph  or knn graph
    graph_loader->LoadGraphMatrix(graph_matrix, feats_matrix);

    //then override graph_matrix with the unnormalized laplacian
    LoadUnnormalizedLaplacian(graph_matrix);

    shogun::CMulticlassLabels* result = ClusterGraph(graph_matrix);
    for (int i=0; i<result->get_num_labels(); ++i)
        std::cout << i+1 << "\t" << result->get_label(i) << std::endl;

    // clean up
    SG_UNREF(result);
}

// ATTENTION SG_UNREF the return result object
// clustering on the given graph_matrix
shogun::CMulticlassLabels* SpectralClustering::ClusterGraph(shogun::SGMatrix<float64_t>& graph_matrix){
    EigenSolver solver;
    shogun::SGMatrix<float64_t> k_eigenvectors = solver.GetTopKEigenvectorsMatrix(graph_matrix, -1, std::min(100, (graph_matrix.num_rows-1)/4));
    int num_clusters = k_eigenvectors.num_rows;
    shogun::CDenseFeatures<float64_t>* features=new shogun::CDenseFeatures<float64_t>();
    features->set_feature_matrix(k_eigenvectors);
    SG_REF(features);

    /* create distance */
    shogun::CEuclideanDistance* distance = new shogun::CEuclideanDistance(features, features);

    /* create distance machine */
    shogun::CKMeans* clustering = new shogun::CKMeans(num_clusters, distance);
    clustering->train(features);

    /* build clusters */
    shogun::CMulticlassLabels* result = shogun::CLabelsFactory::to_multiclass(clustering->apply());

    // #TODO, clean up
    SG_UNREF(clustering);
    SG_UNREF(features);

    return result;
}
