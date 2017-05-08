#ifndef ___ClassUnionFindTree
#define ___ClassUnionFindTree

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <string>
#include <algorithm>
#include <queue>
#include <map>

class UnionFindTree
{
private:
	int n;
	std::vector<int> par;
	std::vector<int> rank;
public:
	UnionFindTree();
	UnionFindTree(int num);
	int find(int x);
	void unite(int x, int y);
	bool same(int x, int y);
};

#endif
