#include "Graph.h"
#include <fstream>
#include <iostream>
#include <sstream>

void Graph::Load(std::string filename){
    std::ifstream graphfile(filename);

    std::string line;
    while(std::getline(graphfile, line)){
        std::string token;
        int node_id;
        std::istringstream sline( line );

        // read the first token which is the node id
        std::getline(sline, token, '\t');
        node_id = std::stoi( token );

        std::vector<int> neighbors;

        // loop over the rest of the tokens/neighbors of the node
        while (std::getline(sline, token, '\t')){
            neighbors.push_back( std::stoi(token) );
        }

        // save the node
        graph[node_id] = neighbors;
    }
    graphfile.close();
}

bool Graph::IsEmpty(){
    return graph.empty();
}

void Graph::PrintGraph(){
    for (auto& iter : graph ){
        std::cout << iter.first;
        for (auto& n : iter.second){
            std::cout << "\t" << n;
        }
        std::cout << std::endl;
    }
}

int Graph::GetSize(){
    return graph.size();
}

std::map<int, std::vector<int>>* Graph::GetGraph(){
    return &graph;
}

int Graph::GetEdgesNum(){
    int edges_num = 0;
    for (auto& iter : graph){
        edges_num += iter.second.size();
    }

    return edges_num;
}

const std::vector<int>* Graph::Neighbours(int node_id){
    return &graph[node_id];
}

/* An O(m) Algorithm for Cores Decomposition of Networks
 * Vladimir Batagelj and Matjaz Zaversnik, 2003.
 * http://arxiv.org/abs/cs.DS/0310049
 */
std::vector<int> Graph::Coreness(){
    int n = graph.size(), md = 0;
    int pu, pw, w, num, du;
    std::vector<int> pos(n+1), vert(n+1);
    std::vector<int> deg(n+1);

    int d;
    for (int v = 1; v <= n; v++){
        d = graph[v].size();
        deg[v] = d;
        if (d > md) md = d;
    }

    std::vector<int> bin(md+1);

    for (int v=1; v <=n; v++) bin[deg[v]] += 1;

    int start = 1;
    for (int d = 0; d <= md; d++){
        num = bin[d];
        bin[d] = start;
        start += num;
    }

    for (int v = 1; v <= n; v++){
        pos[v] = bin[deg[v]];
        vert[pos[v]] = v;
        bin[deg[v]] += 1;
    }

    for (int d = md; d >= 1; d--){
        bin[d] = bin[d-1];
    }
    bin[0] = 1;

    for (int i = 1; i <= n; i++){
        int v = vert[i];

        for (auto& u : graph[v]){
            if (deg[u] > deg[v]){
                du = deg[u];
                pu = pos[u];
                pw = bin[du];
                w = vert[pw];
                if (u != w){
                    pos[u] = pw;
                    pos[w] = pu;
                    vert[pu] = w;
                    vert[pw] = u;
                }
                bin[du] += 1;
                deg[u] -= 1;
            }
        }
    }

    return deg;
}
