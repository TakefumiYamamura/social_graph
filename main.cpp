#include "bidirectional_search.h"
#include "bidirectional_search_probablistic.h"
#include "bounded_bidirectional_search.h"
#include "graph_data.h"
#include "result.h"
#include <iostream>
#include <time.h>


using namespace std;

int main(){
	int test_num = 150;
	graph_data gd = graph_data();
	int nodes = 0;
	int depth = 0;

	vector<Result> results = vector<Result>(3, Result(0, 0, 0));
	vector<vector<int> > win_results = vector<vector<int> >(3, vector<int>(3, 0));
	for (int i = 0; i < test_num; ++i)
	{
		pair<int, int> p = gd.fetch_two_nodes();
		bidirectional_search bd = bidirectional_search(p.first, p.second, gd);
		Result result1 = bd.exec();
		results[0].node_size += result1.node_size;
		results[0].depth += result1.depth;
		results[0].api_count += result1.api_count;
		bidirectional_search_probablistic bdp = bidirectional_search_probablistic(p.first, p.second, gd);
		Result result2 = bdp.exec();
		results[1].node_size += result2.node_size;
		results[1].depth += result2.depth;
		results[1].api_count += result2.api_count;
		bounded_bidirectional_search bbs = bounded_bidirectional_search(p.first, p.second, gd);
		Result result3 = bbs.exec();
		results[2].node_size += result3.node_size;
		results[2].depth += result3.depth;
		results[2].api_count += result3.api_count;
		cout << endl;

        if(result1.node_size == min(result1.node_size, min( result2.node_size, result2.node_size) ) ) win_results[0][0]++;
        if(result2.node_size == min(result1.node_size, min( result2.node_size, result2.node_size) ) ) win_results[0][1]++;
        if(result3.node_size == min(result1.node_size, min( result2.node_size, result2.node_size) ) ) win_results[0][2]++;

        if(result1.depth == min(result1.depth, min( result2.depth, result2.depth) ) ) win_results[1][0]++;
        if(result2.depth == min(result1.depth, min( result2.depth, result2.depth) ) ) win_results[1][1]++;
        if(result3.depth == min(result1.depth, min( result2.depth, result2.depth) ) ) win_results[1][2]++;

        if(result1.api_count == min(result1.api_count, min( result2.api_count, result2.api_count) ) ) win_results[2][0]++;
        if(result2.api_count == min(result1.api_count, min( result2.api_count, result2.api_count) ) ) win_results[2][1]++;
        if(result3.api_count == min(result1.api_count, min( result2.api_count, result2.api_count) ) ) win_results[2][2]++;

	}

	for (int i = 0; i < 3; ++i)
	{
		// cout << "nodes        : " << results[i].node_size << endl;
		// cout << "depth        : " << results[i].depth << endl;
		// cout << "api_count    : " << results[i].api_count << endl;
		cout << "ave_nodes    : " << 1.0 * results[i].node_size/ test_num << endl;
		cout << "ave_depth    : " << 1.0 * results[i].depth / test_num << endl;
		cout << "ave_api_count: " << 1.0 * results[i].api_count / test_num << endl;
		cout << endl;
	}

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3 ; ++j)
		{
			cout << win_results[i][j] << " ";
		}
		cout << endl;
	}

}
