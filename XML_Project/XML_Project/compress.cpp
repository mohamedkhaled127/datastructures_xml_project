//Encoding function need string that is to be encoded
#include "compress.h"

vector<int> compress(string str)
{
	unordered_map<string, int> code_table;
	for (int i = 0; i <= 255; i++) {
		string single_char = "";
		single_char += char(i);
		code_table[single_char] = i;
	}

	string p = "", c = "";
	p += str[0];
	int sequ = 256;
	vector<int> out_sequ;
    for (unsigned int i = 0; i < str.length(); i++) {
		if (i != str.length() - 1)
			c += str[i + 1];
		if (code_table.find(p + c) != code_table.end()) {
			p = p + c;
		}
		else {
			out_sequ.push_back(code_table[p]);
			code_table[p + c] = sequ;
			sequ++;
			p = c;
		}
		c = "";
	}
	out_sequ.push_back(code_table[p]);
	return out_sequ;
}

string decompress(vector<int> o_code)
{
	string out = "";
	unordered_map<int, string> code_table;
	for (int i = 0; i <= 255; i++) {
		string single_char = "";
		single_char += char(i);
		code_table[i] = single_char;
	}
	int old_sequ = o_code[0], n;
	string s = code_table[old_sequ];
	string c = "";
	c += s[0];
	cout << s;
	int no_seq = 256;
    for (unsigned int i = 0; i < o_code.size() - 1; i++) {
		n = o_code[i + 1];
		if (code_table.find(n) == code_table.end()) {
			s = code_table[old_sequ];
			s = s + c;
		}
		else {
			s = code_table[n];
		}
		out += s;
		c = "";
		c += s[0];
		code_table[no_seq] = code_table[old_sequ] + c;
		no_seq++;
		old_sequ = n;
	}
	return out;
}
//Function to write the encoded values to .dat file
void writeFile(string f,vector<int> a) {
	ofstream file(f, ios::binary | ios::out);
    for (unsigned int i = 0; i < a.size(); i++) {
		int num = a[i];
		file.write((char *)&num, sizeof(int));
	}
	file.close();
}
//Function to read the encoded values to .dat file
vector<int> readFile(string f) {
	ifstream file(f, ios::binary | ios::in);
	vector<int>b;
	while (!file.eof()) {
		int num;
		file.read((char *)&num, sizeof(int));
		b.push_back(num);
	}
	file.close();
	return b;
}
