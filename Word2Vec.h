

#ifndef WORD2VEC_H
#define WORD2VEC_H

#include "embedding.h"
#include "VocabGen.h"
#include "ExpTable.h"
#include <math.h>

// Solution Class
class Word2Vec{
public:
	Word2Vec(	const char* filename,
				int min_count, int window,
				int size, double alpha,
				double min_alpha, int negative,
				int thread_number, double subsampling,
				double lambda, int iteration);
	void resetWeights();								// reset the weights
	void inittable();									// sample table
	void saveClusterModel(const char* filename);				// output to the file
	void saveEmbeddingModel(const char* filename);
	void trainModel();									// train

	friend void* trainModelThread(void *id);			// thread to train the whole model

	~Word2Vec();
private:
	VocabGen* v;
	RandomGen* r;
	ExpTable* e;
	int *table;
	int layer1_size, window_size, min_count, negative, thread_number, iteration;
	long long now_total_words, word_number, tablesize, filesize, total_words, word_counts_actual, total_train_words;
	double alpha, min_alpha, subsampling, lambda;
	char* filename, *indexname;
	clock_t  start;
	std::vector<Embedding*> globalembeddings;
	std::vector< std::vector<Embedding*> > senseembeddings;
	std::vector< std::vector<Embedding*> > clusterembeddings;
	std::vector< int > clusternumber;
	std::vector< std::vector<long long> > wordfreq;
	pthread_mutex_t *mutex;
};

#endif
