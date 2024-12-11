#include <iostream>
#include <random>
#include <vector>
using namespace std;

class Graph { // A class called Graph using an adjacency list which has 3 member variables
 public:
  int vertices; // number of vertices in the graph
  vector<vector<int>> adjList; // adjacency list to store edges for each vertex. it is a vector of vectors of type int
  vector<int> weight; // a vector of type int to store the weight of each vertex

  Graph(int v) { // default constructor for graph which takes the number of vertex as input 
    vertices = v; // store the number of vertices
    weight.resize(v, 0); // resize the weight vector to match the number of vertices and initialise them to all 0 
    adjList.resize(v); // resize the adjlist to hold 'v' vertice 
  }

  void addVertex(int v) { // a function to add a vertex to the graph which takes an integer value 
    adjList.push_back(vector<int>()); // add a new empty adjacency list for the new vertex
    cout << "Vertex " << v << " added" << endl;
  }

  void addEdge(int u, int v) { // a function to add an edge from vertex u to vertex v 
    if (findPathHelper(u, v) == true) { // if the funciton pathFindHelper returns true, meaning there is a path from u to v already
      cout << "Edge already exists from " << u << " to " << v << endl;
      return; // exit the function and do not add an edge
    }
    if (u == v) { // if we are trying to add a self edge
      cout << "Self loop not allowed from " << u << " to " << v << endl;
      return; // exit the function and do not add an edge
    }
    adjList[u].push_back(v); // if all criteria's are met, add the vertex v to the adjacency list of u, meaning u and v are connected
    cout << "An edge from " << u << " to " << v << " is added" << endl;
    weight[u]++; // increment the weight of the vertex since we added a new edge
  }

  void deleteEdge(int u, int v) { // a function to delete an edge from u to v 
    for (auto i = adjList[u].begin(); i != adjList[u].end(); i++) { // Iterate through the adjacency list of u
      if (*i == v) { // if the value of the current element (*i) of the adjacency list (u) is equal to the end vertex (v)
        adjList[u].erase(i); // remove the vertex v from the adjacency list, meaning the edge from u to v will be removed
        cout << "Edge from " << u << " to " << v << " is deleted" << endl;
        weight[u]--; // decrement the weight
        return;
      }
    }
    cout << "Edge from " << u << " to " << v
         << " does not exist or already deleted" << endl;
  }

  bool findPathHelper(int u, int v) { // A boolean helper function to check if a path exists from u to v
    for (auto i = adjList[u].begin(); i != adjList[u].end(); i++) { // iterate through the adjacency list of u
      if (*i == v) { // if found
        return true; // return true and exit 
      }
    }
    return false; // if not found return false
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
