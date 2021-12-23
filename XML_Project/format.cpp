#include "format.h"

string formatting(vector<string> t) {
	int time = 0;
	int open_no = 0;
	int close_no = 0;
	string str = "";
	for (unsigned int i = 0; i < t.size(); i++) {
		if (t[i][0] == '<' && (t[i][1] == '?' || t[i][1] == '!')) {
			str += t[i] + "\n";		//print output
		}
		else if (t[i][0] == '<' && !(t[i][1] == '/')) {
			open_no++;
			close_no = 0;
			if (open_no > 1) {
				time++;
			}
			for (int j = 0; j < time; j++) {
				str += "\t";		//print tab
			}
			str += t[i] + "\n";	//print output
		}
		else if (t[i][0] == '<' && t[i][1] == '/' && t[i-1][0]!='<') {
			close_no++;
			open_no = 0;
			for (int j = 0; j < time; j++) {
				str += "\t";		//print tab
			}
			str += t[i] + "\n";	//print output
			time--;
		}
		else if (t[i][0] == '<' && t[i][1] == '/' && t[i - 1][0] == '<') {
			close_no++;
			open_no = 0;
			if (close_no > 1) {
				time--;
			}
			for (int j = 0; j < time; j++) {
				str += "\t";		//print tab
			}
			str += t[i] + "\n";	//print output
		}
		else {
			for (int j = 0; j < time; j++) {
				str += "\t";		//print tab
			}
			str += t[i] + "\n";	//print output
		}
	}
	return str;
}
