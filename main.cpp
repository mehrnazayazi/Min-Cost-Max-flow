#include <iostream>
using namespace std;


int m, n;
int Head[80200], Cost[80200];
int End[80200], Cap[80200];
int Y[80200], Next[80200];
int p[80200], l[80200];
bool PathExists;
int minCost = 0;


void Dijkstra(){
    bool uncoloured[n];
    l[0] = 0;
    p[0] = 0;
    uncoloured [0] = true;
    for (int i = 1; i < n; ++i) {
        p[i] = 0;
        uncoloured[i] = true;
        l[i] = 20000;
    }
    bool uncoloured_exist = true;
    int u = 0;
    int counter = 0;
    while(uncoloured_exist){
        counter++;
        if(counter>m){
            PathExists = false;
            return;
        }
        uncoloured[u] = false;
        uncoloured_exist = false;
        int next = Y[u];
        while(next!=-1){
            if(Cap[next]!=0){
                int neighbor = End[next];
                if(uncoloured[neighbor]){
                    if(l[neighbor] > l[u]+ Cost[next]){
                        l[neighbor] = p[u] + Cost[next];
                        p[neighbor] = u;
                    }
                }
            }
            next = Next[next];
        }
        int min = 20000;
        for (int i = 0; i < n; ++i) {
            if(uncoloured[i]){
                uncoloured_exist = true;
                if(l[i] < min){
                    u = i;
                }
            }
        }
    }


}


void AddEdge(int head, int end, int cost, int cap, int name){
    int i = 0, next;
    Head[name] = head;
    End[name] = end;
    Cost[name] = cost;
    Cap[name] = cap;
    if( Y[head]== -1){
        Y[head] = name;
    }else{
        next = Next[Y[head]];
        while(next!= -1){//TODO change it to get back to head;
            next = Next[next];
        }
        Next[next] = name;
    }
}



/* main program for linked list*/
int main()
{

    int  x, y, w, c;
    cin >> n >> m ;
    for (int i = 0; i < n; ++i) {
        p[i] = -1;
    }
    for(int i=0; i < n; i++){
        Y[i] = -1;
    }
    for( int i=0; i < 2*m; i++){
        Next[i] = -1;
    }

    for (int i = 0; i < m ; ++i) {
        cin >> x >> y >> w, c;
        AddEdge(x, y, w, c, i);
        AddEdge(y, x, w, 0, m+i);
    }
    PathExists = true;
    int pathCost = 0, minCap = 20000;
    while(PathExists){
        Dijkstra();
        int i = n-1;
        while (i!=0){
            for(int j=0;j<m;j++){
                if(End[j] == i && Head[j]==p[i]){
                    if(Cap[j] < minCap){
                        minCap = Cap[j];
                    }
                    pathCost+=Cost[j];
                    break;
                }
            }
            i = p[i];
        }
        i = n-1;
        while(i != 0){
            for (int j = 0; j < 2*m ; ++j) {
                if(End[j] == i && Head[j]==p[i]){
                    Cap[j]-=minCap;
                }
                if(End[j] == p[i] && Head[j]== i){
                    Cap[j]+=minCap;
                }
            }
        }
        minCost+=(pathCost*minCap);
        for (int i = 0; i < 2*m; ++i) {
            Cost[i] = Cost[i]+ l[Head[i]] - l[End[i]];
        }
    }

    cout<< minCost;
    cout.flush();


    return 0;
}
