#include<iostream>
using namespace std;


/*
    Problem Statement:
        8-Queens problem using backtracing and branch & bound.
*/


class NQueens {
    private:
    int n;
    vector<vector<char>> board;

    void printBoard() {
        for(int x = 0; x < n; x++) {
            cout<<"             ";
            for(int y = 0; y < n; y++) {
                cout<<board[x][y]<<" ";
            }
            cout<<endl;
        }
    }

    bool isSafe(int row, int col) {
        // column check.
        for(int x = row - 1; x >= 0; x--) {
            if(board[x][col] == 'Q') return false;
        }

        // left diagonal check.
        for(int x = row - 1, y = col - 1; x >= 0 && y >= 0; x--, y--) {
            if(board[x][y] == 'Q') return false;
        }

        // right diagonal check.
        for(int x = row - 1, y = col + 1; x >= 0 && y < n; x--, y++) {
            if(board[x][y] == 'Q') return false;
        }

        return true;
    }

    public:
        NQueens() {
            cout<<"Enter the board size: ";
            cin>>n;
            board = vector<vector<char>>(n, vector<char>(n, '*'));        
        }

        bool placeQueens(int row) {
            if(row == n) {
                printBoard();
                return true;
            }
            else {
                for(int x = row; x < n; x++) {
                    for(int y = 0; y < n; y++) {
                        if(isSafe(x, y)) {
                            board[x][y] = 'Q';
                            if(placeQueens(row + 1)) return true;
                            board[x][y] = '*';
                        }
                    }
                }
                return false;
            }
        }
};

int main() {

    NQueens nq = NQueens();
    cout<<"**************** Solution ****************"<<endl;
    nq.placeQueens(0);
    cout<<"******************************************"<<endl;

}