#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

#define MAX_VERTICES 100
#define INF 1000 //infinity

struct AdjList
{
    int adjVertex;
    float weight;
    AdjList* next;
};

struct AdjListGraph
{
    int numVertices;
    AdjList* adjList[MAX_VERTICES];
};

// a)
void readGraphFromFile(AdjListGraph& graph, string fileName)
{
    ifstream file(fileName);
    file >> graph.numVertices;
    for (int i = 0; i < graph.numVertices; i++)
    {
        graph.adjList[i] = nullptr;
        for (int j = 0; j < graph.numVertices; j++)
        {
            float weight;
            file >> weight;
            if (weight != INF)
            {
                AdjList* newNode = new AdjList;
                newNode->adjVertex = j;
                newNode->weight = weight;
                newNode->next = graph.adjList[i];
                graph.adjList[i] = newNode;
            }
        }
    }
    file.close();
}

// b)
void printGraph(AdjListGraph graph)
{
    cout << "Num of vertices: " << graph.numVertices << endl;
    for (int i = 0; i < graph.numVertices; i++)
    {
        cout << "adjList[" << i << "]: ";
        for (AdjList* p = graph.adjList[i]; p != nullptr; p = p->next)
        {
            cout << p->adjVertex << "(" << p->weight << ") ";
        }
        cout << endl;
    }
    cout << endl;
}

// c) 
void PathBFS(AdjListGraph graph, int s, int parent[])
{
    bool visited[MAX_VERTICES] = { false };
    for(int i = 0; i < graph.numVertices; i++) parent[i] = -1;
    queue<int> q;
    visited[s] = true;
    parent[s] = s;
    q.push(s);
    
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        for (AdjList* p = graph.adjList[curr]; p != nullptr; p = p->next)
        {
            if (!visited[p->adjVertex])
            {
                visited[p->adjVertex] = true;
                parent[p->adjVertex] = curr;
                q.push(p->adjVertex);
            }
        }
    }
}

// d)
void printPath(int parent[], int s, int v)
{
    if (v == s)
    {
        cout << s << " ";
        return;
    }
    printPath(parent, s, parent[v]);
    cout << v << " ";
}

// e)
void DFS(AdjListGraph graph, int v, bool visited[])
{
    visited[v] = true;
    for (AdjList* p = graph.adjList[v]; p != NULL; p = p->next)
    {
        if (!visited[p->adjVertex])
            DFS(graph, p->adjVertex, visited);
    }
}

bool isConnected(AdjListGraph graph)
{
    bool visited[MAX_VERTICES] = { false };
    DFS(graph, 0, visited);
    for(int i = 0; i < graph.numVertices; i++)
        if (!visited[i])
            return false;
    return true;
}

// f)
void DFSConnectedComponents(AdjListGraph graph, int v, bool visited[], int component[], int k)
{
    visited[v] = true; 
    component[v] = k;
    
    for (AdjList* p = graph.adjList[v]; p != NULL; p = p->next)
    {
        if (!visited[p->adjVertex])
            DFSConnectedComponents(graph, p->adjVertex, visited, component, k);
    }
}

int connectedComponents(AdjListGraph graph, int component[])
{
    bool visited[MAX_VERTICES] = { false };
    int k = 0; //num of connected components
    for (int i = 0; i < graph.numVertices; i++)
    {
        if (!visited[i])
        {
            k++;
            DFSConnectedComponents(graph, i, visited, component, k);
        }
    }
    return k;
}

// g)
void printConnectedComponents(int component[], int n, int k)
{
    cout << "Num of connected components is: " << k << endl;
    for(int i = 1; i <= k; i++)
    {
        cout << "Component[" << i << "]: ";
        for(int j = 0; j < n; j++)
            if (component[j] == i)
                cout << j << " ";
        cout << endl;
    }
    cout << endl;
}

