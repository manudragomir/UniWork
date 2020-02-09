#include <iostream>
#include <queue>
#include <vector>
#include <fstream>

using namespace std;

const int NMax = 30;
const int inf = 0x3f3f3f3f;

void Dijkstra(vector < pair < int, int > > G[], int d[], int N, int edges, int source)
{
    for(int i=1; i<=N; i++)
        d[i] = inf;

    d[source] = 0;
    priority_queue < pair < int, int > > Q;
    Q.push({0,source});
    while(!Q.empty())
    {
        int nodc = Q.top().second;
        int cost = -Q.top().first;
        Q.pop();

        if(cost > d[nodc])
            continue;

        for(auto it: G[nodc])
        {
            if(d[it.first] > cost + it.second)
            {
                d[it.first] = cost + it.second;
                Q.push({-d[it.first], it.first});
            }
        }
    }
}


bool BellmanFord(vector < pair < int, pair < int, int > > > muchii, int d[], int N, int edges, int source)
{
    for(int i=1; i<=N; i++)
        d[i] = inf;

    d[source] = 0;
    for(int i=1; i < N; i++)
        for(int j=0; j<muchii.size(); j++)
        {
            int nodc, nodu, cost;
            nodc = muchii[j].first;
            nodu = muchii[j].second.first;
            cost = muchii[j].second.second;
            if(d[nodu] > d[nodc] + cost)
                d[nodu] = d[nodc] + cost;
        }

    for(int j=0; j<muchii.size(); j++)
    {
        int nodc, nodu, cost;
        nodc = muchii[j].first;
        nodu = muchii[j].second.first;
        cost = muchii[j].second.second;
        if(d[nodu] > d[nodc] + cost)
            return false;
    }

    return true;
}


int main()
{

    int N, M;
    ifstream fin("fisi.txt");
    vector < pair < int, int > > G[NMax];
    vector < pair < int, pair < int, int > > >  muchii;
    fin >> N >> M;
    for(int i=1; i<=M; i++)
    {
        int n1, n2, c;
        fin >> n1 >> n2 >> c;
        G[n1].push_back({n2,c});
        G[n2].push_back({n1,c});

        muchii.push_back({n1,{n2,c}});
    }

    int d[NMax+1];
    //Dijkstra(G, d, N, M, 3);
    for(int i=1; i<=N; i++)
        cout << d[i] << " ";

    cout << "\n";

    int b[NMax+1];
    bool check = BellmanFord(muchii, b, N, M, 1);

    if(check == true)
    {
        for(int i=1; i<=N; i++)
            cout << b[i] << " ";
    }

    else
        cout << "Ciclu negativ!";

    return 0;
}
