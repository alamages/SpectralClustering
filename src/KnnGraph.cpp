#include "KnnGraph.h"
#include <iostream>
#include <algorithm>

struct LessIndexValue{
  bool operator()(const IndexValue& a,const IndexValue& b) const{
    return a.distance < b.distance;
  }
};

KnnGraph::~KnnGraph(){
    if(sim_loader){
        delete sim_loader;
    }
}

void KnnGraph::AddSimilarityMatrixLoader(SimilarityMatrixLoader *sim){
    sim_loader = sim;
}

void KnnGraph::HandleKneighbors(std::vector<IndexValue>& k_neighbors, IndexValue& neighbor){
    // if vector is full
    if(k_neighbors.size() >= knn){

        // max heap the front element is the current max
        if (neighbor.distance < k_neighbors.front().distance){
            // remove the current max
            std::pop_heap(k_neighbors.begin(), k_neighbors.end(), LessIndexValue());
            k_neighbors.pop_back();

            // then add the new neighbor
            k_neighbors.push_back(neighbor);
            std::push_heap(k_neighbors.begin(), k_neighbors.end(), LessIndexValue());

        }
    }
    else{
        k_neighbors.push_back(neighbor);

        if(k_neighbors.size() == knn){
            //initialize the max heap
            std::make_heap(k_neighbors.begin(),k_neighbors.end(), LessIndexValue());
        }
    }
}

void KnnGraph::AddMatrixNeighbors(shogun::SGMatrix<float64_t>& graph_matrix,
                                  std::vector<IndexValue>& k_neighbors, size_t m_index){
    for(size_t i = 0; i < k_neighbors.size(); i++){
        float64_t edge = k_neighbors[i].distance;

        if(!weighted)  edge = 1;

        graph_matrix(m_index, k_neighbors[i].index) = edge;
        if(mutual)
            graph_matrix(k_neighbors[i].index, m_index) = edge;
    }
}

void KnnGraph::LoadGraphMatrix(shogun::SGMatrix<float64_t> &graph_matrix,
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
        std::vector<IndexValue> k_neighbors;

        for(size_t j = 0; j < num_rows; j++){
            if (i == j) continue;

            IndexValue current_neighbor(j, distance_matrix(i, j));
            HandleKneighbors(k_neighbors, current_neighbor);
        }

        AddMatrixNeighbors(graph_matrix, k_neighbors, i);
    }
}
