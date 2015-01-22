#ifndef FULLYCONNECTEDGRAPH_H
#define FULLYCONNECTEDGRAPH_H

#include "GraphMatrixLoader.h"
#include "SimilarityMatrixLoader.h"

class FullyConnectedGraph : public GraphMatrixLoader {
public:
    // s = sigma
    FullyConnectedGraph(int s, SimilarityMatrixLoader* sim = NULL): sigma(s), sim_loader(sim){}
    ~FullyConnectedGraph();
    void LoadGraphMatrix(shogun::SGMatrix<float64_t> &graph_matrix,
                           shogun::SGMatrix<float64_t> &feature_matrix);
    void AddSimilarityMatrixLoader(SimilarityMatrixLoader* sim);
private:
    int sigma;
    SimilarityMatrixLoader* sim_loader;
};

#endif // FULLYCONNECTEDGRAPH_H
