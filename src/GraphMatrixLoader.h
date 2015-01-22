/* Copyright 2014: Emmanouil Kiagias <e.kiagias@gmail.com>
 * License: GPLv3
 */
#ifndef SRC_GRAPHMATRIXLOADER_H_
#define SRC_GRAPHMATRIXLOADER_H_

#include <shogun/lib/SGMatrix.h>

class GraphMatrixLoader {
 public:
    GraphMatrixLoader() {}
    virtual ~GraphMatrixLoader() {}
    virtual void LoadGraphMatrix(
            shogun::SGMatrix<float64_t> &graph_matrix,
            shogun::SGMatrix<float64_t> &feature_matrix) = 0;
};

#endif  // SRC_GRAPHMATRIXLOADER_H_
