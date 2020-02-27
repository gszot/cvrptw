#include <algorithm>

#include "CombineGenes.h"
#include "Compare.h"

using namespace std;

Gene CombineGenes(Gene gene1, Gene gene2)
{
	Gene new_gene;
	int gene_len = gene1.vehicle_order.size();
	int cut_index = 1 + (rand() % (gene_len - 2)); //wszystkie poza zerowym i ostatnim
	vector<int> part1 (gene1.vehicle_order.begin(), gene1.vehicle_order.begin() + cut_index);
	vector<int> part2 (gene2.vehicle_order.begin() + cut_index, gene2.vehicle_order.end());
	new_gene.vehicle_order = part1;
	new_gene.vehicle_order.insert(new_gene.vehicle_order.end(), part2.begin(), part2.end());
	return new_gene;
}

Gene1 CombineGenes1(Gene1 gene1, Gene1 gene2)//1-giver 2-reciever
{
	vector<int> shop_ids;
	const float longest_routes_amount = 0.1; //10 procent najd³u¿szych tras
	int index_to_take = ceil(longest_routes_amount * gene1.routes.size());
	//int index_to_take = 2;
	sort(gene1.routes.begin(), gene1.routes.end(), longerRoute);
	vector<vector<int>> routes_taken = gene1.routes;
	routes_taken.resize(index_to_take);
	for (vector<int> route : routes_taken)
	{
		for (int shop_id : route)
		{
			shop_ids.push_back(shop_id);
		}
	}
	Gene1 new_gene;
	vector<int> new_route;
	for (vector<int> route : gene2.routes)
	{
		new_route.clear();
		for (int shop_id : route)
		{
			if (find(shop_ids.begin(), shop_ids.end(), shop_id) == shop_ids.end()) new_route.push_back(shop_id); //shop_id nie wystêpuje w trasach do dodania
		}
		if (!new_route.empty()) new_gene.routes.push_back(new_route);
	}
	new_gene.routes.insert(new_gene.routes.end(), routes_taken.begin(), routes_taken.end());
	return new_gene;
}



/*for (vector<int> &route : gene2.routes)
	{
		route.erase(
			remove_if(route.begin(), route.end(), [&](int shop_id) {
				return find(shop_ids.begin(), shop_ids.end(), shop_id) != shop_ids.end();
			}), route.end());
	}
	gene2.routes.erase(remove_if(gene2.routes.begin(), gene2.routes.end(), [&](vector<int> x) {return x.empty(); }), gene2.routes.end());*/
