/*
 * author:	luo feng
 * date:	2013/12/18
 * source:	LeetCode OJ
 * title:	Sudoku Solver
 * language:	C++
 */

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include <map>
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

void print_comple(pair<pair<int, int>, string> pp)
{
    cout << pp.first.first << " " << pp.first.second << " : " << pp.second << endl; 
}

class Solution {
public:
    static const int MAXN = 9;
    static const int TRI = 3;
    int sol_cnt;
    vector<vector<char> > flag;
    map<pair<int, int>, string> comple;

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

    void set_implicit(vector<vector<char> > &board)
    {
        char digit = 0;
        int ln = 0, col = 0;
        int cnt = 0;
        map<pair<int, int>, string>::iterator iter = comple.begin();

        for(ln = 0; ln < MAXN; ++ln) {
            while((*iter).first.first == ln) {
                for(digit = '1'; digit <= '9'; ++digit) {
                }
                ++iter;
            }
        }
    }

    //用刚填入的数字排除行、列、宫的余集
    void set_exclude(vector<vector<char> > &board, int ln, int col)
    {
        map<pair<int, int>, string>::iterator iter;
        size_t pos = 0;
        int ln_tmp = 0, col_tmp = 0;

        for(iter = comple.begin(); iter != comple.end(); ++iter) {
            ln_tmp = iter->first.first;
            col_tmp = iter->first.second;
            if(ln_tmp == ln && (pos = (*iter).second.find(board[ln][col])) != string::npos) {
                (*iter).second.erase(pos, 1);
            }
            if(col_tmp == col && (pos = (*iter).second.find(board[ln][col])) != string::npos) {
                (*iter).second.erase(pos, 1);
            }
        }

        int s_ln = (ln / TRI) * TRI, s_col = (col / TRI) * TRI;
        int next_ln = 0, next_col = 0;
        int cnt = 9;
        while(cnt--) {
            if(flag[s_ln][s_col] == 0) {
                iter = comple.find(make_pair(s_ln, s_col));
                if(iter != comple.end() && (pos = (*iter).second.find(board[ln][col])) != string::npos) {
                    (*iter).second.erase(pos, 1);
                }
            }
            get_next(s_ln, s_col, next_ln, next_col);
            s_ln = next_ln;
            s_col = next_col;
        }
    }

    //查找余集表，如果其中某个元素的余集只有一个元素，那么就设置该位置的值
    //并且将该元素对应的位置从余集表中删除
    bool get_one(vector<vector<char> > &board)
    {
        map<pair<int, int>, string>::iterator iter;
        int ln = 0, col = 0;

        for(iter = comple.begin(); iter != comple.end(); ++iter) {
            if((*iter).second.size() == 1) {
                ln = (iter->first).first;
                col = (iter->first).second;
                board[ln][col] = (iter->second)[0];
                flag[ln][col] = 1;
                comple.erase(iter);
                set_exclude(board, ln, col);
                return true;
            }
        }

        if(iter == comple.end())
            return false;
    }

    //初始化某个元素的余集
    void set_comple(vector<vector<char> > &board, pair<int, int> cell)
    {
        int i = 0;
        int ln = cell.first, col = cell.second;
        for(i = 0; i < MAXN; ++i) {
            if(flag[i][col] == 1 && comple[cell].find(board[i][col]) == string::npos) {
                comple[cell] += board[i][col];
            }

            if(flag[ln][i] == 1 && comple[cell].find(board[ln][i]) == string::npos) {
                comple[cell] += board[ln][i];
            }
        }

        int s_ln = (ln / TRI) * TRI, s_col = (col / TRI) * TRI;
        int next_ln = 0, next_col = 0;
        size_t pos = 0;
        int cnt = 9;
        while(cnt--) {
            if(flag[s_ln][s_col] == 1 && (pos = comple[cell].find(board[s_ln][s_col])) == string::npos) {
                comple[cell] += board[s_ln][s_col];
            }
            get_next(s_ln, s_col, next_ln, next_col);
            s_ln = next_ln;
            s_col = next_col;
        }

        char digit = 0;
        string str;
        for(digit = '1'; digit <= '9'; ++digit) {
            if((pos = comple[cell].find(digit)) == string::npos) {
                str += digit;
            }
        }
        comple[cell] = str;
    }

    //设置flag标志，并初始化余集
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
                    comple.insert(make_pair(make_pair(i, j), ""));
                }
            }
            flag.push_back(cf);
        }
        for(i = 0; i < MAXN; ++i) {
            for(j = 0; j < MAXN; ++j) {
                if(board[i][j] == '.') {
                    set_comple(board, make_pair(i, j));
                }
            }
        }
    }

    void solveSudoku(vector<vector<char> > &board)
    {
        sol_cnt = 0;
        set_flag(board);
        for_each(comple.begin(), comple.end(), print_comple);
        get_one(board);
        cout << endl;
        for_each(comple.begin(), comple.end(), print_comple);
        while(comple.size() && get_one(board)) {
            for_each(comple.begin(), comple.end(), print_comple);
            cout << endl;
        }
        for_each(comple.begin(), comple.end(), print_comple);
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
    //cout << sol.sol_cnt << endl;

    return 0;
}
