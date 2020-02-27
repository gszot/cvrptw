#include "EvaluateGeneration.h"

using namespace std;

void EvaluateGeneration(Generation &generation, DataSet data)
{
	for (Gene &gene : generation.genes)
	{
		gene.score = EvaluateGene(gene, data);
		//random_shuffle(gene.vehicle_order.begin() + 1, gene.vehicle_order.end());
	}
}

void EvaluateGeneration1(Generation1& generation, DataSet data)
{
	for (Gene1& gene : generation.genes)
	{
		if (gene.changed)
		{
			gene.score = EvaluateGene1(gene, data);
			gene.changed = false;
		}
		//random_shuffle(gene.vehicle_order.begin() + 1, gene.vehicle_order.end());
	}
}