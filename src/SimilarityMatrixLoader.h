#ifndef SIMILARITYMATRIXLOADER_H
#define SIMILARITYMATRIXLOADER_H

#include <shogun/lib/SGMatrix.h>

class SimilarityMatrixLoader {
public:
    SimilarityMatrixLoader(){}
    virtual ~SimilarityMatrixLoader(){}
    virtual void LoadSimilarityMatrix(shogun::SGMatrix<float64_t>& distance_matrix,
                                      shogun::SGMatrix<float64_t>& feature_matrix) = 0;
};

#endif // SIMILARITYMATRIXLOADER_H
