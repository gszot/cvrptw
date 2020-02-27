#include "GeneticAlg.h"
#include "EvaluateGene.h"
#include <Windows.h>
#include <iostream>

void GeneticAlg::Start()
{
	DataSet data = LoadData(path);
	data.print();

	if (!SolutionPossible(data))
	{
		puts("impossible");
		return;
	}

	Generation1 generation;
	
	generation = MakeFirstGeneration1(data, gen_size);
	EvaluateGeneration1(generation, data);
	//generation.print();
	generation.print_best_wo_gene();
	generation.average_vehcost();
	
	GeneScore best, act_best;
	int best_iter;

	puts("-----------------------------");
	for (int i = 1; i <= ITERATIONS; i++)
	{
		printf("iteration: %d\n", i);

		MakeNextGeneration1(generation);
		//MutateGeneration(generation, mutation_rate, data.vehicle_number, data);
		EvaluateGeneration1(generation, data);
		//generation.print();
		act_best = generation.get_best_score();
		if (act_best != best)
		{
			best = act_best;
			best_iter = i;
		}
		generation.print_best_wo_gene();
		generation.average_vehcost();
		printf("best iter: %d\n", best_iter);

		puts("-----------------------------");
	}
	
	for (auto& x : generation.genes)
	{
		Gene1 best_gene = x;
		vector<int> v;
		int sum = 0;
		v.resize(data.shops.size() + 1);
		for (auto& x : v)x = 0;
		for (auto& x : best_gene.routes)
		{
			v[x.size()]++;
			sum += x.size();
		}
		v.resize(15);
		for (auto& x : v)printf("%d ", x);
		printf("%d \n", sum);
	}
	
}

void GeneticAlg::StartV2()
{
	DataSet data = LoadData(path);
	data.print();

	if (!SolutionPossible(data))
	{
		puts("impossible");
		return;
	}

	Gene1 g = MakeGene1(data);

	Gene2 gene;
	Route r;
	int maxSize = 3;
	for (auto x : g.routes)
	{
		r = Route(x);
		r.update(data);
		gene.routes.push_back(r);
	}
	//gene.print();
	std::vector<pair<Route, Route>> uselessPairs;
	for (unsigned i = 1; i <= ITERATIONS; i++)
	{
		std::puts("------------------------------");
		std::printf("iteration maxsize %d %d\n", i, maxSize);
		std::vector<Route> routes;
		for (auto& x : gene.routes)
		{
			if (x.route.size() <= maxSize)
			{
				routes.push_back(x);
				//for (auto& id : x.route)printf("%d ", id);
				//printf("\n");
			}
		}

		std::vector<pair<Route, Route>> pairs;
		pair<Route, Route> pair, pairOp;
		double passed = 0;
		double total = routes.size() * routes.size() / 2;
		cout << total << " total pairs" << endl;
		for (unsigned int i = 0; i < routes.size() - 1; i++)
		{
			for (unsigned int j = i + 1; j < routes.size(); j++)
			{
				passed++;
				//if(maxSize >=4)std::printf("%.2fr\n", passed / total);
				//system("cls");
				if (routes[i].capacity + routes[j].capacity <= data.capacity)
				{
					pair = make_pair(routes[i], routes[j]);
					//pairOp = make_pair(routes[j], routes[i]);
					//if (find(uselessPairs.begin(), uselessPairs.end(), pair) != uselessPairs.end()) continue;
					//if (find(uselessPairs.begin(), uselessPairs.end(), pairOp) != uselessPairs.end()) continue;
					pairs.push_back(pair);
				}
			}
		}
		cout << routes.size() << " routes" << endl;
		cout << pairs.size() << " pairs" << endl;
		cout << uselessPairs.size() << " uselesspairs" << endl;
		Sleep(2000);
		vector<int> shop_ids;
		VehicleGeneData vehicle;
		int dist, delta, bestDelta = 0;
		bool permIsGood, pairUseful;
		Route bestRoute;
		std::pair<Route, Route> bestPair;
		passed = 0;
		total = pairs.size();
		if (total == 0)
		{
			std::puts("ZERO PAR");
			gene.updateScore();
			std::printf("v,c %d %lf\n", gene.score.veh_used, gene.score.cost);
			Sleep(2000);
			maxSize++;
			continue;
		}
		for (auto& x : pairs)
		{
			if (find(uselessPairs.begin(), uselessPairs.end(), x) != uselessPairs.end())continue;
			pairUseful = false;
			passed++;
			if (maxSize >= 4)std::printf("%.2fp\n", passed / total);
			shop_ids.clear();
			for (auto& id : x.first.route)shop_ids.push_back(id);
			for (auto& id : x.second.route)shop_ids.push_back(id);
			sort(shop_ids.begin(), shop_ids.end());
			do {
				/*for (auto& id : shop_ids)printf("%d ", id);
				printf("\n");*/
				vehicle.current_time = 0;
				vehicle.xcoord = data.shops[0].xcoord;
				vehicle.ycoord = data.shops[0].ycoord;
				permIsGood = true;
				for (auto& x : shop_ids)
				{
					dist = ShopDist(vehicle, data.shops[x]);
					if (vehicle.current_time + dist > data.shops[x].due_time)
					{
						permIsGood = false;
						break;
					}
					else
					{
						vehicle.xcoord = data.shops[x].xcoord;
						vehicle.ycoord = data.shops[x].ycoord;
						vehicle.current_time += dist;
						if (vehicle.current_time < data.shops[x].ready_time) vehicle.current_time = data.shops[x].ready_time;
						vehicle.current_time += data.shops[x].service_time;
					}
				}
				if (permIsGood)
				{
					delta = x.first.cost + x.second.cost - vehicle.current_time;
					pairUseful = true;
					if (delta > bestDelta)
					{
						bestDelta = delta;
						bestRoute = Route(shop_ids, vehicle.current_time);
						bestPair = x;
					}
				}
			} while (std::next_permutation(shop_ids.begin(), shop_ids.end()));
			if (!pairUseful)uselessPairs.push_back(x);
		}
		if (bestDelta == 0)
			std::puts("NIC LEPSZEGO");
		else
		{
			gene.routes.erase(std::remove(gene.routes.begin(), gene.routes.end(), bestPair.first), gene.routes.end());
			gene.routes.erase(std::remove(gene.routes.begin(), gene.routes.end(), bestPair.second), gene.routes.end());
			gene.routes.push_back(bestRoute);
		}
		/*std::puts("------------");
		for (auto& id : bestPair.first.route)std::printf("%d ", id);
		std::printf("\n");
		for (auto& id : bestPair.second.route)std::printf("%d ", id);
		std::printf("\n");
		for(auto&id:bestRoute.route)std::printf("%d ", id);
		std::printf("\n");
		std::puts("------------");*/
		//gene.print();
		gene.updateScore();
		std::printf("v,c %d %lf\n", gene.score.veh_used, gene.score.cost);
		Sleep(2000);
		if (bestDelta == 0)
		{
			maxSize++;
		}
	}
}