/*
 * author:	luo feng
 * date:	2014/4/21
 * source:	Introduction to Algorithm
 * title:	DFS(graph)
 * info:	算法导论中图部分的深度优先搜索。主要的训练项目是：图的广度优先搜索的递归方式和非递归方式、拓扑排序。
 */

#include <iostream>
#include <climits>
#include <vector>
#include <list>
#include <stack>
#include <iterator>
using namespace std;

enum COLOR {
	WHITE, GRAY, BLACK
};

struct _gnode {
	int edge;
	struct _gnode *next;
	_gnode(int e) : edge(e), next(NULL) { }
};

struct _margin {
	_gnode *pg;
	_margin() : pg(NULL) { }
};

class graph {
	_margin *vetex;
	COLOR *color;
	int *parent;
	int *distance;
	size_t size;
	list<int> top_sort;

	void dfs_visit(int);
public:
	graph(int, vector<pair<int, int> >::iterator, vector<pair<int, int> >::iterator);
	~graph();
	void show();
	void traverse_dfs();
	void traverse_with_stack();
	void topological_sort();
	//void bfs_path(int, int);
};

// 图的构造函数，vetex_cnt是图的顶点个数，end - beg是边的个数，
// 当然，边的个数对于有向图和无向图不太一样，对于无向图而言，end - beg是边的个数的两倍
graph::graph(int vetex_cnt, vector<pair<int, int> >::iterator beg, vector<pair<int, int> >::iterator end)
{
	size = vetex_cnt;
	vetex = new _margin[size];
	color = new COLOR[size];
	parent = new int[size];
	distance = new int[size];
	for(int i = 0; i < size; ++i) {
		color[i] = WHITE;
		parent[i] = -1;
		distance[i] = INT_MAX;
	}
	pair<int, int> edge;
	_gnode *pg = NULL;
	_margin *head = NULL;

	while(beg != end) {
		edge = *beg;
		pg = new _gnode(edge.second);
		head = &vetex[edge.first];
		pg->next = head->pg;
		head->pg = pg;
		++beg;
	}
}

graph::~graph()
{
	int i = 0;
	_gnode *pg = NULL;

	for(i = 0; i < size; ++i) {
		pg = vetex[i].pg;
		while(pg) {
			vetex[i].pg = pg->next;
			delete pg;
			pg = vetex[i].pg;
		}
	}
	delete vetex;
}

void graph::show()
{
	int i = 0;
	_gnode *pg = NULL;

	for(i = 0; i < size; ++i) {
		pg = vetex[i].pg;
		if(pg) {
			cout << i << " has vetex: " << endl;
		}
		else {
			cout << i << " has no vetex" << endl;
		}
		while(pg) {
			cout << i << " -> " << pg->edge << endl;
			pg = pg->next;
		}
		cout << endl;
	}
}

void graph::dfs_visit(int start)
{
	color[start] = GRAY;
	//cout << "(" << start;
	//cout << start << endl;

	_gnode *pg = vetex[start].pg;
	int vet = 0;
	while(pg != NULL) {
		vet = pg->edge;
		if(color[vet] == WHITE) {
			cout << start << " -> " << vet << " is tree edge" << endl;
			parent[vet] = start;
			dfs_visit(vet);
		}
		else if(color[vet] == GRAY) {
			cout << start << " -> " << vet << " is Backward edge" << endl;
		}
		else if(color[vet] == BLACK) {
			cout << start << " -> " << vet << " is Forward edge or Cross edge" << endl;
		}
		pg = pg->next;
	}
	color[start] = BLACK;
	top_sort.push_front(start);
	//cout << start << ")";
}

// 图的递归访问
void graph::traverse_dfs()
{
	_gnode *pg = NULL;
	int i = 0;

	for(i = 0; i < size; ++i) {
		pg = vetex[i].pg;
		if(color[i] == WHITE) {
			//cout << i << endl;
			dfs_visit(i);
		}
	}
}

void graph::topological_sort()
{
	for(list<int>::iterator iter = top_sort.begin();
		                    iter != top_sort.end(); ++iter) {
		cout << *iter << " ";
	}
	cout << endl;
}

// 图的非递归遍历（使用栈）
// 发现使用栈来模拟递归时，不好判断某条边是否是第一次访问，此时可以使用multiset来保存已经访问的边。
// 因为判断某条边的类型时，是以该条边第一次访问时，顶点的颜色来判断该条边的类型。
void graph::traverse_with_stack()
{
	_gnode *pg = NULL;
	_gnode *tmp = NULL;
	int i = 0;
	stack<int> sta;

	for(i = 0; i < size; ++i) {
		pg = vetex[i].pg;
		if(color[i] == WHITE) {
			color[i] = GRAY;
			//cout << i << endl;
			//cout << "(" << i;
			sta.push(i); // root of subtree
			while(!sta.empty()) {
				tmp = vetex[sta.top()].pg;
				while(tmp && color[tmp->edge] != WHITE) {
					cout << sta.top() << " -> " << tmp->edge << " is Backward edge" << endl;
					tmp = tmp->next;
				}
				if(tmp == NULL) {
					color[sta.top()] = BLACK;
					//cout << sta.top() << ")";
					sta.pop();
				}
				else {
					//cout << "(" << tmp->edge;
					cout << sta.top() << " -> " << tmp->edge << " is tree edge" << endl;
					color[tmp->edge] = GRAY;
					sta.push(tmp->edge);
				}
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	vector<pair<int, int> > vec;
	/*vec.push_back(make_pair(0, 1));
	vec.push_back(make_pair(0, 4));
	vec.push_back(make_pair(1, 5));
	vec.push_back(make_pair(5, 2));
	vec.push_back(make_pair(5, 6));
	vec.push_back(make_pair(2, 6));
	vec.push_back(make_pair(2, 3));
	vec.push_back(make_pair(3, 6));
	vec.push_back(make_pair(3, 7));
	vec.push_back(make_pair(6, 7));
	vec.push_back(make_pair(1, 0));
	vec.push_back(make_pair(4, 0));
	vec.push_back(make_pair(5, 1));
	vec.push_back(make_pair(2, 5));
	vec.push_back(make_pair(6, 5));
	vec.push_back(make_pair(6, 2));
	vec.push_back(make_pair(3, 2));
	vec.push_back(make_pair(6, 3));
	vec.push_back(make_pair(7, 3));
	vec.push_back(make_pair(7, 6));*/
	vec.push_back(make_pair(0, 1));
	vec.push_back(make_pair(0, 7));
	vec.push_back(make_pair(1, 2));
	vec.push_back(make_pair(1, 7));
	vec.push_back(make_pair(2, 5));
	vec.push_back(make_pair(3, 2));
	vec.push_back(make_pair(3, 4));
	vec.push_back(make_pair(4, 5));
	vec.push_back(make_pair(6, 7));
	graph gra(8, vec.begin(), vec.end());
	gra.show();
	gra.traverse_dfs();
	cout << endl;
	gra.topological_sort();
	/*graph gra2(8, vec.begin(), vec.end());
	gra2.show();
	gra2.traverse_with_stack();*/
	cout << endl;

	return 0;
}
