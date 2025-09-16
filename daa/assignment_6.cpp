#include<iostream>
#include<vector>
using namespace std;


/*
    Problem Statement:
        8-Queens problem using backtracing and branch & bound.
*/


class NQueens {
    private:
    int n;
    int count = 0;
    vector<vector<char>> board;

    void printBoard() {
        for(int x = 0; x < n; x++) {
            cout<<"             ";
            for(int y = 0; y < n; y++) {
                cout<<board[x][y]<<" ";
            }
            cout<<endl;
        }
        cout<<"--------------------------------------"<<endl;
    }

    bool isSafe(int row, int col) {        
        // column up check.
        for(int x = row - 1; x >= 0; x--) {
            if(board[x][col] == 'Q') return false;
        }
        // column down check.
        for(int x = row; x < n; x++) {
            if(board[x][col] == 'Q') return false;
        }

        // left diagonal up check.
        for(int x = row - 1, y = col - 1; x >= 0 && y >= 0; x--, y--) {
            if(board[x][y] == 'Q') return false;
        }
        // left diagonal down check.
        for(int x = row + 1, y = col - 1; x < n && y >= 0; x++, y--) {
            if(board[x][y] == 'Q') return false;
        }

        // right diagonal up check.
        for(int x = row - 1, y = col + 1; x >= 0 && y < n; x--, y++) {
            if(board[x][y] == 'Q') return false;
        }
        // right diagonal down check;
        for(int x = row + 1, y = col + 1; x < n && y < n; x++, y++) {
            if(board[x][y] == 'Q') return false;
        }

        return true;
    }

    bool containsQueenInRow(int row) {
        for(int x = 0; x < n; x++) {
            if(board[row][x] == 'Q') return true;
        }
        return false;
    }

    public:
        NQueens() {
            cout<<"Enter the board size: ";
            cin>>n;
            board = vector<vector<char>>(n, vector<char>(n, '*'));        
            cout<<"Enter the (row, column) to place the first queen: ";
            int row, col;
            cin>>row;
            cin>>col;
            board[row][col] = 'Q';
            cout<<"************* Current Board *************"<<endl;                  
            printBoard();         
        }

        void placeQueens(int row) {
            if(row == n) {
                printBoard();
                count++;
            }
            else {
                if(containsQueenInRow(row)) {
                    placeQueens(row + 1);
                }
                else {
                    for(int y = 0; y < n; y++) {
                        if(isSafe(row, y)) {
                            board[row][y] = 'Q';
                            placeQueens(row + 1);
                            board[row][y] = '*';
                        } 
                    }               
                }                
            }
        }

        void displaySolutionCount() {
            cout<<"Total no. of solutions: "<<count<<endl;
        }
};

int main() {

    NQueens nq = NQueens();
    cout<<"**************** Solution ****************"<<endl;
    nq.placeQueens(0);
    nq.displaySolutionCount();
    cout<<"******************************************"<<endl;

}