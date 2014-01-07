/*
 * author:	luo feng
 * date:	2013/12/19
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

    void solveSudoku(vector<vector<char> > &board)
    {
        int i = 0, j = 0;

        for(i = 0; i < MAXN; ++i) {
            for(j = 0; j < MAXN; ++j) {
                
            }
        }
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
