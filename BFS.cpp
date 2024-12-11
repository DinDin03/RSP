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

  void BFS(int start, int end) { // A function to perfrom breadth-first search on a graph. Takes parameters for start vertex and end vertex
    vector<bool> visited(vertices, false); // A vector of booleans to track whether a vertex is visited or not. Have 'vertices' number of elements and initialise them to false
    vector<int> parent(vertices, -1); // A vector of integers to keep track of the parent of each vertex which has vertices number of elememtns and initialised to -1 to indicate no parent
    vector<int> distance(vertices, INT_MAX); // A vector of integers to keep track of the shortest distance from the start vertex to each vertex which is initialised to infinity
    queue<int> q; // A queue for traversal which ensures that vertices are explored in the order of their discovery

    visited[start] = true; // mark the start vertex as visited
    distance[start] = 0; // Set the distance from itself to iteself to 0
    q.push(start); // add the start vertex to the queue. 

    while (!q.empty()) { // Iterate through the queue as long as it is not empty
      int current = q.front(); // an integer called current which will store the value of the first element in the queue
      q.pop(); // pop the element from the queue as it will be processed

      for (int neighbor : adjList[current]) { // Iterate through all the neighbours of the current vertex
        if (!visited[neighbor]) { // if the neighbour is not already visited 
          visited[neighbor] = true; // Mark the neighbour as visited
          parent[neighbor] = current; // Set the parent of that neighbour to be the current vertex
          distance[neighbor] = distance[current] + 1; // Update the distance of the neighbout as the distance to the current vertex + 1
          q.push(neighbor); // Enqueue the neighbour for further exploration 

          if (neighbor == end) { // if the neighbour that is currently being explored is the end vertex
            break; // exit the loop
          }
        }
      }
    }

    if (!visited[end]) { // After the BFS, if the end vertex was not reached then there is no path from start to end
      cout << "\nNo path exists from " << start << " to " << end << endl;
      return;
    }

    vector<int> path; // if a path exists, create a vector of integers which stores the path from start to end
    for (int v = end; v != -1; v = parent[v]) { // Iterate through the elements of the parent vector from the end to start
      path.push_back(v); // Add the vertex to the path vector
    }
    reverse(path.begin(), path.end()); // Reverse the path so that it stores from start to end. During BFS, parent vector stores the immediate predessor of each vertex using backward tracing

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
