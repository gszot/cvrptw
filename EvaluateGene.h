#pragma once

#include "Gene.h"
#include "DataSet.h"
#include "VehicleGeneData.h"

double ShopDist(VehicleGeneData vehicle, ShopDataSet shop);
double RouteCost(vector<int> route, DataSet data);

GeneScore EvaluateGene(Gene gene, DataSet data);
GeneScore EvaluateGene1(Gene1 gene, DataSet data);

