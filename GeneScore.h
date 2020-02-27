#pragma once
class GeneScore
{
public:

	int veh_used;
	long double cost;

	GeneScore(int v=99999, long double c=0) : veh_used(v), cost(c) {}

	void print();

	bool operator== (GeneScore score);
	bool operator!= (GeneScore score);
};