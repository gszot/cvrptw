#include "Gene.h"

void Gene::print()
{
	for (auto& x : vehicle_order)
		printf("%d ", x);
	printf("\n");
}

void Gene1::print()
{
	printf("[");
	for (auto& x : routes)
	{
		printf("(");
		for (auto& y : x)
			printf("%d,", y);
		printf(")");
	}
	printf("]\n");
}

void Gene2::print()
{
	printf("[");
	for (auto& x : routes)
	{
		printf("(");
		for (auto& y : x.route)
			printf("%d,", y);
		printf(")");
	}
	printf("]\n");
}

void Gene2::updateScore()
{
	long double sum = 0;
	for (auto& x : routes)sum += x.cost;
	score = GeneScore(routes.size(), sum);
}
