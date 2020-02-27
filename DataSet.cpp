#include "DataSet.h"

void DataSet::print()
{
	printf("VN: %d CAP: %d\n", vehicle_number, capacity);
	for (auto& shopdata : shops)
		printf("%d %d %d %d %d %d %d\n", shopdata.cust_no, shopdata.xcoord, shopdata.ycoord, shopdata.demand, shopdata.ready_time, shopdata.due_time, shopdata.service_time);
	printf("VN: %d CAP: %d\n", vehicle_number, capacity);
	printf("\n\n\n");
}