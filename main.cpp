#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <stack>
#include <tuple>

using namespace std;

bool can_pass(int x1, int y1, int p1, int x2, int y2) {
    int dx = x1 - x2;
    int dy = y1 - y2;
    int squared_distance = dx * dx + dy * dy;
    return squared_distance <= p1 * p1;
}

vector<vector<bool>> build_adjacency_matrix(const vector<tuple<int, int, int>>& kids) {
    int n = kids.size();
    vector<vector<bool>> adjacency_matrix(n, vector<bool>(n, false));
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {

            int k1_x, k1_y, k1_p;
            tie(k1_x, k1_y, k1_p) = kids[i];

            int k2_x, k2_y, k2_p;
            tie(k2_x, k2_y, k2_p) = kids[j];

            if (can_pass(k1_x, k1_y, min(k1_p, k2_p), k2_x, k2_y)) {
                adjacency_matrix[i][j] = true;
                adjacency_matrix[j][i] = true;
            }
        }
    }
    return adjacency_matrix;
}

void dfs() {

}

void bfs() {

}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input.txt>" << endl;
        return 1;
    }

    ifstream input(argv[1]);

    if (!input.is_open()) {
        cerr << "Error: Unable to open file \"" << argv[1] << "\"" << endl;
        return 1;
    }

    int n, source, target;
    input >> n >> source >> target;

    vector<tuple<int, int, int>> kids(n);

    for (int i = 0; i < n; ++i) {
        int x, y, p;
        input >> x >> y >> p;
        kids[i] = make_tuple(x, y, p);
    }

    input.close();

    vector<vector<bool>> adjacency_matrix = build_adjacency_matrix(kids);
    cout << "Graph:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << adjacency_matrix[i][j] << " ";
        }
        cout << endl;
    }
    exit(0);
}

// int main(){
//     /*
//         INSERT ALL YOUR CODE IN HERE!
//         Program Compile Command: g++ -std=c++11 -Wall -Werror main.cpp -o main
//         Program Run Command: ./main <input.txt>
//         Expected input: /graphs/case{$n}/input_{$n}.txt
//         Expected output: graph.txt bfs.txt dfs.txt
//         Please, try to write clean and readable code. Remember to comment!!
//     */
//     exit(0);
// }