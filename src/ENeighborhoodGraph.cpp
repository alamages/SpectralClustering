#include "ENeighborhoodGraph.h"
#include <iostream>

ENeighborhoodGraph::~ENeighborhoodGraph(){
    if(sim_loader){
        delete sim_loader;
    }
}

void ENeighborhoodGraph::AddSimilarityMatrixLoader(SimilarityMatrixLoader *sim){
    sim_loader = sim;
}

void ENeighborhoodGraph::LoadGraphMatrix(shogun::SGMatrix<float64_t> &graph_matrix,
                                          shogun::SGMatrix<float64_t> &feature_matrix){

    if(!sim_loader){
        std::cerr << "No similarity matrix loader was defined! Aborting..." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    shogun::SGMatrix<float64_t> distance_matrix;

    /* load the similarity/distance matrix */
    sim_loader->LoadSimilarityMatrix(distance_matrix, feature_matrix);

    /* build fully connected graph, W matrix */
    size_t num_rows = distance_matrix.num_rows;
    graph_matrix = shogun::SGMatrix<float64_t>(num_rows, num_rows);

    for(size_t i = 0; i < num_rows; i++){
        for(size_t j = 0; j < num_rows; j++){
            float64_t edge = distance_matrix(i, j);
            if(edge <= epsilon){
                if(!weighted) edge = 1;

                graph_matrix(i, j) = edge;
            }
        }
    }
}

