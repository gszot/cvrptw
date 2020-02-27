#include "Route.h"
#include "EvaluateGene.h"

void Route::update(DataSet data)
{
	capacity = 0;
	cost = RouteCost(route, data);
	for (int s : route)
	{
		capacity += data.shops[s].demand;
	}
}

bool const Route::operator==(const Route r)const { return route == r.route; }
bool const Route::operator!=(const Route r)const {return route != r.route;}

