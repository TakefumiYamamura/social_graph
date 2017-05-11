#include <iostream>
#include <vector>
#include <string>
#include <fstream> 
#include <sstream>
#include <unordered_map>
#include <queue>
#include <set>
#include <algorithm>
#include <random>
#include <cmath>
#include <map>
#include <assert.h>

#include "graph_data.h"
#include "union_find.h"

using namespace std;

graph_data::graph_data(string file_name){
	generator = mt19937(12345);
	ifstream ifs(file_name);
	int max_v = 0;
	vector<pair<int, int> > edges;
	for (int i = 0; i < 2987624; ++i)
	{
		int tmp_a;
		int tmp_b;
		ifs >> tmp_a >> tmp_b;
		ust.insert(tmp_a);
		ust.insert(tmp_b);
		edges.push_back(pair<int, int>(tmp_a, tmp_b));
		max_v = max(tmp_a, tmp_b);
	}
	adj.resize(max_v + 1);
	UnionFindTree uft = UnionFindTree(max_v);
	for (int i = 0; i < edges.size(); ++i)
	{
		uft.unite(edges[i].first, edges[i].second);
		adj[edges[i].first].push_back(edges[i].second);
		adj[edges[i].second].push_back(edges[i].first);
	}
	for (auto itr = ust.begin(); itr != ust.end() ; ++itr)
	{
		nodes.push_back(*itr);
	}
	distribution = uniform_int_distribution<int>(0, ust.size() - 1);

	cout << "max_index : " << max_v << " node_nums :" <<  ust.size() << endl;
	ifs.close();
}

vector<pair<int, int> > graph_data::fetch_edges(){
	return edges;
}

vector<vector<int> > graph_data::fetch_adj(){
	return adj;
}

UnionFindTree graph_data::fetch_uft(){
	return uft;
}

pair<int, int> graph_data::fetch_two_nodes(){
	int p1 = distribution(generator);
	int p2 = distribution(generator);
	while(p1 != p2 || uft.same(nodes[p1], nodes[p2]) == false){
		p2 = distribution(generator);
	}
	return pair<int, int>(nodes[p1], nodes[p2]);
}

