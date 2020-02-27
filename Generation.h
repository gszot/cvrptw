#pragma once
#include <vector>
#include "Gene.h"

class Generation
{
public:
	vector <Gene> genes;
	void print();
	void print_best_with_gene();
	void print_best_wo_gene();
	double best_score();
	void sort_genes();
};

class Generation1
{
public:
	vector <Gene1> genes;
	/*void print();
	void print_best_with_gene();
	void print_best_wo_gene();
	double best_score();
	*/
	void sort_genes();
	GeneScore get_best_score();
	Gene1 get_best_gene();
	void print_best_wo_gene();
	void print_worst();
	void print_scores();
	void print();
	void average_vehcost();
};

