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
#include "result.h"

#include "bounded_bidirectional_search.h"
#include "union_find.h"
#include "graph_data.h"

using namespace std;


// # Undirected graph: ../../data/output/youtube.ungraph.txt
// # Youtube
// # Nodes: 1134890 Edges: 2987624
// # FromNodeId	ToNodeId
// 一番大きなindex 番号　1157806

bounded_bidirectional_search::bounded_bidirectional_search(int _start_id, int _goal_id, graph_data& gd){
	start_id = _start_id;
	goal_id  = _goal_id;
	api_call_count = 0;
	delay_parameter = -2.0;
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




int bounded_bidirectional_search::delay_func(){
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


void bounded_bidirectional_search::print_result(int api_count, int open_node, int depth){
	cout << "bounded_bidirectional_search_result" << endl; 
	cout << "api_call_count is : ";
	cout << api_count << endl;
	cout << "open node num is  : ";
	cout << open_node << endl;
	cout << "depth is          : ";
	cout << depth << endl;
}



Result bounded_bidirectional_search::exec(){
	map<int, priority_queue<Node> > map_q;
	Node start_n = {start_id, 0, 0, adj[start_id].size()};
	start_visited[start_id] = 0;
	goal_visited[goal_id] = 0;
	Node goal_n = {goal_id, 1, 0, adj[goal_id].size()};
	depth_map[0] = 2;
	map_q[0].push(start_n);
	map_q[0].push(goal_n);
	int queue_num = 2;
	int max_depth = 0;
	bool find_flag = false;

	while(queue_num != 0){

		int selected_itr = delay_func();
		Node cur = map_q[selected_itr].top();
		map_q[selected_itr].pop();
		queue_num--;

		if(cur.type == 0){
			if(goal_visited.find(cur.id) != goal_visited.end()){
				int node_size = start_visited.size() + goal_visited.size();
				int depth = start_visited[cur.id] + goal_visited[cur.id];
				// print_result(api_call_count, node_size, depth);
				max_depth = depth;
				// cout << depth << endl;
				find_flag = true;
				break;
				// return pair<int,int>(node_size, depth);
			}
		}else{
			if(start_visited.find(cur.id) != start_visited.end()){
				int node_size = start_visited.size() + goal_visited.size();
				int depth = start_visited[cur.id] + goal_visited[cur.id];
				// print_result(api_call_count, node_size, depth);
				max_depth = depth;
				// cout << depth << endl;
				find_flag = true;
				break;
			}
		}

		api_call_count++;
		for (int i = 0; i < adj[cur.id].size(); ++i)
		{	
			int next_i = adj[cur.id][i];
			if(cur.type == 0 && start_visited.find(next_i) != start_visited.end() ) continue;
			if(cur.type == 1 && goal_visited.find(next_i) != goal_visited.end() ) continue;
			// if(cur.type == 1 && goal_visited[cur.id]) continue;
			Node next = {next_i, cur.type, cur.depth + 1, adj[next_i].size()};
			map_q[next.depth].push(next);
			queue_num++;
			depth_map[next.depth]++;
			if(cur.type == 0){
				start_visited[next_i] = next.depth;
				if(goal_visited.find(next_i) != goal_visited.end()){
					int node_size = start_visited.size() + goal_visited.size();
					int depth = start_visited[next_i] + goal_visited[next_i];
					// print_result(api_call_count, node_size, depth);
					max_depth = depth;
					// cout << depth << endl;
					find_flag = true;
					break;
				}
			}else{
				goal_visited[next_i] = next.depth;
				if(start_visited.find(next_i) != start_visited.end()){
					int node_size = start_visited.size() + goal_visited.size();
					int depth = start_visited[next_i] + goal_visited[next_i];
					// print_result(api_call_count, node_size, depth);
					max_depth = depth;
					// cout << depth << endl;
					find_flag = true;
					break;
				}
			}
		}
		depth_map[cur.depth]--;
		if(find_flag) break;
	}

	for (auto itr = map_q.begin(); itr != map_q.end(); ++itr)
	{
		if(max_depth % 2 == 1 && itr->first >= max_depth / 2){
			cout << "optimal depth is same" << endl;
			int node_size = start_visited.size() + goal_visited.size();
			print_result(api_call_count, node_size, max_depth);
			return Result(node_size, max_depth, api_call_count);
		}

		if(max_depth % 2 == 0 && itr->first >= max_depth / 2){
			cout << "optimal depth is same" << endl;
			int node_size = start_visited.size() + goal_visited.size();
			print_result(api_call_count, node_size, max_depth);
			return Result(node_size, max_depth, api_call_count);

		}
		priority_queue<Node> cur_queue = itr->second;
		while(!cur_queue.empty()){
			Node cur = cur_queue.top();
			cur_queue.pop();
			if(max_depth % 2 == 0 && cur.type == 0 && cur.depth >= max_depth / 2 - 1) continue;

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
					print_result(api_call_count, node_size, depth);
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
				map_q[next.depth].push(next);
				if(cur.type == 0){
					start_visited[next_i] = next.depth;
					if(goal_visited.find(next_i) != goal_visited.end()){
						int node_size = start_visited.size() + goal_visited.size();
						int depth = start_visited[next_i] + goal_visited[next_i];
						if(depth > max_depth) continue;
						print_result(api_call_count, node_size, depth);
						
						return Result(node_size, depth, api_call_count);
					}
				}else{
					goal_visited[next_i] = next.depth;
					if(start_visited.find(next_i) != start_visited.end()){
						int node_size = start_visited.size() + goal_visited.size();
						int depth = start_visited[next_i] + goal_visited[next_i];
						if(depth > max_depth) continue;
						print_result(api_call_count, node_size, depth);
						
						return Result(node_size, depth, api_call_count);

					}
				}
			}
		}
	}
	cout << "optimal depth is same" << endl;
	return Result(0, 0, 0);

}
