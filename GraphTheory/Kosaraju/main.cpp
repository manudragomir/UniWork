#include <iostream>
#include <vector>
#include <stack>
#include <fstream>

using namespace std;

ifstream fin("ctc.in");
ofstream fout("ctc.out");

const int NMax = 25;
vector < int > G[NMax], Gt[NMax], ctc[NMax];
stack < int > st;
int compo = 0;
int viz[NMax];

void DFS(int nod)
{
    viz[nod] = 1;
    for(auto vecin: G[nod])
    {
        if(!viz[vecin])
            DFS(vecin);
    }

    st.push(nod);
}

void DFSt(int nod)
{
    viz[nod] = 1;
    ctc[compo].push_back(nod);
    for(auto vecin: Gt[nod])
    {
        if(!viz[vecin])
            DFSt(vecin);
    }
}

int main()
{
    int V, E;
    fin >> V >> E;
    for(int i=1; i<=E; i++)
    {
        int v1, v2;
        fin >> v1 >> v2;
        G[v1].push_back(v2);
        Gt[v2].push_back(v1);
    }

    for(int i=1; i<=V; i++)
    {
        if(!viz[i])
        {
            DFS(i);
        }
    }

    for(int i=1; i<=V; i++)
        viz[i] = 0;

    while(!st.empty())
    {
        int nod = st.top();
        st.pop();
        if(viz[nod] == 1)
            continue;

        compo++;
        DFSt(nod);
    }

    for(int i=1; i<=compo; i++)
    {
        for(int j=0; j<ctc[i].size(); j++)
        {
            cout << ctc[i][j] << " ";
        }

        cout << "\n";
    }


    return 0;
}
