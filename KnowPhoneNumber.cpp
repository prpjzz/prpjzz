#include <iostream>
#include <fstream>
#include <cstring>
#include <queue>
#include <vector>
#include <set>
using namespace std;

#define MAX_STUDENTS 100

struct PhoneGraph
{
    int numStudents;
    int adjMatrix[MAX_STUDENTS][MAX_STUDENTS];
};

// read file
void readPhoneGraphFromFile(string fileName, PhoneGraph &graph)
{
    ifstream file(fileName);
    file >> graph.numStudents;
    
    for (int i = 0; i < graph.numStudents; i++)
    {
        for (int j = 0; j < graph.numStudents; j++)
        {
            file >> graph.adjMatrix[i][j];
        }
    }
    file.close();
}

// print matrix
void printPhoneGraph(PhoneGraph graph)
{
    cout << "So sinh vien: " << graph.numStudents << endl;
    cout << "Ma tran biet so dien thoai:" << endl;
    for (int i = 0; i < graph.numStudents; i++)
    {
        for (int j = 0; j < graph.numStudents; j++)
        {
            cout << graph.adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// a)
bool knowsDirectly(PhoneGraph g, int x, int y)
{
    if (x < 0 || x >= g.numStudents || y < 0 || y >= g.numStudents)
        return false;
    
    return g.adjMatrix[x][y] == 1;
}

bool canReachDFS(PhoneGraph g, int start, int target, bool visited[])
{
    if (start == target)
        return true;
    
    visited[start] = true;
    
    for (int i = 0; i < g.numStudents; i++)
    {
        if (g.adjMatrix[start][i] == 1 && !visited[i])
        {
            if (canReachDFS(g, i, target, visited))
                return true;
        }
    }
    
    return false;
}

// b)
bool knowsDirectlyOrIndirectly(PhoneGraph g, int x, int z)
{
    if (x < 0 || x >= g.numStudents || z < 0 || z >= g.numStudents)
        return false;
    
    if (x == z)
        return true; 
    
    bool visited[MAX_STUDENTS];
    memset(visited, false, sizeof(visited));
    
    return canReachDFS(g, x, z, visited);
}

// c)
bool canKnowAllClassmates(PhoneGraph g, int x)
{
    if (x < 0 || x >= g.numStudents)
        return false;
    
    for (int i = 0; i < g.numStudents; i++)
    {
        if (i != x && !knowsDirectlyOrIndirectly(g, x, i))
        {
            return false;
        }
    }
    
    return true;
}

// d)
void studentsNoOneKnows(PhoneGraph g)
{
    cout << "Sinh vien ma khong ai biet so dien thoai: ";
    vector<int> result;
    
    for (int j = 0; j < g.numStudents; j++)
    {
        bool someoneKnows = false;
        for (int i = 0; i < g.numStudents; i++)
        {
            if (i != j && knowsDirectlyOrIndirectly(g, i, j))
            {
                someoneKnows = true;
                break;
            }
        }
        
        if (!someoneKnows)
        {
            result.push_back(j);
        }
    }
    
    if (result.empty())
    {
        cout << "Khong co sinh vien nao.";
    }
    else
    {
        for (int student : result)
        {
            cout << student << " ";
        }
    }
    cout << endl;
}

// e)
void studentsWhoKnowEveryone(PhoneGraph g)
{
    cout << "Sinh vien biet so dien thoai het ca lop: ";
    vector<int> result;
    
    for (int i = 0; i < g.numStudents; i++)
    {
        if (canKnowAllClassmates(g, i))
        {
            result.push_back(i);
        }
    }
    
    if (result.empty())
    {
        cout << "Khong co sinh vien nao.";
    }
    else
    {
        for (int student : result)
        {
            cout << student << " ";
        }
    }
    cout << endl;
}

// f)
void findMinimalSet(PhoneGraph g)
{
    cout << "Tim tap hop it sinh vien nhat biet het so dien thoai ca lop:" << endl;
    
   
    vector<set<int>> canReach(g.numStudents);
    
    for (int i = 0; i < g.numStudents; i++)
    {
        for (int j = 0; j < g.numStudents; j++)
        {
            if (knowsDirectlyOrIndirectly(g, i, j))
            {
                canReach[i].insert(j);
            }
        }
    }
    
  
    set<int> covered;
    vector<int> result;
    
    while (covered.size() < g.numStudents)
    {
        int bestStudent = -1;
        int maxNewCovered = 0;
        
       
        for (int i = 0; i < g.numStudents; i++)
        {
            int newCovered = 0;
            for (int j : canReach[i])
            {
                if (covered.find(j) == covered.end())
                {
                    newCovered++;
                }
            }
            
            if (newCovered > maxNewCovered)
            {
                maxNewCovered = newCovered;
                bestStudent = i;
            }
        }
        
        if (bestStudent == -1)
        {
           
            cout << "Khong the tim duoc tap hop de biet het so dien thoai ca lop." << endl;
            return;
        }
      
        result.push_back(bestStudent);
        for (int j : canReach[bestStudent])
        {
            covered.insert(j);
        }
    }
    
    cout << "Tap hop it nhat co " << result.size() << " sinh vien: ";
    for (int student : result)
    {
        cout << student << " ";
    }
    cout << endl;
    

    cout << "Chi tiet:" << endl;
    for (int student : result)
    {
        cout << "Sinh vien " << student << " co the biet so cua: ";
        for (int j : canReach[student])
        {
            cout << j << " ";
        }
        cout << endl;
    }
}

void testPhoneGraphFunctions(PhoneGraph g)
{
    cout << "=== TEST CAC CHUC NANG ===" << endl;
    
    // Test a)
    cout << "a) Sinh vien 0 co biet truc tiep so sinh vien 1: " 
         << (knowsDirectly(g, 0, 1) ? "Co" : "Khong") << endl;
    
    cout << "   Sinh vien 0 co biet truc tiep so sinh vien 2: " 
         << (knowsDirectly(g, 0, 2) ? "Co" : "Khong") << endl;
    
    // Test b)
    cout << "b) Sinh vien 0 co biet (truc tiep/gian tiep) so sinh vien 2: " 
         << (knowsDirectlyOrIndirectly(g, 0, 2) ? "Co" : "Khong") << endl;
    
    cout << "   Sinh vien 1 co biet (truc tiep/gian tiep) so sinh vien 3: " 
         << (knowsDirectlyOrIndirectly(g, 1, 3) ? "Co" : "Khong") << endl;
    
    // Test c)
    cout << "c) Sinh vien 0 co the biet het so ca lop: " 
         << (canKnowAllClassmates(g, 0) ? "Co" : "Khong") << endl;
    
    for (int i = 0; i < g.numStudents; i++)
    {
        cout << "   Sinh vien " << i << " co the biet het ca lop: " 
             << (canKnowAllClassmates(g, i) ? "Co" : "Khong") << endl;
    }
    
    // Test d)
    cout << "d) ";
    studentsNoOneKnows(g);
    
    // Test e)
    cout << "e) ";
    studentsWhoKnowEveryone(g);
    
    // Test f)
    cout << "f) ";
    findMinimalSet(g);
}

int main()
{
    PhoneGraph g;
    
    readPhoneGraphFromFile("phones.txt", g);
    printPhoneGraph(g);
    testPhoneGraphFunctions(g);
    
    return 0;
}
