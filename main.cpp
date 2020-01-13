#include <iostream>
using namespace std;


int m2, n2;
int Head[80200], Cost[80200], BackupCost[80200];
int End[80200], Cap[80200];
int Y[80200], Next[80200];
int p[80200], l[80200];
bool PathExists;
int minCost = 0, flow2=0;


void Dijkstra2(){
    bool uncoloured[n2];
    l[0] = 0;
    p[0] = 0;
    uncoloured [0] = true;
    for (int i = 1; i < n2; ++i) {
        p[i] = 0;
        uncoloured[i] = true;
        l[i] = 20000;
    }
    bool uncoloured_exist = true;
    int u = 0;
    int counter = 0;
    while(uncoloured_exist){
        counter++;
        if(counter> 2 * m2){
            if(l[n2 - 1] < 20000){
                return;
            }
            PathExists = false;
            return;
        }
        uncoloured[u] = false;
        uncoloured_exist = false;
        int next = Y[u];
        while(next!=-1){
            if(u == 17 && End[next] == 26){
                cout<<"cap of edge: "<<Cap[next]<<endl;
            }
            if(Cap[next]!=0){
                int neighbor = End[next];
                if(uncoloured[neighbor]){
                    if(l[neighbor] > l[u]+ Cost[next]){
                        l[neighbor] = l[u] + Cost[next];
                        p[neighbor] = u;
                    }
                }
            }
            next = Next[next];
        }
        int min = 20000;
        for (int i = 0; i < n2; ++i) {
            if(uncoloured[i]){
                uncoloured_exist = true;
                if(l[i] < min){
                    min = l[i];
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
        int former = Y[head];
        int next = Next[former];
        while(next!= -1){//TODO change it to get back to head;
            former = next;
            next = Next[former];
        }
        Next[former] = name;
    }
}



/* main program for linked list*/
int main()
{

    int  x, y, w, c;
    cin >> n2 >> m2 ;
    for (int i = 0; i < n2; ++i) {
        p[i] = -1;
    }
    for(int i=0; i < n2; i++){
        Y[i] = -1;
    }
    for(int i=0; i < 2 * m2; i++){
        Next[i] = -1;
    }

    for (int i = 0; i < m2 ; ++i) {
        cin >> x >> y >> c>> w;
        AddEdge(x, y, w, c, i);
        AddEdge(y, x, -w, 0, m2 + i);
    }
    for (int k = 0; k < 2 * m2; ++k) {
        BackupCost[k] = Cost[k];
    }
    PathExists = true;
    int pathCost = 0, minCap = 20000;
    while(PathExists){
        int pathCost = 0;
        Dijkstra2();
        if(!PathExists){
            break;
        } else{
            int i = n2 - 1;
            while (i!=0){
                cout<<p[i]<<", ";
                cout.flush();
                i = p[i];
            }
            cout<<endl;
        }
        int i = n2 - 1;
        minCap = 200000;
        while (i!=0){
            for(int j=0;j< 2 * m2; j++){
                if(End[j] == i && Head[j]==p[i]){
                    if(Cap[j] < minCap){
                        minCap = Cap[j];
                        if(Cap[j] == 0){
                            cout<<"bottle neck= "<<Head[j]<<"-->>"<<End[j]<<endl;
                        }
                    }
                    pathCost+=BackupCost[j];
                    break;
                }
            }
            i = p[i];
        }
        cout<<"path min cap = "<< minCap<<endl;
        i = n2 - 1;
        while(i != 0){
            for (int j = 0; j < 2 * m2 ; ++j) {
                if(End[j] == i && Head[j]==p[i]){
                    Cap[j]-=minCap;
                }
                if(End[j] == p[i] && Head[j]== i){
                    Cap[j]+=minCap;
                }
            }
            i = p[i];
        }
        minCost+=(pathCost*minCap);
        flow2 += minCap;
        for (int i = 0; i < 2 * m2; ++i) {
                Cost[i] = Cost[i]+ l[Head[i]] - l[End[i]];
        }
    }

    cout<< "cost: "<<minCost<<endl;
    cout.flush();
    cout << "flow: " << flow2;
    cout.flush();


    return 0;
}
