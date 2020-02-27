#include <vector>
#include <algorithm>

#include "Compare.h"

using namespace std;

void RoutesSortTest()
{
	vector<int> a = { 1,2 };
	vector<int> b = { 1,2,3 };
	vector<int> c = { 1,2,3,4 };
	vector<vector<int>> d = { a,b,c };
	sort(d.begin(), d.end(), longerRoute);
	for (auto& x : d)
	{
		for (auto& y : x)printf("%d ", y);
		printf("\n");
	}
}
