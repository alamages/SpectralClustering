/* Copyright 2014: Emmanouil Kiagias <e.kiagias@gmail.com>
 * License: GPLv3
 */
#ifndef SRC_SIMILARITYMATRIXLOADER_H_
#define SRC_SIMILARITYMATRIXLOADER_H_

#include <shogun/lib/SGMatrix.h>

class SimilarityMatrixLoader {
 public:
    SimilarityMatrixLoader() {}
    virtual ~SimilarityMatrixLoader() {}
    virtual void LoadSimilarityMatrix(
            shogun::SGMatrix<float64_t>& distance_matrix,
            shogun::SGMatrix<float64_t>& feature_matrix) = 0;
};

#endif  // SRC_SIMILARITYMATRIXLOADER_H_
