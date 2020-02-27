#pragma once
#include <string>

#include "SolutionPossible.h"
#include "LoadData.h"
#include "Generation.h"
#include "MakeFirstGeneration.h"
#include "EvaluateGeneration.h"
#include "MakeNextGeneration.h"

class GeneticAlg
{
	int ITERATIONS;
	string path;
	long gen_size;
	int mutation_rate;

public:
	GeneticAlg(int it, string p, long size, int rate) : ITERATIONS(it), path(p), gen_size(size), mutation_rate(rate) {}

	void Start();

	void StartV2();

};

