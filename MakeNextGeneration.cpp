#include "MakeNextGeneration.h"
#include "CombineGenes.h"
#include <algorithm>

using namespace std;

void MakeNextGeneration(Generation &generation)
{
	float SURVIVAL_RATE = 0.5;
	unsigned int gene_starting_size = generation.genes.size();
	int index_to_crop = int(SURVIVAL_RATE * generation.genes.size());
	generation.sort_genes();
	generation.genes.resize(index_to_crop);
	while (generation.genes.size() < gene_starting_size)
	{
		int index1 = rand() % generation.genes.size();
		int index2;
		do
		{
			index2 = rand() % generation.genes.size();
		} while (index1 == index2);
		Gene new_gene = CombineGenes(generation.genes[index1], generation.genes[index2]);
		/*printf("newgene: ");
		new_gene.print();
		printf("made from:\n");
		generation.genes[index1].print();
		generation.genes[index2].print();*/
		generation.genes.push_back(new_gene);
	}
}

void MakeNextGeneration1(Generation1 &generation)
{
	float SURVIVAL_RATE = 0.4;
	unsigned int gene_starting_size = generation.genes.size();
	int index_to_crop = int(SURVIVAL_RATE * generation.genes.size());
	generation.sort_genes();
	generation.genes.resize(index_to_crop);

	/*generation.print();
	puts("-------");*/

	int genes_to_make = gene_starting_size - generation.genes.size();
	vector<Gene1> new_genes;
	for (unsigned int i=0; i<genes_to_make; i++) 
	{
		int index1 = rand() % generation.genes.size();
		int index2;
		do
		{
			index2 = rand() % generation.genes.size();
		} while (index1 == index2);
		Gene1 new_gene = CombineGenes1(generation.genes[index1], generation.genes[index2]);

		/*printf("newgene: ");
		new_gene.print();
		printf("made from:\n");
		generation.genes[index1].print();
		generation.genes[index2].print();*/

		new_genes.push_back(new_gene);
	}
	generation.genes.insert(generation.genes.end(), new_genes.begin(), new_genes.end());
	//generation.print();
}