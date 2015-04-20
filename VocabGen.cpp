/*
* @Author: largelyfs
* @Date: Mon Mar 02 19:26:05 2015 +0800
* @Last Modified by:   largelymfs
* @Last Modified time: 2015-04-20 11:46:30
*/

#include <iostream>
#include <stdlib.h>
#include "VocabGen.h"
#include <assert.h>

VocabGen::VocabGen(const char* filename, int max_string):h(NULL),f(NULL), MAX_STRING(max_string){
	this->f = new FileReader(filename, this->MAX_STRING, 0);
	this->h = new HashMap();
	this->h->addWord("</s>",1);

}

VocabGen::~VocabGen(){
	if (this->h!=NULL) delete this->h;
	if (this->f!=NULL) delete this->f;
}

void VocabGen::buildVocab(){
	this->fNumber = 0;
	this->fsize.clear();
	char buf[this->MAX_STRING];
	char filenamebuf[this->MAX_STRING];
	FileReader *tmpf;
	while (this->f->hasWord()){
		this->f->getWord(filenamebuf);
		if (strlen(filenamebuf) != 1){
			tmpf = new FileReader(filenamebuf, this->MAX_STRING, 0);
			while (tmpf->hasWord()){
				tmpf->getWord(buf);
				this->h->addWord(buf, 1);
			}
			this->fsize.push_back(tmpf->fileSize());
			delete tmpf;
			this->fNumber++;
		}
		//skip the \n
		this->f->getWord(buf);
	}
	for (int i = 0; i < this->fNumber; i++)
		std::cout << this->fsize[i] << std::endl;
}

void VocabGen::reduceVocab(int min_count){
	this->h->reduce_vocab(min_count);
}

long long VocabGen::searchWord(char* word){
	return this->h->searchWordIndex(word);
}

long long VocabGen::size(){
	return this->h->size();
}

std::string& VocabGen::searchWordContent(int index){
	return this->h->searchWordContent(index);
}

long long VocabGen::searchWordCnt(int index){
	return this->h->searchWordCnt(index);
}

long long VocabGen::fileSize(int index){
	assert(index < this->fNumber);
	return this->fsize[index];
}

int VocabGen::fileNumber(){
	return this->fNumber;
}

long long VocabGen::totalWords(){
	return this->h->totalWords();
}
using namespace std;

// int main(){
// 	VocabGen *g = new VocabGen("test.txt", 100);
// 	g->buildVocab();
// 	g->reduceVocab(0);
// 	char s[2] = "I";
// 	std::cout << g->searchWord(s) << std::endl;
// 	std::cout << g->size() << std::endl;
// 	delete g;
//     return 0;
// }
