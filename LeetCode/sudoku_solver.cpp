/*
 * author:	luo feng
 * date:	2013/12/18
 * source:	LeetCode OJ
 * title:	Sudoku Solver
 * language:	C++
 */

#include <iostream>
#include <fstream>
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
    vector<vector<char> > flag;
    bool finish;

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
            if(board[s_ln][s_col] == digit && (s_ln < ln || s_col < col || flag[s_ln][s_col] == 1))
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
            if(board[i][col] == digit && (i < ln || flag[i][col] == 1) ||
               board[ln][i] == digit && (i < col || flag[ln][i] == 1)) {
                return 0;
            }
        }

        return 1;
    }

    void place_digit(vector<vector<char> > &board, int ln, int col)
    {
        if(ln == MAXN && col == MAXN) {
            finish = true;
            return;
        }

        int next_ln = 0, next_col = 0;
        get_next(ln, col, next_ln, next_col);

        if(flag[ln][col] == 1) {
            place_digit(board, next_ln, next_col);
            return;
        }

        char digit = 0;
        for(digit = '1'; digit <= '9'; ++digit) {
            board[ln][col] = '.';
            if(!in_square(board, ln, col, digit) && is_valid(board, ln, col, digit)) {
                board[ln][col] = digit;
                place_digit(board, next_ln, next_col);
                if(finish)
                    return;
            }
            board[ln][col] = '.';
        }
    }

    void set_flag(vector<vector<char> > &board)
    {
        int i = 0, j = 0;
        vector<char> cf;

        for(i = 0; i < MAXN; ++i) {
            cf.clear();
            for(j = 0; j < MAXN; ++j) {
                if(board[i][j] != '.') {
                    cf.push_back(1);
                }
                else {
                    cf.push_back(0);
                }
            }
            flag.push_back(cf);
        }
    }

    void solveSudoku(vector<vector<char> > &board)
    {
        finish = false;
        set_flag(board);
        place_digit(board, 0, 0);
    }
};

int main(int argc, char *argv[])
{
    vector<vector<char> > board;
    set_sudoku(board);
    for_each(board.begin(), board.end(), print_sudoku);
    cout << endl;
    Solution sol;
    sol.solveSudoku(board);
    for_each(board.begin(), board.end(), print_sudoku);

    return 0;
}
