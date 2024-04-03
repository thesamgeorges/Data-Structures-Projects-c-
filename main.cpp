#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
//You may choose to maintain a Priority Queue for all the discovered edges to pick the minimum edge every time. A solution without a Priority Queue will also be accepted.
class PQ {
public: //constructor
    PQ(int verticesCount) : prev(verticesCount, -1), distances(verticesCount, std::numeric_limits<int>::max()), visited(verticesCount, false) {
      
    }
    ~PQ() {
      
    } // destructor

    void enqueue(int vertex, int cost) {
        distances[vertex] = cost;
    }

    std::pair<int, int> dequeueMin() {
      
        int minIndex = findMinIndex();
      
          visited[minIndex] = true;
        return std::make_pair(minIndex, distances[minIndex]);
    }

    bool isEmpty() const {
        return std::all_of(visited.begin(), visited.end(), [](bool v) { return v; });
    }

    std::vector<int> prev;

  private:
    std::vector<int> distances;
    std::vector<bool> visited;

    int findMinIndex() const {
        int minIndex = -1;
        int minDistance = std::numeric_limits<int>::max();

        for (int i = 0; i < distances.size(); ++i) {
            if (!visited[i] && distances[i] < minDistance) {
                minDistance = distances[i];
                minIndex = i;
            }
        }

        return minIndex;
    }

    friend void findMinimumSpanningTree(int graph[][5], int verticesCount, PQ& priorityq, std::vector<std::pair<int, int>>& mstEdges);
};

void findMinimumSpanningTree(int graph[][5], int verticesCount, PQ& priorityq, std::vector<std::pair<int, int>>& mstEdges) {
    int startVertex = 0;
    priorityq.enqueue(startVertex, 0);

    while (!priorityq.isEmpty()) {
        int minVertex = priorityq.dequeueMin().first;
       int currentVertex = minVertex;
   int currentDistance = priorityq.distances[minVertex];

        for (int x = 0; x < verticesCount; ++x) {
            if (graph[currentVertex][x] && !priorityq.visited[x] && graph[currentVertex][x] < priorityq.distances[x]) {
                priorityq.enqueue(x, graph[currentVertex][x]);
                priorityq.prev[x] = currentVertex; }
        }

        
        for (int i = 0; i < verticesCount; ++i) {
          if (!priorityq.visited[i] && graph[currentVertex][i] && graph[currentVertex][i] < priorityq.distances[i]) {
                priorityq.distances[i] = graph[currentVertex][i];
            }
        }

        mstEdges.push_back({currentVertex, currentDistance});

      
 }
  
}

int main() {
    int graphMatrix[5][5] = {
        {0, 8, 14, 0, 0},
        {8, 0, 12, 18, 9},
        {14, 12, 0, 23, 0},
        {0, 18, 23, 0, 7},
        {0, 9, 0, 7, 0}
    };

    int verticesCount = 5;

    PQ priorityq(verticesCount);
    std::vector<std::pair<int,int>>mstEdges;

    findMinimumSpanningTree(graphMatrix, verticesCount, priorityq, mstEdges);

    std::cout << "Prim’s MST is Edge -> Cost\n";
    for (const auto & edge : mstEdges) {
        if (priorityq.prev[edge.first] != -1) 
        {

            std::cout << priorityq.prev[edge.first] << " - " << edge.first << " -> " << edge.second << "\n"; }
    }
 return 0;
}
