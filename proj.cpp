#include <bits/stdc++.h>
using namespace std;

#define N 9

/* functions needed:
    solve the actual puzzle using a Backtracking Algorithm and the rest of the functions (solve)
    check if the proposed number is a valid entry (validate)
    see if the board is solved (is_solved)
    find an empty position in the grid (find_empty)
    something to print the board in a nice format (print_board) */

//declaring all our functions on top
bool solve(vector<vector<int>> &board);
bool is_solved(vector<vector<int>> board);
vector<int> find_empty(vector<vector<int>> board);
bool validate(vector<vector<int>> board, int num, vector<int> pos);
void print_board(vector<vector<int>> board);

//main: board goes here along with two function calls
int main() {
    vector<vector<int>> board = {
   {9,8,4,0,0,0,5,0,1},
   {0,0,0,5,0,0,0,0,7},
   {0,0,0,0,0,0,0,0,9},
   {0,0,0,0,1,0,0,0,0},
   {0,2,0,7,0,3,1,0,0},
   {5,6,0,0,0,0,0,0,0},
   {8,0,0,0,0,0,4,9,6},
   {0,0,0,0,9,0,0,0,0},
   {1,0,0,2,8,0,0,0,0}
};
    solve(board);
    print_board(board);
}

/*the juicy bit: the steps simply involve
    finding an empty position
    try to fill it in with digits 1-9
    if a digit is valid, try to complete the board; else try another guess
        if our guesses are exhausted, there was a mistake with a previous guess, so the program backtracks its steps
    keep doing this until the board is solved*/
bool solve(vector<vector<int>> &board) {
    if (is_solved(board))
        return true;
    vector<int> pos = find_empty(board);
    int row = pos[0], col = pos[1];
    //looping through possible elements and checking if valid
    for(int i=1;i<=9;i++) {
        if (validate(board,i,pos)) {
            board[row][col] = i;
            //recursive step
            if (solve(board))
                return true;
            //incorrect guesses are made zero again
            board[row][col] = 0;
        }
    }
    return false;
}
//just an additional function to print the actual board
void print_board(vector<vector<int>> board) {
	for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

//is_solved checks if the board is solved by looking for empty elements in the grid
bool is_solved(vector<vector<int>> board) {
    for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++) {
            if (board[i][j]==0)
                return false;
        }
    }
    return true;
}

//find_empty will loop through all positions in the grid to find an empty(zero) element
//use this function iff the board is not solved (is_solved is false)
vector<int> find_empty(vector<vector<int>> board) {
    vector<int> pos;
    for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++) {
            if (board[i][j] == 0) {
                pos.push_back(i);
                pos.push_back(j);
                return pos;
            }  
        }
    }
}

/*to see if a number is a candidate for a certain position in the grid, check all numbers in the same row, column and 'box'  
  (following the rules of Sudoku) and make sure the candidate is unique in that regard
  This function needs the board, number to test and the position to test the number in */
bool validate(vector<vector<int>> board, int num, vector<int> pos) {
    int row = pos[0];
    int col = pos[1];
    //check row
    for (int i=0;i<N;i++) {
        if (board[row][i] == num && i!=col)
            return false;
    }
    //check column
    for (int i=0;i<N;i++) {
        if (board[i][col] == num && i!=row)
            return false;
    }
    //check the 'box' (trickiest one to check)
    //use floor division to divide the board into 'boxes' then loop through the rows and columns in each box
    /*for example: the top-right box would have rows 0,1,2 (floor division by 3 gives 0 for all row indices)
    and columns 6,7,8 (floor division by 3 gives 2 for all column indices)- we loop through the floordiv*3 (+3) */
    int box_start_row = pos[0]/3;
    int box_start_col = pos[1]/3;
    for (int i=box_start_row*3;i<box_start_row*3+3;i++) {
        for (int j=box_start_col*3;j<box_start_col*3+3;j++) {
            if (board[i][j]==num && i!=pos[0] && j!=pos[1])
                return false;
        }
    }

    return true;
}