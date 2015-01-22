#include "EuclideanDistanceMatrix.h"

#include <iostream>
#include <shogun/lib/ShogunException.h>
#include <shogun/distance/EuclideanDistance.h>
#include <shogun/preprocessor/NormOne.h>

void EuclideanDistanceMatrix::LoadSimilarityMatrix(shogun::SGMatrix<float64_t> &distance_matrix,
                                                   shogun::SGMatrix<float64_t> &feature_matrix){

    //shogun::SGMatrix<float64_t>::display_matrix(feature_matrix);

    shogun::CDenseFeatures<float64_t>* features = new shogun::CDenseFeatures<float64_t>();
    features->set_feature_matrix(feature_matrix);
    SG_REF(features);

    /* normalize using CNormOne */
    if(normalize){
        shogun::CNormOne* prepo_norm = new shogun::CNormOne;
        features->add_preprocessor(prepo_norm);
        bool successful_preprocess = features->apply_preprocessor();

        if (!successful_preprocess){
            std::cerr << "Nope preprocess!" << std::endl;
        }
    }

    /* create distance */
    shogun::CEuclideanDistance* distance=new shogun::CEuclideanDistance(features, features);


    try{
        distance_matrix = distance->get_distance_matrix();
    }
    catch(shogun::ShogunException & sh){
        printf("%s",sh.get_exception_string());
        std::exit(EXIT_FAILURE);
    }

    SG_UNREF(features);
    SG_UNREF(distance);
}
