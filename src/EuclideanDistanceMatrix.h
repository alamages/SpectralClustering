/* Copyright 2014: Emmanouil Kiagias <e.kiagias@gmail.com>
 * License: GPLv3
 */
#ifndef SRC_EUCLIDEANDISTANCEMATRIX_H_
#define SRC_EUCLIDEANDISTANCEMATRIX_H_

#include "SimilarityMatrixLoader.h"

class EuclideanDistanceMatrix : public SimilarityMatrixLoader {
 public:
    explicit EuclideanDistanceMatrix(bool n = true): normalize(n) {}
    ~EuclideanDistanceMatrix() {}
    void LoadSimilarityMatrix(shogun::SGMatrix<float64_t>& distance_matrix,
                              shogun::SGMatrix<float64_t>& feature_matrix);
 private:
    bool normalize;
};

#endif  // SRC_EUCLIDEANDISTANCEMATRIX_H_
