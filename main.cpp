/***************************************************
Title: Bellman-Ford Algorithm
Author: Brian Hernandez
Code Review: Jesse Goodspeed
Date: 05/27/2018
Description:
Below is a C++ implementation of the Bellman-Ford Algorithm. This code runs with
a text file that includes a list of vertices with an adjacency list for each
vertex of the following form:
vertex1 neighbor cost_to_neighbor another_neighbor that_neighbor's_cost ...
vertex2 neighbor cost_to_neighbor another_neighbor that_neighbor's_cost ...
...
final_vertex neighbor cost_to_neighbor another_neighbor that_neighbor's_cost ...

Below are the compilation and run commands for the command-line interface.
TO COMPILE: g++ -std=c++11 main.cpp
TO RUN: ./a.out bFtopology.txt		
****************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <cfloat>

struct Vertex{
    std::unordered_map<std::string, double> adjacency_list;
};

class Graph{
    public:
    Graph();
    void insert_vertex(std::string vertex_name, Vertex* input_vertex);
    void dvr(std::string source_vertex);
    ~Graph();

    private:
    std::unordered_map<std::string, Vertex*> vertices;
    std::unordered_map<std::string, double> distances;
    std::unordered_map<std::string, std::string> prev_hops;
};

namespace file_io {
    Graph* create_graph_from_file(std::string input_file);
}

int main(int argc, char **argv){
    if(argc != 2){
        std::printf("Usage: %s input_graph_file\n", argv[0]);
        return 0;
    }
    Graph* topology_graph = file_io::create_graph_from_file(argv[1]);

    // Input for dvr() is the source node
    topology_graph->dvr("bellman-ford");

    delete topology_graph;
    return 0;
}

//Beginning of Graph functions
Graph::Graph(){
}

void Graph::insert_vertex(std::string vertex_name, Vertex* input_vertex){
    vertices[vertex_name] = input_vertex;
}

void Graph::dvr(std::string source_vertex){
    //Initial conditions for Bellman-Ford algorithm
    for(auto & vertex : vertices){
        distances[vertex.first] = DBL_MAX;
        prev_hops[vertex.first] = "NULL";
    }
    distances[source_vertex] = 0;
    std::cout << std::endl << "--Shortest Path Distance List Iterations--" << std::endl;

    //Run the Bellman-Ford algorithm (vertices)-1 times
    for(auto it = ++vertices.begin(); it != vertices.end(); ++it){
        std::string source_vertex = it->first;
        //For every edge in our graph: we update the min distance and min hop if we find a shorter path
        for(auto & edge : it->second->adjacency_list){
            std::string destination_vertex = edge.first;
            double edge_weight = edge.second;
            if(distances[source_vertex] + edge_weight < distances[destination_vertex]){
                distances[destination_vertex] = distances[source_vertex] + edge_weight;
                prev_hops[destination_vertex] = source_vertex;
                }
            }
        //Output the shortest path distances every iteration
        for(auto & kv : distances){
            if(kv.second > 10000000){
                std::cout << kv.first << ": " << "inf ";
            }
            else{
                std::cout << kv.first << ": " << kv.second << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << "--Shortest Path Predecessor List--" << std::endl;
    for(auto & kv : prev_hops){
        std::cout << kv.first << " preceeded by " << kv.second<< std::endl;
    }
}

Graph::~Graph(){
    for(auto & vertex : vertices){
        delete vertex.second;
    }
}

//Beginning of File Input/Output functions
Graph* file_io::create_graph_from_file(std::string input_file){
    Graph* output_graph = new Graph();

    std::ifstream fin;
    fin.open(input_file);

    std::string curr_line;
    while(getline(fin, curr_line)){
        Vertex* curr_vertex = new Vertex();

        std::istringstream ss(curr_line);
        std::string vertex_name;
        ss >> vertex_name;

        std::string curr_edge;
        double curr_weight;
        while(ss >> curr_edge){
            ss >> curr_weight;
            curr_vertex->adjacency_list[curr_edge] = curr_weight;
        }
        output_graph->insert_vertex(vertex_name, curr_vertex);
    }
    return output_graph;
}
