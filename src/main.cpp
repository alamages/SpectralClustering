/* Copyright 2014: Emmanouil Kiagias <e.kiagias@gmail.com>
 * License: GPLv3
 */
#include <shogun/base/init.h>
#include <math.h>
#include <ctime>
#include "Graph.h"
#include "SpectralClustering.h"
#include "FullyConnectedGraph.h"
#include "EuclideanDistanceMatrix.h"
#include "KnnGraph.h"
#include <iostream>
#include <string>

void PrintClusters(const std::vector<int> cls) {
    for (size_t i = 0; i < cls.size(); i++) {
        std::cout << i+1 << " " << cls[i] << std::endl;
    }
}

int main() {
    shogun::init_shogun_with_defaults();

    // assuming you build inside a build folder in the
    // project's root directory
    std::string graphfile = "../data/graph";

    // first initialize the similarity matrix class
    // only eucliadian similarity is implemented
    // for the moment. no need to delete that graph_loader
    // will delete it once it owns it.
    EuclideanDistanceMatrix* euclidean_sim_matrix =
            new EuclideanDistanceMatrix();

    // afterwards we initialize the graph type we want
    // no need to delete that, spectral clustering
    // will delete it once it owns this object
    // Fully connected graph:
    int sigma = 5;
    FullyConnectedGraph* graph_loader = new FullyConnectedGraph(sigma);

    // other possible graph_loader could be:
    // KNN graph
    // int kn = 10;  // kn -> k nearest neighbors
    // KnnGraph* graph_loader = new KnnGraph(kn);

    // then we add to the graph_loader the similarity matrix object
    graph_loader->AddSimilarityMatrixLoader(euclidean_sim_matrix);

    SpectralClustering* cl = new SpectralClustering();
    // we add the graph load object
    // it is needed for vectors/features clustering
    cl->AddGraphMatrixLoader(graph_loader);

    // provide the vectors file (in libsvm format) to be clustered
    // std::vector<int> cls_feat =
    //        cl->ClusterFeatures("../data/features_libsvm");


    // in the case of an undirected and no weighted graph
    // just call the ClusterGraph method (no need for similarity
    // and graph objects
    std::vector<int> cls_gr = cl->ClusterGraph(graphfile);
    PrintClusters(cls_gr);

    shogun::exit_shogun();
    /* clean up */
    delete cl;

    return 0;
}

