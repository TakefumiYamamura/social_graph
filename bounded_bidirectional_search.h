#ifndef ___Class_bounded_bidirectional_search
#define ___Class_bounded_bidirectional_search

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


class  bounded_bidirectional_search
{
private:
	int start_id;
	int goal_id;
	int api_call_count;
	double delay_parameter;
	std::vector<std::vector<int> > adj;
	std::unordered_map<int, bool> visited;
	std::unordered_map<int, bool> start_visited;
	std::unordered_map<int, bool> goal_visited;
	// std::unordered_map<int, std::priority_queue<Node> > um_queue;
	std::map<int, int> depth_map; // depth count
	std::unordered_map<int, int> depth_visited;// index , depth
	std::mt19937 generator;
    std::uniform_real_distribution<double> distribution;

public:
	bounded_bidirectional_search(int _start_id, int _goal_id, graph_data gd);
	int delay_func();
	void exec();
};

#endif
