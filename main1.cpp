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
    return squared_distance <= p1;
}

vector<vector<bool>> build_adjacency_matrix(const vector<tuple<int, int, int>>& kids) {
    int n = kids.size();
    vector<vector<bool>> adjacency_matrix(n, vector<bool>(n, false));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;

            int xi, yi, pi;
            tie(xi, yi, pi) = kids[i];

            int xj, yj, pj;
            tie(xj, yj, pj) = kids[j];

            if (can_pass(xi, yi, pi, xj, yj) && can_pass(xj, yj, pj, xi, yi)) {
                adjacency_matrix[i][j] = adjacency_matrix[j][i] = true;
            }
        }
    }

    return adjacency_matrix;
}

void write_adjacency_matrix_to_file(const vector<vector<bool>>& adjacency_matrix, const string& filename) {
    ofstream output(filename);

    output << "Graph:" << endl;
    for (const auto& row : adjacency_matrix) {
        for (bool val : row) {
            output << val << " ";
        }
        output << endl;
    }

    output.close();
}

int bfs(const vector<vector<bool>>& adjacency_matrix, int source, int target, const string& filename) {
    int n = adjacency_matrix.size();
    vector<bool> visited(n, false);
    vector<int> distance(n, -1);
    vector<int> parent(n, -1);

    queue<int> q;
    visited[source] = true;
    distance[source] = 0;
    q.push(source);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (current == target) {
            ofstream output(filename);

            output << "BFS:" << endl;
            output << distance[current] << " ";

            stack<int> path;
            for (int v = target; v != -1; v = parent[v]) {
                path.push(v);
            }

            while (!path.empty()) {
                output << path.top() << "->";
                path.pop();
            }
            output.seekp(-2, output.cur);
            output << "  " << endl;

            output.close();
            return distance[current];
        }

        for (int i = 0; i < n; ++i) {
            if (adjacency_matrix[current][i] && !visited[i]) {
                visited[i] = true;
                distance[i] = distance[current] + 1;
                parent[i] = current;
                q.push(i);
            }
        }
    }

    return -1;
}

bool dfs_util(const vector<vector<bool>>& adjacency_matrix, int node, int target, vector<bool>& visited, vector<int>& path) {
    visited[node] = true;
    path.push_back(node);

    for (int i = 0; i < adjacency_matrix.size(); ++i) {
        if (adjacency_matrix[node][i]) {
            if (i == target && path.size() > 2) {
                path.push_back(i);
                return true;
            } else if (!visited[i] && dfs_util(adjacency_matrix, i, target, visited, path)) {
                return true;
            }
        }
    }

    if (path.back() == target && path.size() > 2) {
        return true;
    } else {
        path.pop_back();
        visited[node] = false;
        return false;
    }
}



vector<int> dfs(const vector<vector<bool>>& adjacency_matrix, int source, const string& filename) {
    int n = adjacency_matrix.size();
    vector<bool> visited(n, false);
    vector<int> path;

    dfs_util(adjacency_matrix, source, source, visited, path);

    ofstream output(filename);
    output << "DFS:" << endl;

    if (!path.empty()) {
        for (int node : path) {
            output << node << "->";
        }
        output.seekp(-2, output.cur);
        output << "  " << endl;
    } else {
        output << "-1" << endl;
    }

    output.close();
    return path;
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

    // Save adjacency matrix to a file
    write_adjacency_matrix_to_file(adjacency_matrix, "graph.txt");

    // 2.2 Breadth First Search
    int min_passes = bfs(adjacency_matrix, source, target, "bfs.txt");

    // 2.3 Depth First Search
    vector<int> path = dfs(adjacency_matrix, source, "dfs.txt");

    return 0;
}
