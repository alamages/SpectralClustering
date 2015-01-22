/* Copyright 2014: Emmanouil Kiagias <e.kiagias@gmail.com>
 * License: GPLv3
 */
#ifndef SRC_FULLYCONNECTEDGRAPH_H_
#define SRC_FULLYCONNECTEDGRAPH_H_

#include "GraphMatrixLoader.h"
#include "SimilarityMatrixLoader.h"

class FullyConnectedGraph : public GraphMatrixLoader {
 public:
    explicit FullyConnectedGraph(int s, SimilarityMatrixLoader* sim = NULL):
        sigma(s), sim_loader(sim) {}
    ~FullyConnectedGraph();
    void LoadGraphMatrix(shogun::SGMatrix<float64_t> &graph_matrix,
                         shogun::SGMatrix<float64_t> &feature_matrix);
    void AddSimilarityMatrixLoader(SimilarityMatrixLoader* sim);
 private:
    int sigma;
    SimilarityMatrixLoader* sim_loader;
};

#endif  // SRC_FULLYCONNECTEDGRAPH_H_
