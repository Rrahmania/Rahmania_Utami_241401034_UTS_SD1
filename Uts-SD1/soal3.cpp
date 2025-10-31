#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

class Graph {
private:
    map<string, vector<pair<string, int>>> adjList;
    map<string, string> namaKota;

public:
    //Fungsi untuk menambahkan edge (jalur) antara dua kota
    void tambahEdge(string dari, string ke, int jarak) {
         // Tambah edge dua arah karena graph tidak berarah
        adjList[dari].push_back({ke, jarak});
        adjList[ke].push_back({dari, jarak});
    }

    // Fungsi untuk mengatur nama lengkap kota berdasarkan kode
    void setNamaKota(string kode, string nama) {
        namaKota[kode] = nama;
    }

   
    void DFS(string start) {
        map<string, bool> visited;
        vector<string> result;
        
        vector<string> stack;
        stack.push_back(start);
        
        while (!stack.empty()) {
            string current = stack.back();
            stack.pop_back();
            
            if (!visited[current]) {
                visited[current] = true;
                result.push_back(current);
                
                for (int i = adjList[current].size() - 1; i >= 0; i--) {
                    string neighbor = adjList[current][i].first;
                    if (!visited[neighbor]) {
                        stack.push_back(neighbor);
                    }
                }
            }
        }

        cout << "PENJELAJAHAN PARUL (DFS dari A):" << endl;
        for (int i = 0; i < result.size(); i++) {
            cout << result[i];
            if (i != result.size() - 1) cout << " -> ";
        }
        cout << "\n" << endl;
    }

    void BFS(string start, string target) {
        map<string, bool> visited;
        map<string, string> parent;
        queue<string> q;

        q.push(start);
        visited[start] = true;
        parent[start] = "";

        bool found = false;
        
        while (!q.empty() && !found) {
            string current = q.front();
            q.pop();

            for (auto neighbor : adjList[current]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    parent[neighbor.first] = current;
                    q.push(neighbor.first);
                    
                    if (neighbor.first == target) {
                        found = true;
                        break;
                    }
                }
            }
        }

        vector<string> path;
        string current = target;
        while (current != "") {
            path.push_back(current);
            current = parent[current];
        }
        reverse(path.begin(), path.end());

        int totalJarak = 0;
        for (int i = 0; i < path.size() - 1; i++) {
            for (auto neighbor : adjList[path[i]]) {
                if (neighbor.first == path[i + 1]) {
                    totalJarak += neighbor.second;
                    break;
                }
            }
        }

        cout << "JALUR TERCEPAT PARUL (BFS):" << endl;
        for (int i = 0; i < path.size(); i++) {
            cout << namaKota[path[i]] << " (" << path[i] << ")" << endl;
            if (i < path.size() - 1) {
                for (auto neighbor : adjList[path[i]]) {
                    if (neighbor.first == path[i + 1]) {
                        cout << neighbor.second << "m" << endl;
                        break;
                    }
                }
            }
        }

        cout << "\nJalur terpendek: ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size() - 1) cout << " -> ";
        }
        cout << "\nTotal langkah: " << path.size() - 1 << " edge" << endl;
        cout << "Total jarak: " << totalJarak << " meter" << endl;
    }
};

int main() {
    Graph g;

    g.setNamaKota("A", "Ikan Bakar Pak Harry");
    g.setNamaKota("B", "Gudang Kaleng Bekas");
    g.setNamaKota("C", "Sushi Kucing Alya");
    g.setNamaKota("D", "Kedai IKLC");
    g.setNamaKota("E", "Pasar Ikan Tengah Malam");

    g.tambahEdge("A", "B", 5);
    g.tambahEdge("A", "C", 2);
    g.tambahEdge("B", "D", 4);
    g.tambahEdge("C", "D", 1);
    g.tambahEdge("D", "E", 3);

    g.DFS("A");
    g.BFS("A", "E");

    return 0;
}