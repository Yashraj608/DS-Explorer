#include <iostream>
#include <vector>
#include "Graphs.h"
#include <queue>
#include <stack>
using namespace std;

class Graph
{
private:
    int V;
    vector<vector<int>> adjMatrix;
    vector<vector<pair<int, int>>> adjList; // for weighted graph: {vertex, weight}

public:
    Graph(int vertices)
    {
        V = vertices;
        adjMatrix.resize(V, vector<int>(V, 0));
        adjList.resize(V);
    }

    void addEdge(int u, int v, int weight = 1, bool directed = false)
    {
        if (u >= V || v >= V)
        {
            cout << "Invalid vertices!\n";
            return;
        }
        adjMatrix[u][v] = weight;
        adjList[u].push_back({v, weight});
        if (!directed)
        {
            adjMatrix[v][u] = weight;
            adjList[v].push_back({u, weight});
        }
        cout << "Edge added between " << u << " and " << v << " with weight " << weight << ".\n";
    }

    void removeEdge(int u, int v, bool directed = false)
    {
        if (u >= V || v >= V || adjMatrix[u][v] == 0)
        {
            cout << "Edge does not exist!\n";
            return;
        }
        adjMatrix[u][v] = 0;
        for (auto it = adjList[u].begin(); it != adjList[u].end(); ++it)
            if (it->first == v)
            {
                adjList[u].erase(it);
                break;
            }
        if (!directed)
        {
            adjMatrix[v][u] = 0;
            for (auto it = adjList[v].begin(); it != adjList[v].end(); ++it)
                if (it->first == u)
                {
                    adjList[v].erase(it);
                    break;
                }
        }
        cout << "Edge removed between " << u << " and " << v << ".\n";
    }

    void displayMatrix()
    {
        cout << "\nAdjacency Matrix:\n";
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
                cout << adjMatrix[i][j] << " ";
            cout << "\n";
        }
    }

    void displayList()
    {
        cout << "\nAdjacency List:\n";
        for (int i = 0; i < V; i++)
        {
            cout << i << ": ";
            for (auto &p : adjList[i])
                cout << "(" << p.first << "," << p.second << ") ";
            cout << "\n";
        }
    }

    void DFSUtil(int v, vector<bool> &visited)
    {
        visited[v] = true;
        cout << v << " ";
        for (auto &p : adjList[v])
            if (!visited[p.first])
                DFSUtil(p.first, visited);
    }

    void DFS(int start)
    {
        vector<bool> visited(V, false);
        cout << "DFS Traversal from vertex " << start << ": ";
        DFSUtil(start, visited);
        cout << "\n";
    }

    void DFSAll()
    {
        vector<bool> visited(V, false);
        cout << "DFS Traversal for all vertices: ";
        for (int i = 0; i < V; i++)
            if (!visited[i])
                DFSUtil(i, visited);
        cout << "\n";
    }

    void BFS(int start)
    {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);
        cout << "BFS Traversal from vertex " << start << ": ";
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            cout << v << " ";
            for (auto &p : adjList[v])
            {
                if (!visited[p.first])
                {
                    visited[p.first] = true;
                    q.push(p.first);
                }
            }
        }
        cout << "\n";
    }

    void BFSAll()
    {
        vector<bool> visited(V, false);
        cout << "BFS Traversal for all vertices: ";
        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                queue<int> q;
                visited[i] = true;
                q.push(i);
                while (!q.empty())
                {
                    int v = q.front();
                    q.pop();
                    cout << v << " ";
                    for (auto &p : adjList[v])
                    {
                        if (!visited[p.first])
                        {
                            visited[p.first] = true;
                            q.push(p.first);
                        }
                    }
                }
            }
        }
        cout << "\n";
    }

    int countEdges()
    {
        int count = 0;
        for (int i = 0; i < V; i++)
            for (auto &p : adjList[i])
                count++;
        return count / 2; // for undirected
    }

    void checkEdge(int u, int v)
    {
        if (u >= V || v >= V)
        {
            cout << "Invalid vertices!\n";
            return;
        }
        if (adjMatrix[u][v])
            cout << "Edge exists between " << u << " and " << v << ".\n";
        else
            cout << "No edge between " << u << " and " << v << ".\n";
    }

    void vertexDegree(int v)
    {
        if (v >= V)
        {
            cout << "Invalid vertex!\n";
            return;
        }
        int degree = adjList[v].size();
        cout << "Degree of vertex " << v << " is " << degree << ".\n";
    }

    bool isConnected()
    {
        vector<bool> visited(V, false);
        DFSUtil(0, visited);
        for (bool v : visited)
            if (!v)
                return false;
        return true;
    }

    bool isCyclicUtil(int v, vector<bool> &visited, int parent)
    {
        visited[v] = true;
        for (auto &p : adjList[v])
        {
            int u = p.first;
            if (!visited[u])
            {
                if (isCyclicUtil(u, visited, v))
                    return true;
            }
            else if (u != parent)
                return true;
        }
        return false;
    }

    bool isCyclic()
    {
        vector<bool> visited(V, false);
        for (int i = 0; i < V; i++)
            if (!visited[i] && isCyclicUtil(i, visited, -1))
                return true;
        return false;
    }

    int getVertices() { return V; }
};

// ========================= GRAPH MENU ========================= //
void graphMenu()
{
    int vertices;
    cout << "Enter number of vertices: ";
    cin >> vertices;

    Graph g(vertices);
    int choice, u, v, w;
    bool directed;

    do
    {
        cout << "\n=== GRAPH MENU ===\n";
        cout << "1. Add Edge\n2. Remove Edge\n3. Display Adjacency Matrix\n4. Display Adjacency List\n";
        cout << "5. BFS Traversal\n6. DFS Traversal\n7. BFS All Vertices\n8. DFS All Vertices\n";
        cout << "9. Count Vertices\n10. Count Edges\n11. Check Edge Existence\n";
        cout << "12. Vertex Degree\n13. Check if Connected\n14. Check if Cyclic\n15. Back\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter vertices u v and weight: ";
            cin >> u >> v >> w;
            cout << "Directed edge? (1-Yes / 0-No): ";
            cin >> directed;
            g.addEdge(u, v, w, directed);
            break;
        case 2:
            cout << "Enter vertices u v: ";
            cin >> u >> v;
            cout << "Directed edge? (1-Yes / 0-No): ";
            cin >> directed;
            g.removeEdge(u, v, directed);
            break;
        case 3:
            g.displayMatrix();
            break;
        case 4:
            g.displayList();
            break;
        case 5:
            cout << "Enter starting vertex: ";
            cin >> u;
            g.BFS(u);
            break;
        case 6:
            cout << "Enter starting vertex: ";
            cin >> u;
            g.DFS(u);
            break;
        case 7:
            g.BFSAll();
            break;
        case 8:
            g.DFSAll();
            break;
        case 9:
            cout << "Total vertices: " << g.getVertices() << "\n";
            break;
        case 10:
            cout << "Total edges: " << g.countEdges() << "\n";
            break;
        case 11:
            cout << "Enter vertices u v: ";
            cin >> u >> v;
            g.checkEdge(u, v);
            break;
        case 12:
            cout << "Enter vertex: ";
            cin >> u;
            g.vertexDegree(u);
            break;
        case 13:
            cout << (g.isConnected() ? "Graph is connected\n" : "Graph is disconnected\n");
            break;
        case 14:
            cout << (g.isCyclic() ? "Graph contains cycle\n" : "Graph has no cycle\n");
            break;
        case 15:
            cout << "Returning to main menu...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 15);
}


