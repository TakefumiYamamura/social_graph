#include "bidirectional_search.h"
#include "bidirectional_search_probablistic.h"
#include "bounded_bidirectional_search.h"
#include "graph_data.h"

int main(){
	graph_data gd = graph_data();
	for (int i = 0; i < 10; ++i)
	{
		pair<int, int> p = gd.fetch_two_nodes();
		bidirectional_search bd = bidirectional_search(p.first, p.second, gd);
		bd.exec();
		bidirectional_search_probablistic bdp = bidirectional_search_probablistic(p.first, p.second, gd);
		bdp.exec();
		bounded_bidirectional_search bbs = bounded_bidirectional_search(p.first, p.second, gd);
		bbs.exec();
	}

}
