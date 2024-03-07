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

                Node(int number, int total_node_num);
                void reset();
                void add_neighber(Node* neighber, double distance);
                Neighber* search_neighber();
        };

        struct Line {
            Node* start;
            Node* end;
            double length;
        };

        struct Neighber {
            Node* node;
            Line* line;

            Neighber(Node* node, Line* line);
            ~Neighber();
        };

        void search(Node* start, Node* end);
    }
}
