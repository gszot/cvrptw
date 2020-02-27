#pragma once
#include <vector>
#include "VehicleRoute.h"
#include "GeneScore.h"
#include "Route.h"

class Gene
{
public:
	GeneScore score;
	std::vector <int> vehicle_order; //do i-tego sklepu jedzie samochód o id vehicle_order[i].
	void print();
};

class Gene1
{
public:
	GeneScore score;
	bool changed = true;
	std::vector <vector<int>> routes;
	void print();
};

class Gene2
{
public:
	GeneScore score;
	std::vector <Route> routes;
	void print();
	void updateScore();
};

