#include <iostream>
#include <fstream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

#define MAX_VERTICES 100

struct AdjMatrixGraph
{
    int numVertices;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
};

void readGraphFromFile(string fileName, AdjMatrixGraph &graph)
{
    ifstream file(fileName);
    file >> graph.numVertices;
    
    for (int i = 0; i < graph.numVertices; i++)
    {
        for (int j = 0; j < graph.numVertices; j++)
        {
            file >> graph.adjMatrix[i][j];
        }
    }
    file.close();
}

void printGraph(AdjMatrixGraph graph)
{
    cout << "Num of vertices: " << graph.numVertices << endl;
    for (int i = 0; i < graph.numVertices; i++)
    {
        for (int j = 0; j < graph.numVertices; j++)
        {
            cout << graph.adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


void DFS(const AdjMatrixGraph& graph, int vertex, bool visited[])
{
    visited[vertex] = true;
    cout << vertex << " ";
    
    for (int i = 0; i < graph.numVertices; i++)
    {
        if (graph.adjMatrix[vertex][i] != 0 && !visited[i])
        {
            DFS(graph, i, visited);
        }
    }
}


void DFS_Weighted(const AdjMatrixGraph& graph, int vertex, bool visited[])
{
    visited[vertex] = true;
    cout << vertex << " ";
    

    for (int i = 0; i < graph.numVertices; i++)
    {
        if (graph.adjMatrix[vertex][i] != 0 && !visited[i])
        {
            DFS_Weighted(graph, i, visited);
        }
    }
}


void traverseGraph(AdjMatrixGraph g)
{
    bool visited[MAX_VERTICES];
    memset(visited, false, sizeof(visited));
    
    cout << "Duyet toan bo do thi: ";
    for (int i = 0; i < g.numVertices; i++)
    {
        if (!visited[i])
        {
            cout << "\nThanh phan lien thong bat dau tu dinh " << i << ": ";
            DFS(g, i, visited);
        }
    }
    cout << endl;
}


void BFS(const AdjMatrixGraph& graph, int vertex)
{
    queue<int> q;
    bool visited[MAX_VERTICES];
    memset(visited, false, sizeof(visited));
    
    visited[vertex] = true;
    q.push(vertex);
    
    cout << "BFS tu dinh " << vertex << ": ";
    while (!q.empty())
    {
        int currVertex = q.front();
        cout << currVertex << " ";
        q.pop();
        
        for (int i = 0; i < graph.numVertices; i++)
        {
            if (graph.adjMatrix[currVertex][i] != 0 && !visited[i])
            {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    cout << endl;
}


int countEdges(AdjMatrixGraph g)
{
    int count = 0;

    for (int i = 0; i < g.numVertices; i++)
    {
        for (int j = i + 1; j < g.numVertices; j++)
        {
            if (g.adjMatrix[i][j] != 0)
            {
                count++;
            }
        }
    }
    return count;
}


int countIncomingEdges(AdjMatrixGraph g, int x)
{
    int count = 0;

    for (int i = 0; i < g.numVertices; i++)
    {
        if (g.adjMatrix[i][x] != 0)
        {
            count++;
        }
    }
    return count;
}


void notAdjacent(AdjMatrixGraph g, int x)
{
    cout << "Cac dinh khong ke voi dinh " << x << ": ";
    for (int i = 0; i < g.numVertices; i++)
    {

        if (i != x && g.adjMatrix[x][i] == 0)
        {
            cout << i << " ";
        }
    }
    cout << endl;
}

void notVisited(AdjMatrixGraph g, int x)
{
    bool visited[MAX_VERTICES];
    memset(visited, false, sizeof(visited));

    DFS(g, x, visited);
    
    cout << "\nCac dinh khong tham duoc tu dinh " << x << ": ";
    for (int i = 0; i < g.numVertices; i++)
    {
        if (!visited[i])
        {
            cout << i << " ";
        }
    }
    cout << endl;
}


bool isPath(AdjMatrixGraph g, int arr[], int k)
{

    for (int i = 0; i < k - 1; i++)
    {
        if (g.adjMatrix[arr[i]][arr[i + 1]] == 0)
        {
            return false; 
        }
    }
    return true;
}


void pathToVertex(AdjMatrixGraph g, int x)
{
    cout << "Cac dinh co the den duoc dinh " << x << ": ";
    
    for (int i = 0; i < g.numVertices; i++)
    {
        if (i != x)
        {
            bool visited[MAX_VERTICES];
            memset(visited, false, sizeof(visited));
            

            queue<int> q;
            q.push(i);
            visited[i] = true;
            bool canReach = false;
            
            while (!q.empty() && !canReach)
            {
                int curr = q.front();
                q.pop();
                
                if (curr == x)
                {
                    canReach = true;
                    break;
                }
                
                for (int j = 0; j < g.numVertices; j++)
                {
                    if (g.adjMatrix[curr][j] != 0 && !visited[j])
                    {
                        visited[j] = true;
                        q.push(j);
                    }
                }
            }
            
            if (canReach)
            {
                cout << i << " ";
            }
        }
    }
    cout << endl;
}

int main()
{
    AdjMatrixGraph g;
    bool visited[MAX_VERTICES];
    
    // Đọc và in đồ thị
    readGraphFromFile("Graph1.txt", g);
    printGraph(g);
    

    cout << "=== TEST CAC HAM ===" << endl;
    

    memset(visited, false, sizeof(visited));
    cout << "DFS tu dinh 0: ";
    DFS(g, 0, visited);
    cout << endl;
    
    // BFS từ đỉnh 0
    BFS(g, 0);
    
    // Duyệt toàn bộ đồ thị
    traverseGraph(g);
    
    // Đếm số cạnh
    cout << "So canh cua do thi vo huong: " << countEdges(g) << endl;
    
    // Đếm cạnh vào đỉnh 1
    cout << "So canh vao dinh 1: " << countIncomingEdges(g, 1) << endl;
    
    // Đỉnh không kề với đỉnh 0
    notAdjacent(g, 0);
    
    // Đỉnh không thăm được từ đỉnh 0
    notVisited(g, 0);
    
    // Test đường đi
    int path[] = {0, 1, 2};
    cout << "Day 0->1->2 co phai la duong di: " << (isPath(g, path, 3) ? "Co" : "Khong") << endl;
    
    // Đỉnh có thể đến đỉnh 2
    pathToVertex(g, 2);
    
    return 0;
}
