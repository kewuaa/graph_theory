#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

#include "core.hpp"

using namespace graph_theory;


void load_nodes(std::vector<shortest_path::Node>& node_list, const char* filename) {
    std::ifstream f(filename);
    std::string line;
    std::getline(f, line);
    int n = std::stoi(line);
    node_list.reserve(n);
    for (int i = 1; i < n + 1; i++) {
        node_list.emplace_back(i, n);
    }
    for (int i = 0; i < n; i++) {
        if (!std::getline(f, line)) {
            throw std::runtime_error("incorrect number");
        }
        std::istringstream stream(line);
        std::string s;
        for (int j = 0; j < i; j++) {
            if (!std::getline(stream, s, ' ')) {
                throw std::runtime_error("incorrect number");
            }
            double distance;
            try {
                distance = std::stod(s);
            } catch (std::invalid_argument& e) {
                continue;
            }
            node_list[i].add_neighber(&node_list[j], distance);
            node_list[j].add_neighber(&node_list[i], distance);
        }
    }
    f.close();
}


int main(int argc, char** argv) {
    std::vector<shortest_path::Node> node_list;
    const char* filename = argc < 2 ? "./adjacency_matrix.txt" : argv[1];
    if (!std::filesystem::exists(filename)) {
        std::string msg = "Invaild path: ";
        msg += filename;
        msg += " not exists";
        throw std::runtime_error(msg);
    }
    load_nodes(node_list, filename);
    shortest_path::Node* start;
    shortest_path::Node* end;
    for (int i = 0; i < node_list.size(); i++) {
        for (int j = i + 1; j < node_list.size(); j++) {
            start = &node_list[i];
            end = &node_list[j];
            shortest_path::search(start, end);
            printf(
                "shortest path of node %d -> node %d: %lf\n",
                start->number,
                end->number,
                end->distance
            );
            for (auto& node : node_list) {
                node.reset();
            }
        }
    }


    return 0;
}
