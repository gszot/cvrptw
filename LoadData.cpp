#include <fstream>

#include "LoadData.h"

using namespace std;

DataSet LoadData(string path)
{
	DataSet data;
	ShopDataSet shopdata;
	ifstream file;
	//dane/cvrptw4.txt
	//dane/cvrptw2.txt
	//dane/C101edit.txt
	file.open(path);
	file >> data.vehicle_number;
	file >> data.capacity;
	while (!file.eof())
	{
		file >> shopdata.cust_no;
		file >> shopdata.xcoord;
		file >> shopdata.ycoord;
		file >> shopdata.demand;
		file >> shopdata.ready_time;
		file >> shopdata.due_time;
		file >> shopdata.service_time;
		/*printf("%s\n", typeid(shopdata.cust_no).name());
		printf("%s\n", typeid(shopdata.xcoord).name());
		printf("%s\n", typeid(shopdata.ycoord).name());
		printf("%s\n", typeid(shopdata.demand).name());
		printf("%s\n", typeid(shopdata.ready_time).name());
		printf("%s\n", typeid(shopdata.due_time).name());
		printf("%s\n\n", typeid(shopdata.service_time).name());*/
		data.shops.push_back(shopdata);
	}
	return data;
}