#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <string>
#include <vector>

class Graph {
public:
    // load the graphfile and initializes the graph map
    void Load(std::string filename);
    // returns an array with the core sequence
    std::vector<int> Coreness();
    // get the node number of graph
    int GetSize();
    void PrintGraph();
    bool IsEmpty();
    int GetEdgesNum();
    std::map<int, std::vector<int>>* GetGraph();
    // #TODO is not needed to be removed
    const std::vector<int>* Neighbours(int node_id);

private:
    std::map<int, std::vector<int>> graph;
};

#endif // GRAPH_H
