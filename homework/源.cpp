
#include <iostream>
#include "../../../vector/vectordes.h"
#include"../../../vector/vectorex.h"
#include <queue>
#include "../../../vector/stack.h"
#include <climits>

using namespace std;

// ����ͼ�����ݽṹ
class Graph {
private:
    int V; // ������
    vector<vector<int>> adj; // �ڽӾ���

public:
    Graph(int v) {
        V = v;
        adj.resize(V);
        for (int i = 0; i < V; i++) {
            adj[i].resize(V);
            for (int j = 0; j < V; j++) {
                adj[i][j] = 0;
            }
        }
    }

    // ��ӱ�
    void addEdge(int v, int w) {
        adj[v][w] = 1;
        adj[w][v] = 1;
    }

    // BFS�㷨
    void BFS(int s) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[s] = true;
        q.push(s);

        while (!q.empty()) {
            int v = q.front();
            cout << v << " ";
            q.pop();

            for (int i = 0; i < V; i++) {
                if (adj[v][i] && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
        cout << endl;
    }

    // DFS�㷨
    void DFS(int s) {
        vector<bool> visited(V, false);
        stack<int> st;

        visited[s] = true;
        st.push(s);

        while (!st.empty()) {
            int v = st.top();
            cout << v << " ";
            st.pop();

            for (int i = 0; i < V; i++) {
                if (adj[v][i] && !visited[i]) {
                    visited[i] = true;
                    st.push(i);
                }
            }
        }
        cout << endl;
    }

    // Dijkstra�㷨
    void dijkstra(int s) {
        vector<int> dist(V, INT_MAX);
        vector<bool> visited(V, false);

        dist[s] = 0;

        for (int i = 0; i < V - 1; i++) {
            int u = -1;
            for (int j = 0; j < V; j++) {
                if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                    u = j;
                }
            }

            visited[u] = true;

            for (int v = 0; v < V; v++) {
                if (adj[u][v] && !visited[v]) {
                    int newDist = dist[u] + adj[u][v];
                    if (newDist < dist[v]) {
                        dist[v] = newDist;
                    }
                }
            }
        }

        cout << "���·���㷨: " << endl;
        for (int i = 0; i < V; i++) {
            cout << "Vertex " << i << ": " << dist[i] << endl;
        }
    }

    // Prim�㷨
    void prim() {
        vector<int> parent(V, -1);
        vector<int> key(V, INT_MAX);
        vector<bool> visited(V, false);

        key[0] = 0;

        for (int i = 0; i < V - 1; i++) {
            int u = -1;
            for (int j = 0; j < V; j++) {
                if (!visited[j] && (u == -1 || key[j] < key[u])) {
                    u = j;
                }
            }

            visited[u] = true;

            for (int v = 0; v < V; v++) {
                if (adj[u][v] && !visited[v] && adj[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = adj[u][v];
                }
            }
        }

        cout << "��С֧����: " << endl;
        for (int i = 1; i < V; i++) {
            cout << parent[i] << " - " << i << " : " << adj[parent[i]][i] << endl;
        }
    }
};

int main() {
    // ���԰���
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);

    cout << "BFS �㷨: ";
    g.BFS(0);

    cout << "DFS �㷨: ";
    g.DFS(0);

    g.dijkstra(0);

    g.prim();

    return 0;
}
