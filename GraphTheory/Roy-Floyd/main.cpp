
#include <iostream>
#include <queue>
#include <vector>
#include <fstream>

using namespace std;

const int Nmax = 50;

ifstream fin("in.txt");

void RoyFloyd(int m[Nmax][Nmax], int nodes)
{
    for(int k=1; k<=nodes; k++)
    {
        for(int i=1; i<=nodes; i++)
        {
            for(int j=1; j<=nodes; j++)
            {
                if(i!=k && i!=j && j!=k && m[i][k] && m[k][j])
                    m[i][j] = 1;
            }
        }
    }
}

void Init(int m[Nmax][Nmax], int nodes)
{
    for(int i=1; i<=nodes; i++)
        for(int j=1; j<=nodes; j++)
            m[i][j] = 0;
}

void Print(int m[Nmax][Nmax], int nodes)
{
    for(int i=1; i<=nodes; i++)
    {
        for(int j=1; j<=nodes; j++)
        {
            cout << m[i][j] << " ";
        }
        cout << "\n";
    }
}

int main()
{
    int nodes, n1, n2;
    int m[Nmax][Nmax];
    fin >> nodes;
    Init(m,nodes);
    while(fin >> n1 >> n2)
    {
        m[n1][n2] = 1;
    }

    RoyFloyd(m, nodes);
    Print(m, nodes);

    return 0;
}
