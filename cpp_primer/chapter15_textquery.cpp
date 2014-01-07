/*
 * author:	luo feng
 * date:	2013/12/10
 * source:	C++ Primer
 * info:	第15章15.9节再谈文本查询示例
 * language:	C++
 */

#include <iostream>
#include <stdexcept>
using namespace std;

class TextQuery {
public:
    typedef vector<string>::size_type line_no;

    void read_file(ifstream &is)
    { 
        store_file(is);
        build_map();
    }

    set<line_no> run_query(const string &) const;
    string text_line(line_no) const;
    void print_map();

private:

    void store_file(ifstream &);
    void build_map();
    vector<string> lines_of_text;
    map<string, set<line_no> > word_map;
};

void TextQuery::store_file(ifstream &is)
{
    string line;

    while(getline(is, line)) {
        lines_of_text.push_back(line);
    }
}

void TextQuery::build_map()
{
    istringstream iss;
    string word;
    line_no l_no = 1;

    for(vector<string>::iterator iter = lines_of_text.begin();
                                 iter != lines_of_text.end(); ++iter, ++l_no) {
        iss.str(*iter);
        while(iss >> word) {
            word_map[word].insert(l_no);
        }
        iss.clear();
    }
}

void TextQuery::print_map()
{
    cout << "map:" << endl;
    for(map<string, set<line_no> >::iterator iter = word_map.begin();
                                             iter != word_map.end(); ++iter) {
        cout << (*iter).first << ": ";
        for(set<line_no>::iterator siter = (*iter).second.begin();
                                   siter != (*iter).second.end(); ++siter) {
            cout << *siter << " ";
        }
        cout << endl;
    }
}

set<TextQuery::line_no> TextQuery::run_query(const string &str) const
{
    map<string, set<line_no> >::const_iterator loc = word_map.find(str);
    if(loc == word_map.end())
        return set<line_no>();
    else
        return loc->second;
}

string TextQuery::text_line(TextQuery::line_no l_no) const
{
    if(l_no < lines_of_text.size())
        return lines_of_text[l_no-1];
    throw out_of_range("line number out of range");
}

class Query_base

int main(int argc, char *argv[])
{
    

    return 0;
}
