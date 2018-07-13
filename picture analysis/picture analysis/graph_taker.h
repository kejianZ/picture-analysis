#pragma once
#include <vector>
#include <list>


using namespace std;

class graph
{
public:
	graph();
	~graph();
	vector<vector<int>> find_mid_point;
private:
};

graph::graph()
{
	int min_x = 0;
	int min_y = 0;
	int max_x = 0;
	int max_y = 0;
	vector<vector<int>> poitns;
}

graph::~graph()
{
}