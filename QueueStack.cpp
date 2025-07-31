
#include<bits/stdc++.h>
#define endl "\n"
using namespace std;

void printStack(stack<int> s){
    while (!s.empty()){
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
}

void printQueue(queue<int> q){
    while (!q.empty()){
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}

int popK(queue<int> &q, int k){
    queue<int> tmp;

    for(int i = 1; i<k; i++){
        tmp.push(q.front());
        q.pop();
    }

    int x = q.front();
    q.pop();

    while (!q.empty()){
        tmp.push(q.front());
        q.pop();
    }

    while (!tmp.empty()){
        q.push(tmp.front());
        tmp.pop();
    }

    return x;
}

void insertAtK(stack<int> &s, int value, int k){
    stack<int> temp;

    // step 1: pop k-1
    for(int i = 1; i < k; i++){
        temp.push(s.top());
        s.pop();
    }

    s.push(value);

    for (int i = 1; i < k; i++){
        s.push(temp.top());
        temp.pop();
    }
}

void reverseQueue(queue<int> &q){
    stack<int> s;

    while(!q.empty()){
        s.push(q.front());
        q.pop();
    }

    while (!s.empty()){
        q.push(s.top());
        s.pop();
    }
}

int findMin(stack<int> &s){
    if (s.empty()){
        return -1;
    }

    stack<int> temp;
    int minVal = s.top();

    while (!s.empty()){
        int cur = s.top();
        s.pop();

        if (cur < minVal)
            minVal = cur;
    }

    return minVal;

}

void sortQueueAsc(queue<int> &q){
    vector<int> temp;
    while (!q.empty()){
        temp.push_back(q.front());
        q.pop();
    }

    sort(temp.begin(), temp.end());

    for (int i = 0; i < temp.size(); i++)
        q.push(temp[i]);
}

int main(){
    queue<int> q;
    q.push(5); q.push(3); q.push(2); q.push(8); q.push(7);

    printQueue(q);


    int a = popK(q, 2);

    cout << " phan tu thu K la: " << a << endl;

    cout << "hang doi con lai: ";
    printQueue(q);

    stack<int> s;
    s.push(2); s.push(5); s.push(-7); s.push(8);
    insertAtK(s, 99, 2);
    printStack(s);

    reverseQueue(q);
    printQueue(q);

    cout << findMin(s) << endl;

    sortQueueAsc(q);
    printQueue(q);

}
