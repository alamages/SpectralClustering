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

int main() {
    shogun::init_shogun_with_defaults();

    std::string graphfile = "graph";
    // no need to delete that, graph matrix loader
    // will delete it once it owns this object
    EuclideanDistanceMatrix* euclidean_sim_matrix =
            new EuclideanDistanceMatrix();

    // Fully connected graph
    int sigma = 5;
    // no need to delete that, spectral clustering
    // will delete it once it owns this object
    FullyConnectedGraph* graph_loader = new FullyConnectedGraph(sigma);


    // KNN graph
    // int kn = atoi(conf["kn"].c_str());
    // KnnGraph* graph_loader = new KnnGraph(kn);

    graph_loader->AddSimilarityMatrixLoader(euclidean_sim_matrix);

    SpectralClustering* cl = new SpectralClustering();
    cl->AddGraphMatrixLoader(graph_loader);
    //cl->ClusterFeatures(graphfile);
    cl->ClusterGraph(graphfile);

    shogun::exit_shogun();

    /* clean up */
    delete cl;

    return 0;
}

