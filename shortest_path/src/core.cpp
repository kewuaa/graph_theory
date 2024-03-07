#include <iostream>

#include "core.hpp"


namespace graph_theory::shortest_path {
    Neighber::Neighber(Node* node, Line* line): node(node), line(line) {
        //
    }

    Neighber::~Neighber() {
        delete this->line;
    }

    Node::Node(int number, int total_node_num):
        _all_neighbers_searched(false),
        number(number), marked(false), distance(-1) {
        _neighbers.reserve(total_node_num);
    }

    void Node::reset() {
        _all_neighbers_searched = false;
        marked = false;
        distance = -1;
    }

    void Node::add_neighber(Node* neighber, double distance) {
        auto l = new Line();
        l->start = this;
        l->end = neighber;
        l->length = distance;
        _neighbers.emplace_back(neighber, l);
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
            if (min_distance < 0 || _neighbers[i].line->length < min_distance) {
                min_distance = _neighbers[i].line->length;
                nearest_neighber = &_neighbers[i];
            }
        }
        if (min_distance < 0) {
            _all_neighbers_searched = true;
        }
        return nearest_neighber;
    }

    void search(Node *start, Node *end) {
        std::vector<Line*> lines;
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
                double distance = marked_nodes[i]->distance + neighber->line->length;
                if (min_distance < 0 || distance < min_distance) {
                    min_distance = distance;
                    nearest_neighber = neighber;
                }
            }
            nearest_neighber->node->marked = true;
            nearest_neighber->node->distance = min_distance;
            marked_nodes.push_back(nearest_neighber->node);
            lines.push_back(nearest_neighber->line);
            if (nearest_neighber->node == end) {
                break;
            }
        }
    }
}
