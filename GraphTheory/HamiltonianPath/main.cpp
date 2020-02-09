#include <iostream>

using namespace std;

const int NMax = 15;

bool checkHamiltonian(int adj[NMax][NMax], int N){
    int dp[1<<NMax][NMax];
    for(int i = 0; i < (1<<N); i++){
        for(int j = 0; j < N; j++){
            dp[i][j] = 0;
        }
    }

    for(int i = 0; i < N; i++){
        dp[1<<i][i] = 1;
    }

    for(int mask = 0; mask < (1<<N); ++mask){
        for(int wOut = 0; wOut < N; ++wOut){

                for(int nextNode = 0; nextNode < N; ++nextNode){

                }
        }
    }

}

int main()
{

    return 0;
}
