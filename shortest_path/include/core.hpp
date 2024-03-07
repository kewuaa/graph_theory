#include <vector>


namespace graph_theory {
    namespace shortest_path {
        struct Neighber;

        class Node {
            private:
                bool _all_neighbers_searched;
                std::vector<Neighber> _neighbers;
            public:
                int number;
                bool marked;
                double distance;
                Node* forward_node;

                Node(int number);
                void reset();
                void add_neighber(Node* neighber, double distance);
                Neighber* search_neighber();
        };

        struct Neighber {
            Node* node;
            double distance;

            Neighber(Node* node, double length);
        };

        class Graph {
            private:
                std::vector<Node> _node_list;
            public:
                void load_from_txt(const char* path);
                int node_count();
                Node* search(int start_i, int end_i);
                void reset_nodes();
        };
    }
}
