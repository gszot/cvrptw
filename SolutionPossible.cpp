#include <algorithm>

#include "SolutionPossible.h"

using namespace std;

double Dist(int x1, int y1, int x2, int y2)
{
	return sqrt(
		(x1-x2)*(x1-x2)
		+
		(y1-y2)*(y1-y2)
	);
}
bool SolutionPossible(DataSet data)
{
	int depot_x = data.shops[0].xcoord;
	int depot_y = data.shops[0].ycoord;
	double dist;
	for (auto& shop : data.shops)
	{
		if (shop.cust_no != 0)
		{
			dist = Dist(depot_x, depot_y, shop.xcoord, shop.ycoord);
			if (max(dist, (double)shop.ready_time) + shop.service_time + dist > data.shops[0].due_time) return false;
		}
	}
	return true;
}