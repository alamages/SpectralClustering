#include <iostream>
#include "Graph.h"
#include "SpectralClustering.h"
#include "FullyConnectedGraph.h"
#include "EuclideanDistanceMatrix.h"
#include "KnnGraph.h"

#include <iostream>
#include <math.h>
#include <ctime>
#include <shogun/base/init.h>

void Usage(char prog[]){
    std::cerr << "Usage: " << prog << " input_libsvm_file" << std::endl
     << " example: " << prog << " data" << std::endl;
}

int main(int argc, char * argv[])
{    
    // simple argument parsing:
    /*if (argc != 2){
        Usage(argv[0]);

        return 1;
    }*/

    std::string graphfile = "oo";//static_cast<std::string>(argv[1]);

    //parse the config file
    shogun::init_shogun_with_defaults();

    //no need to delete that, graph matrix loader will delete it once it owns this object
    EuclideanDistanceMatrix* euclidean_sim_matrix = new EuclideanDistanceMatrix();

    //Fully connected graph

    int sigma = 5;
    //no need to delete that, spectral clustering will delete it once it owns this object
    FullyConnectedGraph* graph_loader = new FullyConnectedGraph(sigma);


    // KNN graph
    //int kn = atoi(conf["kn"].c_str());
    //KnnGraph* graph_loader = new KnnGraph(kn);

    graph_loader->AddSimilarityMatrixLoader(euclidean_sim_matrix);

    SpectralClustering* cl = new SpectralClustering();
    cl->AddGraphMatrixLoader(graph_loader);
    //cl->ClusterFeatures(graphfile);
    cl->LoadGraphFile(graphfile);
    cl->GraphCluster();
    shogun::exit_shogun();

    /* clean up */
    delete cl;

    return 0;
}

