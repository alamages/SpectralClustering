TEMPLATE = app
CONFIG += c++11
CONFIG -= qt
TARGET = SpectralClustering
INCLUDEPATH += . src

# Input
HEADERS += src/EigenSolver.h \
           src/ENeighborhoodGraph.h \
           src/EuclideanDistanceMatrix.h \
           src/FullyConnectedGraph.h \
           src/Graph.h \
           src/GraphMatrixLoader.h \
           src/KnnGraph.h \
           src/SimilarityMatrixLoader.h \
    src/SpectralClustering.h

SOURCES += src/EigenSolver.cpp \
           src/ENeighborhoodGraph.cpp \
           src/EuclideanDistanceMatrix.cpp \
           src/FullyConnectedGraph.cpp \
           src/Graph.cpp \
           src/KnnGraph.cpp \
           src/main.cpp \
    src/SpectralClustering.cpp

win32:CONFIG(release, debug|release): LIBS += -L/usr/local/lib/release/ -lshogun
else:win32:CONFIG(debug, debug|release): LIBS += -L/usr/local/lib/debug/ -lshogun
else:unix: LIBS += -L/usr/local/lib/ -lshogun

INCLUDEPATH += /usr/local/include
