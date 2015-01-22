#ifndef EIGENSOLVER_H
#define EIGENSOLVER_H

#include <shogun/lib/SGMatrix.h>

class EigenSolver{
public:
    shogun::SGMatrix<double> GetTopKEigenvectorsMatrix(shogun::SGMatrix<float64_t>& graph_matrix,
                                                   int min_k, int max_k);
private:
    // find the top k eigenvectors to be passed in kmeans for clustering
    int GetBestK(shogun::SGVector<float64_t>& eigenvalues,
                 int min_k, int max_k);
};


#endif // EIGENSOLVER_H
