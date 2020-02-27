#pragma once
#include "ShopDataSet.h"
#include <vector>

class DataSet
{
public:
	int vehicle_number;
	int capacity;
	std::vector <ShopDataSet> shops;
	void print();
};

