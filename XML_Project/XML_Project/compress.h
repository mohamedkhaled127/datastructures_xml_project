#ifndef COMPRESS_H
#define COMPRESS_H

#include "Headers.h"

vector<int> compress(string str);	
string decompress(vector<int> o_code);
void writeFile(string f, vector<int> a);
vector<int> readFile(string f);

#endif // COMPRESS_H
