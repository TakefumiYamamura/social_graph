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
#include "union_find.h"
#include "graph_data.h"
#include "result.h"

using namespace std;

// # Undirected graph: ../../data/output/youtube.ungraph.txt
// # Youtube
// # Nodes: 1134890 Edges: 2987624
// # FromNodeId	ToNodeId
// 一番大きなindex 番号　1157806

bidirectional_search::bidirectional_search(int _start_id, int _goal_id, graph_data gd){
	start_id = _start_id;
	goal_id  = _goal_id;
	api_call_count = 0;
	adj = gd.fetch_adj();
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

void bidirectional_search::print_result(int api_count, int open_node, int depth){
	cout << "bidirectional_search_result" << endl; 
	cout << "api_call_count is : ";
	cout << api_count << endl;
	cout << "open node num is  : ";
	cout << open_node << endl;
	cout << "depth is          : ";
	cout << depth << endl;
}

Result bidirectional_search::exec(){
	priority_queue<Node> q;
	Node start_n = {start_id, 0, 0, adj[start_id].size()};
	start_visited[start_id] = 0;
	goal_visited[goal_id] = 0;
	Node goal_n = {goal_id, 1, 0, adj[goal_id].size()};
	q.push(start_n);
	q.push(goal_n);

	while(!q.empty()){
		Node cur = q.top();
		q.pop();

		if(cur.type == 0){
			if(goal_visited.find(cur.id) != goal_visited.end()){
				int node_size = start_visited.size() + goal_visited.size();
				int depth = start_visited[cur.id] + goal_visited[cur.id];
				print_result(api_call_count, node_size, depth);
				return Result(node_size, depth, api_call_count);
			}
		}else{
			if(start_visited.find(cur.id) != start_visited.end()){
				int node_size = start_visited.size() + goal_visited.size();
				int depth = start_visited[cur.id] + goal_visited[cur.id];
				return Result(node_size, depth, api_call_count);
			}
		}

		api_call_count++;
		for (int i = 0; i < adj[cur.id].size(); ++i)
		{	
			int next_i = adj[cur.id][i];
			if(cur.type == 0 && start_visited.find(next_i) != start_visited.end() ) continue;
			if(cur.type == 1 && goal_visited.find(next_i) != goal_visited.end() ) continue;
			Node next = {next_i, cur.type, cur.depth + 1, adj[next_i].size()};
			q.push(next);
			if(cur.type == 0){
				start_visited[next_i] = next.depth;
				if(goal_visited.find(next_i) != goal_visited.end()){
					int node_size = start_visited.size() + goal_visited.size();
					int depth = start_visited[next_i] + goal_visited[next_i];
					print_result(api_call_count, node_size, depth);
					return Result(node_size, depth, api_call_count);
				}
			}else{
				goal_visited[next_i] = next.depth;
				if(start_visited.find(next_i) != start_visited.end()){
					int node_size = start_visited.size() + goal_visited.size();
					int depth = start_visited[next_i] + goal_visited[next_i];
					print_result(api_call_count, node_size, depth);
				    return Result(node_size, depth, api_call_count);
				}
			}
		}
	}
	return Result(0, 0, 0);

}
