#ifndef ENEIGHBORHOODGRAPH_H
#define ENEIGHBORHOODGRAPH_H


#include <vector>

#include "GraphMatrixLoader.h"
#include "SimilarityMatrixLoader.h"

class ENeighborhoodGraph : public GraphMatrixLoader {
public:
    ENeighborhoodGraph(float64_t e, bool w = false, SimilarityMatrixLoader* sim = NULL):
        epsilon(e), weighted(w), sim_loader(sim){}
    ~ENeighborhoodGraph();
    void LoadGraphMatrix(shogun::SGMatrix<float64_t>& graph_matrix,
                                              shogun::SGMatrix<float64_t>& feature_matrix);
    void AddSimilarityMatrixLoader(SimilarityMatrixLoader *sim);

private:
    float64_t epsilon;
    bool weighted;
    SimilarityMatrixLoader* sim_loader;
};

#endif // ENEIGHBORHOODGRAPH_H
