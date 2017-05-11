#ifndef ___Class_bidirectional_search
#define ___Class_bidirectional_search

#include <iostream>
#include <vector>
#include <string>
#include <fstream> 
#include <sstream>
#include <unordered_map>
#include <queue>

#include "graph_data.h"

class  bidirectional_search
{
private:
	int start_id;
	int goal_id;
	int api_call_count;
	std::vector<std::vector<int> > adj;
	std::unordered_map<int, bool> visited;
	std::unordered_map<int, bool> start_visited;
	std::unordered_map<int, bool> goal_visited;
	std::unordered_map<int, int> depth_visited;

public:
	bidirectional_search(int _start_id, int _goal_id, graph_data gd);
	void exec();
};

#endif