// h)
bool hasPath(AdjListGraph graph, int s, int d)
{
    if (s == d) return true;
    
    bool visited[MAX_VERTICES] = { false };
    queue<int> q;
    visited[s] = true;
    q.push(s);
    
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        
        for (AdjList* p = graph.adjList[curr]; p != nullptr; p = p->next)
        {
            if (p->adjVertex == d) return true;
            if (!visited[p->adjVertex])
            {
                visited[p->adjVertex] = true;
                q.push(p->adjVertex);
            }
        }
    }
    return false;
}

// i)
void pathDFS(AdjListGraph graph, int s, bool visited[], int parent[])
{
    visited[s] = true;
    for (AdjList* p = graph.adjList[s]; p != nullptr; p = p->next)
    {
        if (!visited[p->adjVertex])
        {
            parent[p->adjVertex] = s;
            pathDFS(graph, p->adjVertex, visited, parent);
        }
    }
}

void PathDFS(AdjListGraph graph, int s, int parent[])
{
    bool visited[MAX_VERTICES] = { false };
    for(int i = 0; i < graph.numVertices; i++) parent[i] = -1;
    parent[s] = s;
    pathDFS(graph, s, visited, parent);
}

// j)
vector<int> pathNoVertex(AdjListGraph graph, int s, int d, int v)
{
    vector<int> path;
    if (s == v || d == v) return path; // Nếu s hoặc d là v thì không có đường đi
    
    bool visited[MAX_VERTICES] = { false };
    int parent[MAX_VERTICES];
    for(int i = 0; i < graph.numVertices; i++) parent[i] = -1;
    
    queue<int> q;
    visited[s] = true;
    visited[v] = true; 
    parent[s] = s;
    q.push(s);
    
    bool found = false;
    while (!q.empty() && !found)
    {
        int curr = q.front();
        q.pop();
        
        for (AdjList* p = graph.adjList[curr]; p != nullptr; p = p->next)
        {
            if (p->adjVertex == d)
            {
                parent[d] = curr;
                found = true;
                break;
            }
            if (!visited[p->adjVertex])
            {
                visited[p->adjVertex] = true;
                parent[p->adjVertex] = curr;
                q.push(p->adjVertex);
            }
        }
    }
    
    if (found)
    {
       
        stack<int> st;
        int curr = d;
        while (curr != s)
        {
            st.push(curr);
            curr = parent[curr];
        }
        st.push(s);
        
        while (!st.empty())
        {
            path.push_back(st.top());
            st.pop();
        }
    }
    
    return path;
}

// k) Tìm đường đi chỉ qua các cạnh có trọng số >= M
vector<int> pathGreatThan(AdjListGraph graph, int s, int d, int M)
{
    vector<int> path;
    bool visited[MAX_VERTICES] = { false };
    int parent[MAX_VERTICES];
    for(int i = 0; i < graph.numVertices; i++) parent[i] = -1;
    
    queue<int> q;
    visited[s] = true;
    parent[s] = s;
    q.push(s);
    
    bool found = false;
    while (!q.empty() && !found)
    {
        int curr = q.front();
        q.pop();
        
        for (AdjList* p = graph.adjList[curr]; p != nullptr; p = p->next)
        {
            if (p->weight >= M) // Chỉ đi qua cạnh có trọng số >= M
            {
                if (p->adjVertex == d)
                {
                    parent[d] = curr;
                    found = true;
                    break;
                }
                if (!visited[p->adjVertex])
                {
                    visited[p->adjVertex] = true;
                    parent[p->adjVertex] = curr;
                    q.push(p->adjVertex);
                }
            }
        }
    }
    
    if (found)
    {
        stack<int> st;
        int curr = d;
        while (curr != s)
        {
            st.push(curr);
            curr = parent[curr];
        }
        st.push(s);
        
        while (!st.empty())
        {
            path.push_back(st.top());
            st.pop();
        }
    }
    
    return path;
}

