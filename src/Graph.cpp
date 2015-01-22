/* Copyright 2014: Emmanouil Kiagias <e.kiagias@gmail.com>
 * License: GPLv3
 */
#include "Graph.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <vector>

void Graph::Load(std::string filename) {
    std::ifstream graphfile(filename);

    std::string line;
    while (std::getline(graphfile, line)) {
        std::string token;
        int node_id;
        std::istringstream sline(line);

        // read the first token which is the node id
        std::getline(sline, token, '\t');
        node_id = std::stoi(token);

        std::vector<int> neighbors;

        // loop over the rest of the tokens/neighbors of the node
        while (std::getline(sline, token, '\t')) {
            neighbors.push_back(std::stoi(token));
        }
        // save the node
        graph[node_id] = neighbors;
    }
    graphfile.close();
}

bool Graph::IsEmpty() {
    return graph.empty();
}

void Graph::PrintGraph() {
    for (auto& iter : graph) {
        std::cout << iter.first;
        for (auto& n : iter.second) {
            std::cout << "\t" << n;
        }
        std::cout << std::endl;
    }
}

int Graph::GetSize() {
    return graph.size();
}

std::map<int, std::vector<int>>* Graph::GetGraph() {
    return &graph;
}

int Graph::GetEdgesNum() {
    int edges_num = 0;
    for (auto& iter : graph) {
        edges_num += iter.second.size();
    }

    return edges_num;
}
