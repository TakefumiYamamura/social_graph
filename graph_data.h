#ifndef ___Class_fetch_data
#define ___Class_fetch_data

#include <iostream>
#include <vector>
#include <string>
#include <fstream> 
#include <sstream>
#include <unordered_map>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <random>
#include "union_find.h"


class graph_data
{
private:
	std::vector<std::pair<int, int> > edges;
	std::vector<std::vector<int> > adj;
	UnionFindTree uft;
	std::unordered_set<int> ust;
	std::vector<int> nodes;
	std::mt19937 generator;
    std::uniform_int_distribution<int> distribution;


public:
	graph_data(std::string file_name = "com_youtube_ungraph.txt");
	std::vector<std::pair<int, int> > fetch_edges();
	std::vector<std::vector<int> > fetch_adj();
	UnionFindTree fetch_uft();
	std::pair<int, int> fetch_two_nodes();

};

#endif