#include "MutateGeneration.h"
#include "MutateGene.h"
#include "MakeGene.h"

void MutateGeneration(Generation &generation, int mutation_rate, int vehicle_number, DataSet data)
{
	for (Gene& gene : generation.genes)
	{
		int choice = rand() % 100;
		if (choice < mutation_rate)
		{
			gene = MakeGene(data);
			//MutateGene(gene, vehicle_number);
		}
	}
}