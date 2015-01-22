#ifndef SPECTRALCLUSTERING_H
#define SPECTRALCLUSTERING_H

#include "Graph.h"
#include "GraphMatrixLoader.h"

#include <shogun/lib/SGMatrix.h>
#include <shogun/clustering/KMeans.h>

class SpectralClustering {
public:
    explicit SpectralClustering(GraphMatrixLoader* g_loader = NULL) : graph_loader(g_loader){}
    ~SpectralClustering();
    // load the graph file
    void LoadGraphFile(std::string filename);
    void GraphCluster();
    void ClusterFeatures(std::string libsvmfile);
    shogun::CMulticlassLabels* ClusterGraph(shogun::SGMatrix<float64_t>& graph_matrix);
    void AddGraphMatrixLoader(GraphMatrixLoader* g_loader);
private:
    Graph graph;
    GraphMatrixLoader* graph_loader;
    // this prepares the matrix for the stand-alone version
    shogun::SGMatrix<float64_t> GetStandardMatrix(Graph& grapht);
    void LoadFromSvmLibFormat(const char * file_name,
        shogun::SGMatrix<float64_t> &feats_matrix,
        int32_t &dim_feat, int32_t &num_samples);
    void LoadUnnormalizedLaplacian(shogun::SGMatrix<float64_t> &graph_matrix);

};

#endif // SPECTRALCLUSTERING_H
