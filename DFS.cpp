#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
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
    // cout << "Vertex " << v << " added" << endl;
  }

  void addEdge(int u, int v) {
    if (findPathHelper(u, v) == true) {
      // cout << "Edge already exists from " << u << " to " << v << endl;
      return;
    }
    if (u == v) {
      // cout << "Self loop not allowed from " << u << " to " << v << endl;
      return;
    }
    adjList[u].push_back(v);
    // cout << "An edge from " << u << " to " << v << " is added" << endl;
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

  bool DFSHelper(int current, int end, vector<bool> &visited, vector<int> &path,
                 vector<int> &tempPath) { // A helper function for DFS. Current is the current vertex being explored
                                          // end is the destination vertex. visisted tracks whether a vertex has been already visited or not 
                                          // path a reference to store the final path from start to end if found 
                                          // a temporary path to track the current traversal
    visited[current] = true; // Mark the current vertex being explored as visited
    tempPath.push_back(current); // push the current vertex into the temporary path
    cout << "pushed " << current << " to the temp path" << endl;
    cout << "Current path is: ";
    for (int temp : tempPath) {
      cout << temp << " ";
    }
    cout << endl;
    cout << "Checking path " << current << " to " << end << endl;

    if (current == end) { // if the end node is reached
      path = tempPath; // copy the path in the temporary path to the final path 
      cout << "end is reached" << endl;
      return true;  // End found
    }
    cout << "end was not reached. trying again" << endl;

    for (int neighbor : adjList[current]) { // iterate through the neighbours of the current vertex
      if (!visited[neighbor]) { // if the neighbour is not visited
        if (DFSHelper(neighbor, end, visited, path, tempPath)) { // recursively call the function for the neighbour so it goes in deep
          return true; // return true if the helper function returns true, meaning a path is found
        }
      }
    }

    tempPath.pop_back(); // if all neighbours of the current vertex have been explored and no path is found, romve the current vertex from the temp path to back track to the previous vertex
    return false;
  }

  void DFS(int start, int end) { // function to call the DFS which takes a start vertex and end vertex
    vector<bool> visited(vertices, false);  // To track visited nodes
    vector<int> path;                       // To store the final path
    vector<int> tempPath;                   // To store the current path
    cout << "Path (" << start << "," << end << ")" << endl;

    if (!DFSHelper(start, end, visited, path, tempPath)) {
      cout << "No path exists from " << start << " to " << end << endl << endl;
      return;
    }

    cout << start << " to " << end << " is reachable via ";
    int distance = 0;
    for (int node : path) {
      cout << node << " ";
      distance++;
    }
    cout << "\nDistance is: " << distance - 1 << endl;
    cout << endl;
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
  for (int i = 0; i < numVerteces * 10; i++) {
    int u = dist(gen);
    int v = dist(gen);
    g.addEdge(u, v);
  }
  g.display();
  // g.printVertexWeight();
  for (int i = 0; i < numVerteces; i++) {
    int num = 0;
    for (int j = num; j < numVerteces; j++) {
      if (i != j) {
        g.DFS(i, j);
      }
    }
  }
  return 0;
}
