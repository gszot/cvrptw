#include "MakeGeneTest.h"

void MakeGeneTest()//dzia³a
{
	DataSet data;
	int shop_amount = 10;
	int vehicle_amount = 5;
	data.vehicle_number = vehicle_amount;
	
	for (int i = 0;i < shop_amount;i++)
	{
		ShopDataSet shopdata;
		data.shops.push_back(shopdata);
	}

	Gene gene = MakeGene(data);
	for (auto& v : gene.vehicle_order)
		printf("%d ", v);
}