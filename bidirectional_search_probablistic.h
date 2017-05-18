#ifndef ___Class_bidirectional_search_probablistic
#define ___Class_bidirectional_search_probablistic

#include <iostream>
#include <vector>
#include <string>
#include <fstream> 
#include <sstream>
#include <unordered_map>
#include <queue>
#include <set>
#include <map>
#include <random>
#include "graph_data.h"
#include "result.h"

class  bidirectional_search_probablistic
{
private:
	int start_id;
	int goal_id;
	int api_call_count;
	double delay_parameter;
	std::vector<std::vector<int> > adj;
	// std::unordered_map<int, bool> visited;
	std::unordered_map<int, int> start_visited;
	std::unordered_map<int, int> goal_visited;
	// std::unordered_map<int, std::priority_queue<Node> > um_queue;
	std::map<int, int> depth_map; // depth count
	// std::unordered_map<int, int> depth_visited;// index , depth
	std::mt19937 generator;
    std::uniform_real_distribution<double> distribution;

public:
	bidirectional_search_probablistic(int _start_id, int _goal_id, graph_data gd);
	int delay_func();
	Result exec();
	void print_result(int api_count, int open_node, int depth);
};

#endif