// l) Kiểm tra đồ thị có hướng liên thông mạnh
bool strongConnected(AdjListGraph graph)
{
    for (int i = 0; i < graph.numVertices; i++)
    {
        bool visited[MAX_VERTICES] = { false };
        queue<int> q;
        visited[i] = true;
        q.push(i);
        int count = 1;
        
        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            
            for (AdjList* p = graph.adjList[curr]; p != nullptr; p = p->next)
            {
                if (!visited[p->adjVertex])
                {
                    visited[p->adjVertex] = true;
                    q.push(p->adjVertex);
                    count++;
                }
            }
        }
        
        if (count != graph.numVertices)
            return false;
    }
    return true;
}

// m)
void findAllPathsUtil(AdjListGraph graph, int curr, int d, bool visited[], 
                     vector<int>& currentPath, vector<vector<int>>& allPaths)
{
    visited[curr] = true;
    currentPath.push_back(curr);
    
    if (curr == d)
    {
        allPaths.push_back(currentPath);
    }
    else
    {
        for (AdjList* p = graph.adjList[curr]; p != nullptr; p = p->next)
        {
            if (!visited[p->adjVertex])
            {
                findAllPathsUtil(graph, p->adjVertex, d, visited, currentPath, allPaths);
            }
        }
    }
    
    currentPath.pop_back();
    visited[curr] = false;
}

void allPaths(AdjListGraph graph, int s, int d, vector<vector<int>>& paths)
{
    bool visited[MAX_VERTICES] = { false };
    vector<int> currentPath;
    findAllPathsUtil(graph, s, d, visited, currentPath, paths);
}


int main()
{
    AdjListGraph g;
    readGraphFromFile(g, "Graph3.txt");
    printGraph(g);
    
    int parent[MAX_VERTICES];
    int s, d;
    cout << "Input start vertex: "; cin >> s;
    cout << "Input destination vertex: "; cin >> d;
    

    if (!hasPath(g, s, d))
    {
        cout << "No path exists from " << s << " to " << d << endl;
    }
    else
    {
        PathBFS(g, s, parent);
        cout << "A path from " << s << " to " << d << " using BFS is: ";
        printPath(parent, s, d);
        cout << endl;
        

        PathDFS(g, s, parent);
        cout << "A path from " << s << " to " << d << " using DFS is: ";
        if (parent[d] != -1)
        {
            printPath(parent, s, d);
        }
        else
        {
            cout << "No path found";
        }
        cout << endl;
    }
    
    bool connected = isConnected(g);
    if (connected)
        cout << "Graph is connected." << endl;
    else
        cout << "Graph is unconnected." << endl;
    
    int comp[MAX_VERTICES] = {-1};
    int k = connectedComponents(g, comp);
    printConnectedComponents(comp, g.numVertices, k);
    

    cout << "\n--- Testing extended functions ---" << endl;
    

    int avoid;
    cout << "Enter vertex to avoid: "; cin >> avoid;
    vector<int> pathAvoid = pathNoVertex(g, s, d, avoid);
    if (!pathAvoid.empty())
    {
        cout << "Path from " << s << " to " << d << " avoiding " << avoid << ": ";
        for (int v : pathAvoid) cout << v << " ";
        cout << endl;
    }
    else
    {
        cout << "No path from " << s << " to " << d << " avoiding " << avoid << endl;
    }
    

    int M;
    cout << "Enter minimum weight: "; cin >> M;
    vector<int> pathWeight = pathGreatThan(g, s, d, M);
    if (!pathWeight.empty())
    {
        cout << "Path from " << s << " to " << d << " using edges with weight >= " << M << ": ";
        for (int v : pathWeight) cout << v << " ";
        cout << endl;
    }
    else
    {
        cout << "No path from " << s << " to " << d << " using edges with weight >= " << M << endl;
    }
    

    if (strongConnected(g))
        cout << "Graph is strongly connected." << endl;
    else
        cout << "Graph is not strongly connected." << endl;
    

    vector<vector<int>> allPathsList;
    allPaths(g, s, d, allPathsList);
    cout << "All simple paths from " << s << " to " << d << ":" << endl;
    for (const auto& path : allPathsList)
    {
        for (int v : path) cout << v << " ";
        cout << endl;
    }
    
    return 0;
}
