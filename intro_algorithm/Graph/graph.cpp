/*
 * author:	luo feng
 * date:	2014/4/14
 * source:	Introduction to Algorithm
 * title:	BFS(graph)
 * info:	算法导论中图部分的广度优先搜索。主要的训练项目是：图的数据结构，广度优先搜索，广度优先搜索树。
 *		深度优先搜索。主要的训练项目是：深度优先搜索。
 */

#include <iostream>
#include <climits>
#include <vector>
#include <queue>
#include <iterator>
using namespace std;

enum COLOR {
	WHITE, GREY, BLACK
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
public:
	graph(int, vector<pair<int, int> >::iterator, vector<pair<int, int> >::iterator);
	~graph();
	void show();
	void traverse_bfs(int);
	void bfs_path(int, int);
	void traverse_dfs(int);
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

// 广度优先搜索有几个需要注意的地方：为了区分节点是否访问过，将节点分成三种颜色
// （白色->未访问过，灰色->访问过但还有相邻的节点没有访问，黑色->所有相邻的节点都被访问了），
// 而且，在访问过程中用到了队列，从代码可以看出来，它的访问方式跟二叉树中的层次遍历类似
void graph::traverse_bfs(int start)
{
	color[start] = GREY;

	queue<int> que;
	int node = 0;
	_gnode *pg = NULL;
	que.push(start);
	distance[start] = 0;
	cout << start << endl;
	while(!que.empty()) {
		node = que.front();
		pg = vetex[node].pg;
		while(pg) {
			if(color[pg->edge] == WHITE) {
				color[pg->edge] = GREY;
				cout << pg->edge << endl;
				parent[pg->edge] = node;
				distance[pg->edge] = distance[node] + 1;
				que.push(pg->edge);
			}
			pg = pg->next;
		}
		color[node] = BLACK;
		que.pop();
	}
}

void graph::traverse_dfs(int start)
{
	
}

// 经过广度优先搜索遍历后，所遍历的路径形成了一棵广度优先搜索树，bfs_path()打印广度优先搜索树中从start到end的路径以及距离
void graph::bfs_path(int start, int end)
{
	if(end == start) {
		cout << end << endl;
	}
	else if(parent[end] == -1) {
		cout << "no path from " << start << " to " << end << endl;
	}
	else {
		bfs_path(start, parent[end]);
		cout << end << " distance: " << distance[end] << endl;
	}
}

int main(int argc, char const *argv[])
{
	vector<pair<int, int> > vec;
	vec.push_back(make_pair(0, 1));
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
	vec.push_back(make_pair(7, 6));
	graph gra(8, vec.begin(), vec.end());
	gra.show();
	gra.traverse_bfs(1);
	cout << endl;
	int end_node = 2;
	cout << "path from " << 1 << " to " << end_node << endl;
	gra.bfs_path(1, end_node);

	return 0;
}
