/*
 * author:	luo feng
 * date:	2014/3/20
 * source:	Jobdu OJ
 * title:	excel sort
 * language:	C++
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

struct student {
	string id;
	string name;
	unsigned int remark;
};

ostream& operator<<(ostream &out, student stu)
{
	out << stu.id << " " << stu.name << " " << stu.remark;
	return out;
}

struct compare_id {
	bool operator()(student x, student y)
	{
		return x.id < y.id;
	}
};

struct compare_name {
	bool operator()(student x, student y)
	{
		if(x.name == y.name) {
			return x.id < y.id;
		}
		else {
			return x.name < y.name;
		}
	}
};

struct compare_remark {
	bool operator()(student x, student y)
	{
		if(x.remark == y.remark) {
			return x.id < y.id;
		}
		else {
			return x.remark < y.remark;
		}
	}
};

int main()
{
	unsigned long records = 0;
	unsigned int c = 0;
	unsigned int cnt = 0;
	vector<student> svec;
	student stu;
	int index = 0;

    ifstream cin("luo.txt");
	while(cin >> records >> c, records && c) {
		svec.resize(records);
		index = 0;
		while(index < records) {
			cin >> svec[index].id >> svec[index].name >> svec[index].remark;
			++index;
		}
		switch(c) {
			case 1:
			    sort(svec.begin(), svec.end(), compare_id());
			    break;
			case 2:
			    sort(svec.begin(), svec.end(), compare_name());
			    break;
			case 3:
			    sort(svec.begin(), svec.end(), compare_remark());
			    break;
			default:
			    break;
		}
		cout << "Case " << ++cnt << ":" << endl;
		copy(svec.begin(), svec.end(), ostream_iterator<student>(cout, "\n"));
		svec.clear();
	}

	return 0;
}