/* Copyright 2014: Emmanouil Kiagias <e.kiagias@gmail.com>
 * License: GPLv3
 */
#include "EigenSolver.h"
#include <shogun/lib/SGVector.h>
#include <limits>
#include <iostream>


// #TODO write cleaner
// actually selects the k with the biggest eigengap
int EigenSolver::GetBestK(shogun::SGVector<float64_t>& eigenvalues,
                          int min_k, int max_k) {
    float64_t avg, i_diff, rel_i_diff, sum = 0;
    int max_k_selected = 1;
    int end_index = eigenvalues.size() - 1;

    // set the initial max value to the lower double possible value
    float64_t max_diff = std::numeric_limits<float64_t>::min();

    // careful max_k input can not be > n size of eigenvalues
    for (int i = 0; i < max_k; i++) {
        i_diff = eigenvalues[end_index-i] - eigenvalues[end_index-i-1];

        sum += i_diff;
        avg = sum / static_cast<float64_t>(i+1);

        // relative i diff
        rel_i_diff = (i_diff-avg)/avg;


        if (rel_i_diff > max_diff) {
            max_diff = rel_i_diff;
            max_k_selected = i + 1;
        }
    }

    if (max_k_selected < min_k)
        max_k_selected = min_k;

    return max_k_selected;
}

shogun::SGMatrix<float64_t> EigenSolver::GetTopKEigenvectorsMatrix(
        shogun::SGMatrix<float64_t>& graph_matrix, int min_k, int max_k) {
    // the given graph_matrix is overwritten
    // and contains orthonormal eigenvectors afterwards
    shogun::SGVector<float64_t> eigenvalues =
            shogun::SGMatrix<float64_t>::compute_eigenvectors(graph_matrix);
    int row_end = graph_matrix.num_rows-1;
    int top_k = GetBestK(eigenvalues, min_k, max_k);

    shogun::SGMatrix<float64_t> top_k_matrix(top_k, graph_matrix.num_cols);

    // keep only k eigenvectors
    for (int i = 0; i < graph_matrix.num_rows; i++) {
        for (int j = 0; j < top_k; j++) {
            top_k_matrix(j, i) = graph_matrix(i, row_end-j);
        }
    }

    return top_k_matrix;
}


