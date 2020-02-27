#include "MakeGene.h"
#include "VehicleGeneData.h"
#include "EvaluateGene.h"

#include <windows.h>

using namespace std;

void Remove(vector<int> &vec, int value)
{
	vec.erase(std::remove(vec.begin(), vec.end(), value), vec.end());
}

int FindClosestIndex(DataSet data, vector<int> shops, VehicleGeneData vehicle)
{
	int minDist = 999999, dist;
	int closestIndex;

	for (unsigned int i = 0; i < shops.size(); i++)
	{
		dist = ShopDist(vehicle, data.shops[shops[i]]);
		if (dist < minDist)
		{
			minDist = dist;
			closestIndex = i;
		}
	}
	return closestIndex;
}

Gene MakeGene(DataSet data)
{
	Gene gene;
	int vehicle_id;
	int max_used_id = 0;
	gene.vehicle_order.push_back(-1); // do depota nie jedzie nic
	for (unsigned int i = 1; i < data.shops.size(); i++) // od 1 do ostatniego w³¹cznie
	{
		vehicle_id = rand() % data.vehicle_number;
		if (vehicle_id > max_used_id)
		{
			max_used_id++;
			vehicle_id = max_used_id;
		}
		gene.vehicle_order.push_back(vehicle_id);
	}
	//gene.print();
	return gene;
}

Gene1 MakeGene1(DataSet data)
{
	Gene1 gene;
	vector <int> assigned_shops; //shops assigned to current vehicle;
	vector <int> unfilled_shops, aval_unfilled_shops_prev, aval_unfilled_shops_next;
	VehicleGeneData vehicle;
	int vehicle_id = 0;
	int shop_id;
	int shop_id_index;
	double dist;

	for (auto& shop : data.shops)
	{
		if(shop.cust_no != 0)
			unfilled_shops.push_back(shop.cust_no);
	}
	//unsigned long long int cap = 0;
	//unsigned long long int time = 0;
	while (!unfilled_shops.empty())
	{
		

		vehicle_id++;
		vehicle.current_capacity = data.capacity;
		vehicle.current_time = 0;
		vehicle.xcoord = data.shops[0].xcoord;
		vehicle.ycoord = data.shops[0].ycoord;

		aval_unfilled_shops_prev = unfilled_shops;
		aval_unfilled_shops_next.clear();
		assigned_shops.clear();

		while(true)
		{
			for (auto& shop : aval_unfilled_shops_prev)
			{
				if (vehicle.current_capacity < data.shops[shop].demand)
				{
					//cap++;
					continue;
				}
				dist = ShopDist(vehicle, data.shops[shop]);
				if (vehicle.current_time + dist > data.shops[shop].due_time)
				{
					//time++;
					continue;
				}
				aval_unfilled_shops_next.push_back(shop);
			}
			
			if (aval_unfilled_shops_next.empty())
			{
				break;
			}

			//shop_id_index = rand() % aval_unfilled_shops_next.size();
			shop_id_index = FindClosestIndex(data, aval_unfilled_shops_next, vehicle);
			shop_id = aval_unfilled_shops_next[shop_id_index];

			assigned_shops.push_back(shop_id);
			Remove(unfilled_shops, shop_id);
			aval_unfilled_shops_next.erase(aval_unfilled_shops_next.begin() + shop_id_index);

			
			vehicle.current_capacity -= data.shops[shop_id].demand;
			vehicle.xcoord = data.shops[shop_id].xcoord;
			vehicle.ycoord = data.shops[shop_id].ycoord;
			vehicle.current_time += dist;
			if (vehicle.current_time < data.shops[shop_id].ready_time) vehicle.current_time = data.shops[shop_id].ready_time;
			vehicle.current_time += data.shops[shop_id].service_time;

			aval_unfilled_shops_prev = aval_unfilled_shops_next;
			aval_unfilled_shops_next.clear();
		}	

		//dist = ShopDist(vehicle, data.shops[0]);
		/*if (vehicle.current_time + dist > data.shops[0].due_time)   //nie zachodzi w spe³nialnym datasecie
		{
			unfilled_shops.insert(unfilled_shops.end(), assigned_shops.begin(), assigned_shops.end());
		}
		else*/  
		gene.routes.push_back(assigned_shops);
		
	}
	//printf("%llu %llu\n", cap, time);
	return gene;
}

//zappendowanie œcie¿ki i usuniêcie powtórek w oryginalnych œcie¿kach - nie potrzebuje naprawy - zachowuje spe³nialnoœæ
//https://books.google.pl/books?id=EkELtZAXViEC&pg=PA148&lpg=PA148&dq=cvrptw+gene+crossing&source=bl&ots=rs_N6zRvQH&sig=ACfU3U1oxpZFfo8J9UX_SYZFieh9R3MvSw&hl=pl&sa=X&ved=2ahUKEwiRtdPkvs3nAhWJpYsKHR8FAUoQ6AEwEHoECAkQAQ#v=onepage&q=cvrptw%20gene%20crossing&f=false
/*for (auto& x : unfilled_shops)printf("%d ", x);
			printf("\n");*/