#include "MakeFirstGeneration.h"

using namespace std;

Generation MakeFirstGeneration(DataSet data, long gen_size)
{
	long GENERATION_SIZE = gen_size;
	Generation generation;
	for (long i = 0; i < GENERATION_SIZE; i++)
	{
		generation.genes.push_back(MakeGene(data));
	}
	return generation;
}

Generation1 MakeFirstGeneration1(DataSet data, long gen_size)
{
	long GENERATION_SIZE = gen_size;
	Generation1 generation;
	puts("generating population");
	for (long i = 1; i <= GENERATION_SIZE; i++)
	{
		printf("%d\n", i);
		generation.genes.push_back(MakeGene1(data));
	}
	return generation;
}