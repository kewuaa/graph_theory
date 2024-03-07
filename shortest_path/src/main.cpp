#include <string>
#include <filesystem>

#include "core.hpp"

using namespace graph_theory;


int main(int argc, char** argv) {
    shortest_path::Graph graph;
    const char* filename = argc < 2 ? "./adjacency_matrix.txt" : argv[1];
    if (!std::filesystem::exists(filename)) {
        std::string msg = "Invaild path: ";
        msg += filename;
        msg += " not exists";
        throw std::runtime_error(msg);
    }
    graph.load_from_txt(filename);
    for (int i = 0; i < graph.node_count(); i++) {
        for (int j = i + 1; j < graph.node_count(); j++) {
            shortest_path::Node* end = graph.search(i, j);
            printf(
                "shortest path of node %d -> node %d: %lf\n",
                i + 1,
                end->number,
                end->distance
            );
            printf("road:\n\t");
            printf("%d ", end->number);
            shortest_path::Node* node = end;
            while (node->forward_node != nullptr) {
                node = node->forward_node;
                printf("<- %d ", node->number);
            }
            printf("\n\n");
            graph.reset_nodes();
        }
    }
    return 0;
}
