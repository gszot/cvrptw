#include <time.h>
#include <vector>

#include "GeneticAlg.h"

int main()
{
	srand(time(NULL));

	string path = "dane/rc21010.txt";
	//string path = "dane/m2kvrptw-0.txt";
	//string path = "dane/cvrptw4.txt";
	//string path = "dane/C101edit.txt";

	int ITERATIONS = 100;
	long gen_size = 10;
	int mutation_rate = 10;  //od 0 do 100

	GeneticAlg ga(ITERATIONS, path, gen_size, mutation_rate);
	//ga.Start();
	ga.StartV2();
	
	return 0;
}









/*Gene1 gene;
	GeneScore score;
	gene = MakeGene1(data);
	score = EvaluateGene1(gene, data);
	data.print();
	gene.print();
	score.print();*/
