#include <iostream>
#include <fstream>
#include <queue>
#include <limits>
using namespace std;

ifstream f("input.txt");

int n,mat[1001][1001],parinte[1001],cost[1001];
bool inCoada[1001];

/// pentru comparare
struct compara{
    bool operator()(int x,int y)
    {
        return cost[x] > cost[y];
    }
};

void afisare_ruta(int x)
{
    /// Functie de afisare recursiva a drumului
    if(parinte[x] != -1)
        afisare_ruta(parinte[x]);
    cout << x << " ";
}

void daijktra(int inc,int final_)
{
    for(int i=1;i<=n;i++)
    {
        inCoada[i] = false;
        cost[i] = INT_MAX;
        parinte[i] = -1;
    }

    cost[inc] = 0;
    parinte[inc] = -1;

    priority_queue<int,vector<int>,compara> q;
    q.push(inc);
    inCoada[inc] = true;

    while(!q.empty())
    {
        int actual = q.top();
        q.pop();

        for(int i=1;i<=n;i++)
            if(mat[actual][i] > 0 && cost[actual] + mat[actual][i] < cost[i])
            {
                parinte[i] = actual;
                cost[i] = cost[actual] + mat[actual][i];
                if(!inCoada[i])
                {
                    q.push(i);
                    inCoada[i] = true;
                }
            }

        // daca il scoatedm din coada vrem si variabila schimbata
        inCoada[actual] = false;
    }

    if(parinte[final_] != -1)
    {
        cout << "Drumul : ";
        afisare_ruta(final_);
        cout << endl << "Costul drumului : " << cost[final_];
    }
    else
    {
        cout << "Nu exista un drum de la nodul " << inc << " la " << final_ << "\n..";
    }
}

int main()
{
    int inc,sf;
    f >> n;
    f >> inc >> sf;
    int x,y,L;
    while(f >> x >> y >> L)
        mat[x][y] = L;

    daijktra(inc,sf);

    return 0;
}

/// INPUTURI :

/*
6
2 4
1 2 1
2 5 1
5 6 1
6 3 1
3 4 1
3 2 1

7
1 5
1 5 321320000
2 1 2
2 3 3
1 3 12
3 5 18
3 7 4
7 5 4

7
3 7
1 3 4
3 2 8
2 6 5
7 6 1
5 7 2

*/


