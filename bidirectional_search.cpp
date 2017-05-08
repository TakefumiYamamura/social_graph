#include <iostream>
#include <vector>
#include <string>
#include <fstream> 
#include <sstream>
#include <unordered_map>
#include <queue>
#include <set>
#include <algorithm>

#include "bidirectional_search.h"

using namespace std;

// std::ifstream ifs("facebook_combined.txt");
std::ifstream ifs("com_youtube_ungraph.txt");
// # Undirected graph: ../../data/output/youtube.ungraph.txt
// # Youtube
// # Nodes: 1134890 Edges: 2987624
// # FromNodeId	ToNodeId
// 一番大きなindex 番号　1157806

bidirectional_search::bidirectional_search(int _start_id, int _goal_id){
	start_id = _start_id;
	goal_id  = _goal_id;
	api_call_count = 0;
	// std::ifstream ifs("facebook_combined.txt");
	// adj.resize(1142173);
	int max_v = 0;
	set<int> st;
	vector<pair<int, int> > edges;
	for (int i = 0; i < 2987624; ++i)
	{
		int tmp_a;
		int tmp_b;
		// cout << i << endl;
		ifs >> tmp_a >> tmp_b;
		st.insert(tmp_a);
		st.insert(tmp_b);
		edges.push_back(pair<int, int>(tmp_a, tmp_b));
		max_v = max(tmp_a, tmp_b);
		// adj[tmp_a].push_back(tmp_a);
		// adj[tmp_b].push_back(tmp_b);
	}
	adj.resize(max_v + 1);
	for (int i = 0; i < edges.size(); ++i)
	{
		adj[edges[i].first].push_back(edges[i].second);
		adj[edges[i].second].push_back(edges[i].first);
	}
	cout << "max_index : " << max_v << " node_nums :" <<  st.size() << endl;
	ifs.close();

}


struct Node
{
	int id;
	int type;
	// type = 0 start
	// type = 1 goal
};


void bidirectional_search::exec(){
	queue<Node> q;
	Node start_n = {start_id, 0};
	start_visited[start_id] = true;
	goal_visited[goal_id] = true;
	Node goal_n = {goal_id, 1};
	q.push(start_n);
	q.push(goal_n);

	while(!q.empty()){
		Node cur = q.front();
		q.pop();
		if(cur.type == 0){
			if(start_visited[cur.id]) continue;
			start_visited[cur.id] = true;
			if(goal_visited.find(cur.id) != goal_visited.end()){
				cout << "api_call_count is " << endl;
				cout << api_call_count << endl;
				cout << "open node num is " << endl;
				cout << start_visited.size() + goal_visited.size() << endl;
				return;
			}
		}else{
			goal_visited[cur.id] = true;
			if(start_visited.find(cur.id) != start_visited.end()){
				cout << "api_call_count is " << endl;
				cout << api_call_count << endl;
				cout << "open node num is " << endl;
				cout << start_visited.size() + goal_visited.size() << endl;
				return;
			}
		}

		for (int i = 0; i < adj[cur.id].size(); ++i)
		{	
			Node next = {adj[cur.id][i], cur.type};
			if(cur.type == 0){
			}else{
				
			}
			q.push(next);
		}
	}

}
