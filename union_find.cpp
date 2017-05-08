#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <string>
#include <algorithm>
#include <queue>
#include <map>

#include "union_find.h"

using namespace std;

UnionFindTree::UnionFindTree(){}
UnionFindTree::UnionFindTree(int num){
	n = num;
	par.resize(n);
	rank.resize(n);
	for (int i = 0; i < n; ++i)
	{
		par[i] = i;
		rank[i] = 0;
	}
}

int UnionFindTree::find(int x){
	if(par[x] == x){
		return x;
	}else{
		return par[x] = find(par[x]);
	}
}

void UnionFindTree::unite(int x, int y){
	int root_x = find(x);
	int root_y = find(y);
	if(root_x == root_y) return;
	if(rank[root_x] < rank[root_y]){
		par[root_x] = root_y;
	}else{
		par[root_y] = root_x;
		if(rank[root_x] == rank[root_y]) rank[root_x]++;
	}
}

bool UnionFindTree::same(int x, int y){
	return find(x) == find(y);
}
