#include "CombineGenesTest.h"

void CombineGenesTest()//dzia³a
{
	Gene gene1, gene2, gene3;
	gene1.vehicle_order = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	gene2.vehicle_order = { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
	gene3 = CombineGenes(gene1, gene2);
	for (auto& v : gene3.vehicle_order)
		printf("%d ", v);
}
