#include <iostream>
#include <random>
#include <vector>
using namespace std;

class Graph {
 public:
  int vertices;
  vector<vector<int>> adjList;
  vector<int> weight;

  Graph(int v) {
    vertices = v;
    weight.resize(v, 0);
    adjList.resize(v);
  }

  void addVertex(int v) {
    adjList.push_back(vector<int>());
    cout << "Vertex " << v << " added" << endl;
  }

  void addEdge(int u, int v) {
    if (findPathHelper(u, v) == true) {
      cout << "Edge already exists from " << u << " to " << v << endl;
      return;
    }
    if (u == v) {
      cout << "Self loop not allowed from " << u << " to " << v << endl;
      return;
    }
    adjList[u].push_back(v);
    cout << "An edge from " << u << " to " << v << " is added" << endl;
    weight[u]++;
  }

  void deleteEdge(int u, int v) {
    for (auto i = adjList[u].begin(); i != adjList[u].end(); i++) {
      if (*i == v) {
        adjList[u].erase(i);
        cout << "Edge from " << u << " to " << v << " is deleted" << endl;
        weight[u]--;
        return;
      }
    }
    cout << "Edge from " << u << " to " << v
         << " does not exist or already deleted" << endl;
  }

  bool findPathHelper(int u, int v) {
    for (auto i = adjList[u].begin(); i != adjList[u].end(); i++) {
      if (*i == v) {
        return true;
      }
    }
    return false;
  }
  void findPath() {
    int u, v;
    cout << "Enter start vertex: ";
    cin >> u;
    cout << "Enter destination vertex: ";
    cin >> v;
    bool find = findPathHelper(u, v);
    if (find == true) {
      cout << "There is a path" << endl;
      return;
    }
    cout << "There is no path" << endl;
  }

  void printVertexWeight() {
    int max = 0;
    int min = 1000;
    int maxVertex = 0;
    int minVertex = 0;
    cout << endl;
    for (int i = 0; i < vertices; i++) {
      cout << "Vertex " << i << " has weight " << weight[i] << endl;
      if (weight[i] > max) {
        max = weight[i];
        maxVertex = i;
      } else if (weight[i] < min) {
        min = weight[i];
        minVertex = i;
      }
    }
    cout << "\nThe vertex with most number of edges is " << maxVertex
         << " with " << max << " egdes" << endl;
    cout << "The vertex with least number of edges is " << minVertex << " with "
         << min << " egdes" << endl
         << endl;
  }

  void display() {
    cout << endl;
    for (int i = 0; i < vertices; i++) {
      cout << "Vertex " << i << ": ";
      for (int v : adjList[i]) {
        cout << v << " ";
      }
      cout << endl;
    }
  }
};

int main() {
  random_device rd;
  mt19937 gen(rd());
  int numVerteces;
  cout << "Enter the number of verteces you want to add: ";
  cin >> numVerteces;
  uniform_int_distribution<> dist(0, numVerteces - 1);
  Graph g(numVerteces);

  for (int i = 0; i < numVerteces; i++) {
    g.addVertex(i);
  }
  for (int i = 0; i < numVerteces * (numVerteces); i++) {
    int u = dist(gen);
    int v = dist(gen);
    g.addEdge(u, v);
  }
  g.display();
  g.printVertexWeight();
  for (int i = 0; i < numVerteces * (numVerteces); i++) {
    int u = dist(gen);
    int v = dist(gen);
    g.deleteEdge(u, v);
  }
  g.display();
  g.printVertexWeight();
  char choice;
  cout << "Do you want to check for path (Y/N): ";
  cin >> choice;
  while (choice != 'N') {
    g.findPath();
    cout << "Do you want to check for path (Y/N): ";
    cin >> choice;
  }

  return 0;
}
