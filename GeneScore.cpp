#include "GeneScore.h"
#include <stdio.h>

void GeneScore::print()
{
	printf("v c:%d %lf\n", veh_used, cost);
}

bool GeneScore::operator==(GeneScore score)
{
	return (veh_used == score.veh_used) & (cost == score.cost);
}

bool GeneScore::operator!=(GeneScore score)
{
	return !operator==(score);
}

