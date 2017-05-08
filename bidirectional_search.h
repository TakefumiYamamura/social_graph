#ifndef ___Class_bidirectional_search
#define ___Class_bidirectional_search

#include <iostream>
#include <vector>
#include <string>
#include <fstream> 
#include <sstream>
#include <unordered_map>
#include <queue>

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

public:
	bidirectional_search(int _start_id, int _goal_id);
	std::vector<int> fetch_next(int cur);
	void exec();
};

#endif