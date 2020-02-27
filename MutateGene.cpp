#include "MutateGene.h"

void MutateGene(Gene& gene, int veh_number)
{
	for (auto& v : gene.vehicle_order)
	{
		if(v != -1)
			v = rand() % veh_number;
	}
}