/* Copyright 2014: Emmanouil Kiagias <e.kiagias@gmail.com>
 * License: GPLv3
 */
#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_

#include <map>
#include <string>
#include <vector>

class Graph {
 public:
    // load the graphfile and initializes the graph map
    void Load(std::string filename);
    int GetSize();
    void PrintGraph();
    bool IsEmpty();
    int GetEdgesNum();
    std::map<int, std::vector<int>>* GetGraph();
 private:
    std::map<int, std::vector<int>> graph;
};

#endif  // SRC_GRAPH_H_
