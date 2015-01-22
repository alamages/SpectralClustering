/* Copyright 2014: Emmanouil Kiagias <e.kiagias@gmail.com>
 * License: GPLv3
 */
#include "FullyConnectedGraph.h"
#include <iostream>

void FullyConnectedGraph::AddSimilarityMatrixLoader(
        SimilarityMatrixLoader *sim) {
    sim_loader = sim;
}

FullyConnectedGraph::~FullyConnectedGraph() {
    if (sim_loader) {
        delete sim_loader;
    }
}

void FullyConnectedGraph::LoadGraphMatrix(
        shogun::SGMatrix<float64_t> &graph_matrix,
        shogun::SGMatrix<float64_t> &feature_matrix) {
    if (!sim_loader) {
        std::cerr << "No similarity matrix loader was defined! Aborting..."
                  << std::endl;
        std::exit(EXIT_FAILURE);
    }

    shogun::SGMatrix<float64_t> distance_matrix;

    /* load the similarity/distance matrix */
    sim_loader->LoadSimilarityMatrix(distance_matrix, feature_matrix);

    /* build fully connected graph, W matrix */
    size_t num_rows = distance_matrix.num_rows;
    graph_matrix = shogun::SGMatrix<float64_t>(num_rows, num_rows);

    for (size_t i = 0; i < num_rows; i++) {
        for (size_t j = 0; j < num_rows; j++) {
            float64_t value_temp =
                    exp((-pow(distance_matrix(i, j), 2))/(2*pow(sigma, 2)));
            if (value_temp < 0)
                continue;

            graph_matrix(i, j) = value_temp;
        }
    }
}
