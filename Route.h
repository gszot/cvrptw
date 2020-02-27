#pragma once
#include <vector>
#include "DataSet.h"
class Route
{
public:
	std::vector<int> route;
	bool changed = true;
	double cost = 0;
	double capacity = 0;

	Route() = default;
	Route(std::vector<int> r, int c=0) : route(r), cost(c) {
		changed = false;
	}

	void update(DataSet data);

	bool const operator==(const Route r)const;
	bool const operator!=(const Route r)const;
	
};

