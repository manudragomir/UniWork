///Check wheter a given graph is Bipartite
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

bool BFS(vector < int > G[], int nod, int viz[])
{
    viz[nod] = 1;
    queue < pair < int, int > > Q;
    Q.push({nod,1});
    while(!Q.empty())
    {
        int nod_act = Q.front().first;
        int place = Q.front().second;
        int next;

        if(place == 1)
            next = 2;
        else
            next = 1;

        Q.pop();

        for(auto it: G[nod_act])
        {
            if(viz[it] != 0 && viz[it] != next)
                return false;

            if(!viz[it])
            {
                viz[it] = next;
                Q.push({it,next});
            }
        }
    }


    return true;

}

bool Iterate(vector < int > G[], int nodes)
{
    int viz[20];
    for(int i=1; i<=nodes; i++)
        viz[i] = 0;

    bool check = true;
    for(int i=1; i<=nodes && check ; i++)
        if(!viz[i])
            check = BFS(G,i,viz);

    return check;
}

int main()
{
    ifstream fin("input.in");
    int T;
    fin >> T;
    for(int i=1; i<=T; i++)
    {
        int nodes;
        vector < int > G[20];
        fin >> nodes;
        for(int j=1; j<=nodes; j++)
        {
            for(int k=1; k<=nodes; k++)
            {
                int tr;
                fin >> tr;
                if(tr == 1)
                    G[j].push_back(k);
            }
        }

        bool check = Iterate(G, nodes);
        if(check == true)
            cout << 1 << "\n";
        else
            cout << 0 << "\n";
    }

    return 0;
}
