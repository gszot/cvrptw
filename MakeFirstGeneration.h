#pragma once
#include <random>
#include <numeric>
#include "Generation.h"
#include "DataSet.h"
#include "MakeGene.h"

Generation MakeFirstGeneration(DataSet data, long gen_size);
Generation1 MakeFirstGeneration1(DataSet data, long gen_size);