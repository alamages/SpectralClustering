#ifndef EUCLIDEANDISTANCEMATRIX_H
#define EUCLIDEANDISTANCEMATRIX_H

#include "SimilarityMatrixLoader.h"

class EuclideanDistanceMatrix : public SimilarityMatrixLoader {
public:
    explicit EuclideanDistanceMatrix(bool n = true): normalize(n){}
    ~EuclideanDistanceMatrix(){}
    void LoadSimilarityMatrix(shogun::SGMatrix<float64_t>& distance_matrix,
                                          shogun::SGMatrix<float64_t>& feature_matrix);
private:
    bool normalize;
};

#endif // EUCLIDEANDISTANCEMATRIX_H
