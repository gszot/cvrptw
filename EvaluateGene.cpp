#include <vector>
#include <set>

#include "EvaluateGene.h"
#include "GeneScore.h"


using namespace std;

double ShopDist(VehicleGeneData vehicle, ShopDataSet shop)
{
	return sqrt(
		(vehicle.xcoord - shop.xcoord)*(vehicle.xcoord - shop.xcoord)
		+ 
		(vehicle.ycoord - shop.ycoord)*(vehicle.ycoord - shop.ycoord)
	);
}
double RouteCost(vector<int> route, DataSet data)
{
	double dist;
	VehicleGeneData vehicle;
	vehicle.current_time = 0;
	vehicle.xcoord = data.shops[0].xcoord;
	vehicle.ycoord = data.shops[0].ycoord;
	for (int shop_id : route)
	{
		dist = ShopDist(vehicle, data.shops[shop_id]);
		vehicle.xcoord = data.shops[shop_id].xcoord;
		vehicle.ycoord = data.shops[shop_id].ycoord;
		vehicle.current_time += dist;
		if (vehicle.current_time < data.shops[shop_id].ready_time) vehicle.current_time = data.shops[shop_id].ready_time;
		vehicle.current_time += data.shops[shop_id].service_time;
	}
	dist = ShopDist(vehicle, data.shops[0]);
	vehicle.xcoord = data.shops[0].xcoord;
	vehicle.ycoord = data.shops[0].ycoord;
	vehicle.current_time += dist;

	return vehicle.current_time;
}

GeneScore EvaluateGene(Gene gene, DataSet data)
{
	GeneScore gene_score;
	int vehicles_unused_W = 0;
	int vehicles_used = 0;
	set <int> vehicles_id_used;
	int total_cost_W = 1;
	double total_cost = 0;
	
	vector <VehicleGeneData> vehicles_data;
	for (int i = 0;i < data.vehicle_number;i++)
	{
		VehicleGeneData vehicle_data;
		vehicle_data.current_time = 0;
		vehicle_data.current_capacity = data.capacity;
		vehicle_data.xcoord = data.shops[0].xcoord;
		vehicle_data.ycoord = data.shops[0].ycoord;
		vehicles_data.push_back(vehicle_data);
	}
	int actual_vehicle_id;
	double dist_to_actual;
	double dist_to_depot;
	double start_time;
	for (unsigned int i = 1; i < data.shops.size(); i++)
	{
		actual_vehicle_id = gene.vehicle_order[i];
		//printf("sid: %d vid: %d t: %lf c: %d\n", i, actual_vehicle_id, vehicles_data[actual_vehicle_id].current_time, vehicles_data[actual_vehicle_id].current_capacity);
		dist_to_actual = ShopDist(vehicles_data[actual_vehicle_id], data.shops[i]);
		//printf("d: %lf\n\n\n", dist_to_actual);
		if (vehicles_data[actual_vehicle_id].current_time + dist_to_actual > data.shops[i].due_time) { gene_score.veh_used = data.vehicle_number + 1; gene_score.cost = -1; return gene_score; } 
		else if (vehicles_data[actual_vehicle_id].current_capacity < data.shops[i].demand) { gene_score.veh_used = data.vehicle_number + 1; gene_score.cost = -2; return gene_score; }
		else
		{
			start_time = vehicles_data[actual_vehicle_id].current_time;

			vehicles_data[actual_vehicle_id].current_time += dist_to_actual; //czas na dojazd
			if (vehicles_data[actual_vehicle_id].current_time < data.shops[i].ready_time) vehicles_data[actual_vehicle_id].current_time = data.shops[i].ready_time; //ewentualne czekanie na wy³adunek
			vehicles_data[actual_vehicle_id].current_time += data.shops[i].service_time; //czas na wy³adunek
			vehicles_data[actual_vehicle_id].xcoord = data.shops[i].xcoord; //przemieszczenie
			vehicles_data[actual_vehicle_id].ycoord = data.shops[i].ycoord; //do sklepu
			vehicles_data[actual_vehicle_id].current_capacity -= data.shops[i].demand; //zmiejszenie pojemnoœci pojazdu

			if (vehicles_id_used.find(actual_vehicle_id) == vehicles_id_used.end())
				vehicles_id_used.insert(actual_vehicle_id);

			total_cost += (vehicles_data[actual_vehicle_id].current_time - start_time);
		}
	}

	for (int veh_id : vehicles_id_used)//powrót wszystkich do depota
	{
		dist_to_depot = ShopDist(vehicles_data[veh_id], data.shops[0]);
		//printf("d: %lf\n", dist_to_depot);
		if (vehicles_data[veh_id].current_time + dist_to_depot > data.shops[0].due_time) { gene_score.veh_used = data.vehicle_number + 1; gene_score.cost = -3; return gene_score; }
		else
			total_cost += dist_to_depot;
	}

	vehicles_used = vehicles_id_used.size();//liczba u¿ytych

	//gene_score = (data.vehicle_number - vehicles_used) * vehicles_unused_W + total_cost * total_cost_W;
	gene_score.veh_used = vehicles_used;
	gene_score.cost = total_cost * total_cost_W;

	return gene_score;
}

GeneScore EvaluateGene1(Gene1 gene, DataSet data)
{
	GeneScore gene_score;
	double total_cost = 0;

	if (gene.score.veh_used == -1)
	{
		gene_score.cost = 0;
		gene_score.veh_used = -1;
		return gene_score;
	}
	
	for (auto& route : gene.routes)
		total_cost += RouteCost(route, data);

	gene_score.cost = total_cost;
	gene_score.veh_used = gene.routes.size();
	return gene_score;
}