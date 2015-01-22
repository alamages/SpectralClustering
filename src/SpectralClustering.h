/* Copyright 2014: Emmanouil Kiagias <e.kiagias@gmail.com>
 * License: GPLv3
 */
#ifndef SRC_SPECTRALCLUSTERING_H_
#define SRC_SPECTRALCLUSTERING_H_

#include "Graph.h"
#include "GraphMatrixLoader.h"
#include <shogun/lib/SGMatrix.h>
#include <shogun/clustering/KMeans.h>
#include <string>
#include <vector>

class SpectralClustering {
 public:
    explicit SpectralClustering(GraphMatrixLoader* g_loader = NULL) :
        graph_loader(g_loader) {}
    ~SpectralClustering();
    // load the graph file
    std::vector<int> ClusterGraph(std::string filename);
    std::vector<int> ClusterFeatures(std::string libsvmfile);
    shogun::CMulticlassLabels* ClusterGraphMatrix(
            shogun::SGMatrix<float64_t> &graph_matrix);
    void AddGraphMatrixLoader(GraphMatrixLoader* g_loader);
 private:
    GraphMatrixLoader* graph_loader;
    void GetStandardMatrix(Graph &grapht,
                           shogun::SGMatrix<float64_t> &graph_matrix);
    void LoadFromSvmLibFormat(const char * file_name,
        shogun::SGMatrix<float64_t> &feats_matrix,
        int32_t &dim_feat, int32_t &num_samples);
    void LoadUnnormalizedLaplacian(shogun::SGMatrix<float64_t> &graph_matrix);
};

#endif  // SRC_SPECTRALCLUSTERING_H_
