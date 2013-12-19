/*
 * author:	luo feng
 * date:	2013/12/19
 * source:	LeetCode OJ
 * title:	Valid Sudoku
 * language:	C++
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
using namespace std;

void set_sudoku(vector<vector<char> > &board)
{
    ifstream is("../../current/sudoku");
    vector<char> ln;
    int i = 9, j = 9;
    while(i--) {
        ln.clear();
        j = 9;
        while(j--) {
            ln.push_back(is.get());
        }
        board.push_back(ln);
    }
}

void print_cell(char ch)
{
    cout << ch << " ";
}

void print_sudoku(vector<char> ln)
{
    for_each(ln.begin(), ln.end(), print_cell);
    cout << endl;
}

class Solution {
public:
    static const int MAXN = 9;
    static const int TRI = 3;

    void get_next(int ln, int col, int &next_ln, int &next_col)
    {
        if(!((ln + 1) % TRI) && !((col + 1) % TRI)) {
            if(ln + 1 == MAXN && col + 1 == MAXN) {
                next_ln = ln + 1;
                next_col = col + 1;
            }
            else if(ln + 1 != MAXN && col + 1 == MAXN) {
                next_ln = ln + 1;
                next_col = 0;
            }
            else {
                next_ln = ln - 2;
                next_col = col + 1;
            }
        }
        else if(((ln + 1) % TRI) && !((col + 1) % TRI)) {
            next_ln = ln + 1;
            next_col = col - 2;
        }
        else {
            next_ln = ln;
            next_col = col + 1;
        }
    }

    int in_square(vector<vector<char> > &board, int ln, int col, char digit)
    {
        int s_ln = (ln / TRI) * TRI, s_col = (col / TRI) * TRI;
        int next_ln = 0, next_col = 0;
        int cnt = 9;

        while(cnt--) {
            if(board[s_ln][s_col] == digit && s_ln != ln && s_col != col)
                return 1;
            get_next(s_ln, s_col, next_ln, next_col);
            s_ln = next_ln;
            s_col = next_col;
        }

        return 0;
    }

    int is_valid(vector<vector<char> > &board, int ln, int col, char digit)
    {
        int i = 0;

        for(i = 0; i < MAXN; ++i) {
            if(board[i][col] == digit && i != ln ||
               board[ln][i] == digit && i != col) {
                return 0;
            }
        }

        return 1;
    }

    bool isValidSudoku(vector<vector<char> > &board)
    {
        int i = 0, j = 0;
        
        for(i = 0; i < MAXN; ++i) {
            for(j = 0; j < MAXN; ++j) {
                if(board[i][j] != '.' && (in_square(board, i, j, board[i][j]) || !is_valid(board, i, j, board[i][j]))) {
                   cout << i << " " << j << board[i][j] << endl;
                   return false;
                }
            }
        }
        
        return true;
    }
};

int main(int argc, char *argv[])
{
    vector<vector<char> > board;
    set_sudoku(board);
    for_each(board.begin(), board.end(), print_sudoku);
    cout << endl;
    Solution sol;
    cout << boolalpha <<sol.isValidSudoku(board) << endl;

    return 0;
}
