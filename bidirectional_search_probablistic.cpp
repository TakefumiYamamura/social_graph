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

#include "bidirectional_search_probablistic.h"
#include "union_find.h"
#include "graph_data.h"

using namespace std;


// # Undirected graph: ../../data/output/youtube.ungraph.txt
// # Youtube
// # Nodes: 1134890 Edges: 2987624
// # FromNodeId	ToNodeId
// 一番大きなindex 番号　1157806

bidirectional_search_probablistic::bidirectional_search_probablistic(int _start_id, int _goal_id, graph_data gd){
	start_id = _start_id;
	goal_id  = _goal_id;
	api_call_count = 0;
	delay_parameter = -2.0;
	ifstream ifs("com_youtube_ungraph.txt");
	adj = gd.fetch_adj();
	// 乱数初期化
	generator = mt19937(12345);
	distribution = uniform_real_distribution<double>(0.0,1.0);
}


struct Node
{
	int id;
	int type;
	int depth;
	int follow_nums;
	bool operator < (const Node& x) const {
		if(depth == x.depth){
			return follow_nums < x.follow_nums;
		}
		return depth > x.depth;
	}
	// type = 0 start
	// type = 1 goal
};


int bidirectional_search_probablistic::delay_func(){
	// 0 ~ 1.00000
	double probability = distribution(generator);
	double denominator = 0;
	for (auto itr = depth_map.begin(); itr != depth_map.end(); ++itr)
	{
		if(itr->second <= 0) continue;
		double d = itr->first;
		denominator += exp(delay_parameter * d);
	}


	double molecule = 0;
	for (auto itr = depth_map.begin(); itr != depth_map.end(); ++itr)
	{
		if(itr->second <= 0) continue;
		double d = itr->first;
		molecule += exp(delay_parameter * d);
		// cout << molecule / denominator << endl;
		if(molecule / denominator >  probability){
			return itr->first;
		}
	}
	cout << "error" << endl;
	// assert(true);

	return -1;
}


void bidirectional_search_probablistic::exec(){
	map<int, priority_queue<Node> > map_q;
	// unordered_map<int, priority_queue<Node> > um;
	Node start_n = {start_id, 0, 0, adj[start_id].size()};
	// start_visited[start_id] = true;
	// goal_visited[goal_id] = true;
	Node goal_n = {goal_id, 1, 0, adj[goal_id].size()};
	depth_map[0] = 2;
	map_q[0].push(start_n);
	map_q[0].push(goal_n);
	int queue_num = 2;

	while(queue_num != 0){
		// auto itr  = map_q.begin();
		int selected_itr = delay_func();
		Node cur = map_q[selected_itr].top();
		map_q[selected_itr].pop();
		queue_num--;
		
		if(cur.type == 0){
			if(start_visited[cur.id]) continue;
			start_visited[cur.id] = true;
			if(goal_visited.find(cur.id) != goal_visited.end()){
				cout << "api_call_count is " << endl;
				cout << api_call_count << endl;
				cout << "open node num is " << endl;
				cout << start_visited.size() + goal_visited.size() << endl;
				cout << "depth is " << endl;
				cout << depth_visited[cur.id] + cur.depth << endl;
				break;
			}
			depth_visited[cur.id] = cur.depth;
		}else{
			if(goal_visited[cur.id]) continue;
			goal_visited[cur.id] = true;
			if(start_visited.find(cur.id) != start_visited.end()){
				cout << "api_call_count is " << endl;
				cout << api_call_count << endl;
				cout << "open node num is " << endl;
				cout << start_visited.size() + goal_visited.size() << endl;
				cout << "depth is " << endl;
				cout << depth_visited[cur.id] + cur.depth << endl;
				break;
			}
			depth_visited[cur.id] = cur.depth;
		}

		api_call_count++;
		for (int i = 0; i < adj[cur.id].size(); ++i)
		{	
			// if(cur.type == 0 && start_visited[cur.id]) continue;
			// if(cur.type == 1 && goal_visited[cur.id]) continue;
			Node next = {adj[cur.id][i], cur.type, cur.depth + 1, adj[adj[cur.id][i]].size()};
			map_q[next.depth].push(next);
			queue_num++;
			depth_map[next.depth]++;
		}
		depth_map[cur.depth]--;
	}

}
