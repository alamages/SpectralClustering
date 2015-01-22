#ifndef GRAPHMATRIXLOADER_H
#define GRAPHMATRIXLOADER_H

#include <shogun/lib/SGMatrix.h>

class GraphMatrixLoader {
public:
    GraphMatrixLoader(){}
    virtual ~GraphMatrixLoader(){}
    virtual void LoadGraphMatrix(shogun::SGMatrix<float64_t> &graph_matrix,
                                  shogun::SGMatrix<float64_t> &feature_matrix) = 0;
};

#endif // GRAPHMATRIXLOADER_H
