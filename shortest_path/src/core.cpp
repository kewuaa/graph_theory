#include <sstream>
#include <fstream>

#include "core.hpp"


namespace graph_theory::shortest_path {
    Node::Node(int number):
        _all_neighbers_searched(false),
        number(number), marked(false), distance(-1), forward_node(nullptr) {
        _neighbers.reserve(3);
    }

    void Node::reset() {
        _all_neighbers_searched = false;
        marked = false;
        distance = -1;
        forward_node = nullptr;
    }

    void Node::add_neighber(Node* neighber, double distance) {
        _neighbers.emplace_back(neighber, distance);
    }

    Neighber* Node::search_neighber() {
        if (_all_neighbers_searched) {
            return nullptr;
        }
        double min_distance = -1;
        Neighber* nearest_neighber = nullptr;
        for (int i = 0; i < _neighbers.size(); i++) {
            if (_neighbers[i].node->marked) {
                continue;
            }
            if (min_distance < 0 || _neighbers[i].distance < min_distance) {
                min_distance = _neighbers[i].distance;
                nearest_neighber = &_neighbers[i];
            }
        }
        if (min_distance < 0) {
            _all_neighbers_searched = true;
        }
        return nearest_neighber;
    }

    Neighber::Neighber(Node* node, double distance): node(node), distance(distance) {
        //
    }

    void Graph::load_from_txt(const char* filename) {
        std::ifstream f(filename);
        std::string line;
        std::getline(f, line);
        int n = std::stoi(line);
        _node_list.reserve(n);
        for (int i = 1; i < n + 1; i++) {
            _node_list.emplace_back(i);
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
                _node_list[i].add_neighber(&_node_list[j], distance);
                _node_list[j].add_neighber(&_node_list[i], distance);
            }
        }
        f.close();
    }

    int Graph::node_count() {
        return _node_list.size();
    }

    Node* Graph::search(int start_i, int end_i) {
        Node* start = &_node_list[start_i];
        Node* end = &_node_list[end_i];
        std::vector<Node*> marked_nodes;

        start->marked = true;
        start->distance = 0;
        marked_nodes.push_back(start);

        while (1) {
            double min_distance = -1;
            Neighber* nearest_neighber = nullptr;
            for (int i = 0; i < marked_nodes.size(); i++) {
                auto neighber = marked_nodes[i]->search_neighber();
                if (neighber == nullptr) {
                    continue;
                }
                double distance = marked_nodes[i]->distance + neighber->distance;
                if (min_distance < 0 || distance < min_distance) {
                    neighber->node->forward_node = marked_nodes[i];
                    min_distance = distance;
                    nearest_neighber = neighber;
                }
            }
            nearest_neighber->node->marked = true;
            nearest_neighber->node->distance = min_distance;
            marked_nodes.push_back(nearest_neighber->node);
            if (nearest_neighber->node == end) {
                break;
            }
        }
        return end;
    }

    void Graph::reset_nodes() {
        for (auto& node : _node_list) {
            node.reset();
        }
    }
}
