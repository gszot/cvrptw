#include <algorithm>

#include "Generation.h"
#include "Compare.h"

void Generation::print()
{
	for (auto& v : genes)
	{
		printf("VU: %d C: %lf A: ", v.score.veh_used, v.score.cost);
		v.print();
	}
	printf("\n");
}
void Generation::print_best_with_gene()
{
	printf("best gene: V: %d C: %lf A:", genes[0].score.veh_used, genes[0].score.cost);
	genes[0].print();
}
void Generation::print_best_wo_gene()
{
	printf("best gene: V: %d C: %lf\n", genes[0].score.veh_used, genes[0].score.cost);
}
double Generation::best_score()
{
	sort_genes();
	return genes[0].score.cost;
}
void Generation::sort_genes()
{
	sort(genes.begin(), genes.end(), compareGenes);
}

void Generation1::sort_genes()
{
	sort(genes.begin(), genes.end(), compareGenes1);
}
GeneScore Generation1::get_best_score()
{
	int best_veh = 999999;
	double best_cost = 0;
	for (auto& x : genes)
	{
		if (x.score.veh_used < best_veh)
		{
			best_veh = x.score.veh_used;
			best_cost = x.score.cost;
		}
		else if (x.score.veh_used == best_veh && x.score.cost < best_cost)
		{
			best_cost = x.score.cost;
		}
	}
	return GeneScore(best_veh, best_cost);
}
Gene1 Generation1::get_best_gene()
{
	Gene1 best;
	int best_veh = 999999;
	double best_cost = 0;
	for (auto& x : genes)
	{
		if (x.score.veh_used < best_veh)
		{
			best = x;
			best_veh = x.score.veh_used;
			best_cost = x.score.cost;
		}
		else if (x.score.veh_used == best_veh && x.score.cost < best_cost)
		{
			best_cost = x.score.cost;
			best = x;
		}
	}
	return best;
}
void Generation1::print_best_wo_gene()
{
	GeneScore best = get_best_score();
	printf("best gene: V: %d C: %lf\n", best.veh_used, best.cost);
}
void Generation1::print_worst()
{
	//sort_genes();
	int worst_veh = 999999;
	double worst_cost = 0;
	for (auto& x : genes)
	{
		if (x.score.veh_used > worst_veh)
		{
			worst_veh = x.score.veh_used;
			worst_cost = x.score.cost;
		}
		else if (x.score.veh_used == worst_veh && x.score.cost > worst_cost)
		{
			worst_cost = x.score.cost;
		}
	}
	printf("worst gene: V: %d C: %lf\n", worst_veh, worst_cost);
}
void Generation1::print_scores()
{
	//sort_genes();
	for (auto& x : genes)
	{
		printf("gene: V: %d C: %lf\n", x.score.veh_used, x.score.cost);
	}
}
void Generation1::print()
{
	for (auto& x : genes)
		x.print();
}
void Generation1::average_vehcost()
{
	long double sum_veh = 0, sum_cost = 0;
	for (auto& x : genes)
	{
		sum_veh += x.score.veh_used;
		sum_cost += x.score.cost;
	}
	printf("avg V: %.1lf C: %.1lf\n", sum_veh/genes.size(), sum_cost/genes.size());
}
