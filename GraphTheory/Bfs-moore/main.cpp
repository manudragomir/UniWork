#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

const int Nmax = 50;
const int inf = 0x3f3f3f3f;

ifstream fin("in.txt");

void Moore(vector < int > G[], int nodes, int start, int dist[], int parinte[])
{
    queue < int > Q;
    for(int i=1; i<=nodes; i++)
    {
        dist[i] = inf;
        parinte[i] = 0;
    }

    dist[start] = 0;
    Q.push(start);
    while(!Q.empty())
    {
        int nod = Q.front();
        Q.pop();
        for(auto it: G[nod])
            if(dist[it] == inf)
            {
                dist[it] = dist[nod] + 1;
                parinte[it] = nod;
                Q.push(it);
            }
    }
}

void Moore_Drum(int parinte[], int fina)
{
    if(fina == 0)
        return;

    Moore_Drum(parinte, parinte[fina]);
    cout << fina << " ";

}

int main()
{
    vector < int > G[Nmax];
    int nodes, n1, n2, fina;
    int dist[Nmax], parinte[Nmax];
    fin >> nodes;
    while(fin >> n1 >> n2)
    {
        G[n1].push_back(n2);
        G[n2].push_back(n1);
    }

    int start;

    cin >> start >> fina;
    Moore(G, nodes, start, dist, parinte);

    cout << "Distanta e: " << dist[fina] << "\n";

    Moore_Drum(parinte, fina);


    return 0;
}
