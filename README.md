# Spectral Clustering

This code implements Spectral Clustering, more or less, as described [here](http://www.informatik.uni-hamburg.de/ML/contents/people/luxburg/publications/Luxburg07_tutorial.pdf). The code uses  [shogun](https://github.com/shogun-toolbox/shogun) machine learning library for matrixes manipulation and kmeans.

There is no warranty that the code is error/bug free and valid. Purpose of the code is to provide a simple implementation of the algorithm. 

Dependencies
--------------------

 * c++11 
 * qmake 
 * shogun

Compile
------------

Make sure you have shogun installed (you can add by hand shogun's path in the .pro file, you can override what's already there). 

`git clone https://github.com/alamages/SpectralClustering.git`  
`cd SpectralClustering`  
`mkdir build && cd build`  
`qmake ..`  

Info
---------------

The code supports feature vectors and undirected unweighted graph  clustering. Input vectors must be provided in libsvm format. The input graph must be provided in this format:

[node\_id] [neighbor\_id1] [neighbor\_id2] ....

The node ids must in an increasing sequence starting from index 1 up to n (where n is the number of nodes). Same with the neighbor ids.

Examples of input files can be found in the data/ folder.

You can check the `main.cpp` for a simple example of how to use the code.

TODO
------
 
 * make more tests
 * probably add support for weighted/directed graph someday
 * add class to provide custom graph similarity matrix for graph files 

