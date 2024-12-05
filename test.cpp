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

  void BFS(int start, int end) {
    vector<bool> visited(
        vertices,
        false);  // keeps track of whether certain vertex is visisted or not
    vector<int> parent(vertices,
                       -1);  // Records the parent of each vertex in the BFS
                             // tree. this helps reconstruct the path
    vector<int> distance(vertices,
                         INT_MAX);  // Stores the shortest distane from starting
                                    // vertex to each vertex
    queue<int> q;  // A queue is used to manages the vertices in the BFS tree

    visited[start] = true;  // Mark the start vertex as visited
    distance[start] = 0;    // Distance from the starting vertex to itself is 0
    q.push(start);          // Add the start vertex to the queue

    while (!q.empty()) {  // Iterate until the queue.empty() is false in
                          // otherwords as long as the queue is not empty
      int current =
          q.front();  // set the vertex at the front of the queue to the current
      q.pop();        // remove it from the queue

      for (int neighbor :
           adjList[current]) {  // iterates through all the adjacent vertices of
                                // the current vertex
        if (!visited[neighbor]) {      // if the neighbour is not visited
          visited[neighbor] = true;    // Mark it as visited
          parent[neighbor] = current;  // set the parent of that newly visited
                                       // vertex to the current vertex
          distance[neighbor] = distance[current] + 1;  // increment the distance
          q.push(neighbor);  // add the neighbour to the queue

          if (neighbor == end) {  // if the neighbour is same as the end stop
            break;
          }
        }
      }
    }

    if (!visited[end]) {
      cout << "\nNo path exists from " << start << " to " << end << endl;
      return;
    }

    vector<int> path;
    for (int v = end; v != -1;
         v = parent[v]) {  // reconstruct the shortest path by backtracking from
                           // end to start using the parent array
      path.push_back(v);
    }
    reverse(path.begin(), path.end());

    cout << "\nShortest path from " << start << " to " << end << ": ";
    for (int node : path) {
      cout << node << "->";
    }
    cout << "reached";
    cout << "\nPath length: " << distance[end] << endl;
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
  for (int i = 0; i < numVerteces * 2; i++) {
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
        g.BFS(i, j);
      }
    }
  }
  return 0;
}
