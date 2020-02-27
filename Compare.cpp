#include "Compare.h"

bool compareGenes(const Gene& gene1, const Gene& gene2)
{
	if (gene1.score.veh_used == gene2.score.veh_used)
		return gene1.score.cost < gene2.score.cost;
	else
		return gene1.score.veh_used < gene2.score.veh_used;
}
bool compareGenes1(const Gene1& gene1, const Gene1& gene2)
{
	if (gene1.score.veh_used == gene2.score.veh_used)
		return gene1.score.cost < gene2.score.cost;
	else
		return gene1.score.veh_used < gene2.score.veh_used;
}
bool longerRoute(const vector<int>& route1, const vector<int>& route2)
{
	return route1.size() > route2.size();
}