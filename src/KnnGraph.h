#ifndef KNNGRAPHLOADER_H
#define KNNGRAPHLOADER_H

#include <vector>

#include "GraphMatrixLoader.h"
#include "SimilarityMatrixLoader.h"

// class and comparison function for max_heap in order
// to find k nearest neighbors
class IndexValue {
public:
    IndexValue(){}
    IndexValue(int i, float64_t d): index(i), distance(d){}
    size_t index;
    float64_t distance;
};

class KnnGraph : public GraphMatrixLoader {
public:
    KnnGraph(size_t kn, bool w = true, bool m = true, SimilarityMatrixLoader* sim = NULL):
        knn(kn), weighted(w), mutual(m), sim_loader(sim){}
    ~KnnGraph();
    void LoadGraphMatrix(shogun::SGMatrix<float64_t>& graph_matrix,
                                              shogun::SGMatrix<float64_t>& feature_matrix);
    void AddSimilarityMatrixLoader(SimilarityMatrixLoader *sim);

private:
    size_t knn;
    bool weighted;
    bool mutual;
    SimilarityMatrixLoader* sim_loader;
    void HandleKneighbors(std::vector<IndexValue>& k_neighbors, IndexValue& neighbor);
    void AddMatrixNeighbors(shogun::SGMatrix<float64_t>& graph_matrix,
                            std::vector<IndexValue>& k_neighbors, size_t m_index);
};

#endif // KNNGRAPHLOADER_H
