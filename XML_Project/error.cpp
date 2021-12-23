// substring.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include"error.h"

int checking_errors(vector<string>& inp_vec, vector<string>& corrected_vec, vector<int>& error_vec)
{
	stack<string> s;
	string temp = "";
	int Error_count = 0;
	int current = 0;
	bool flag = false;
	for (unsigned int i = 0; i < inp_vec.size(); i++)
	{
		if (current == i - 2)
			flag = false;
		if ((inp_vec[i][0] == '<' && inp_vec[i][1] == '!') || (inp_vec[i][0] == '<' && inp_vec[i][1] == '?')) //first tag
		{
			corrected_vec.push_back(inp_vec[i]);
		}
		if (inp_vec[i][0] != '<')     // data
		{
			corrected_vec.push_back(inp_vec[i]);
		}
		if (inp_vec[i][0] == '<' && inp_vec[i][1] != '/' && inp_vec[i][1] != '!')   // opening
		{
			if (i != 0 && inp_vec[i - 1][0] != '<')  // opening with no tag befor it "error"
			{
				error_vec.push_back(i - 1);
				Error_count++;
				temp = s.top();
				temp.insert(1, "/");
				corrected_vec.push_back(temp);
				s.pop();
			}
			s.push(inp_vec[i]);                                                
			corrected_vec.push_back(inp_vec[i]);
		}
		if (inp_vec[i][0] == '<' && inp_vec[i][1] == '/')         // close tag
		{
			if (!s.empty()) 
			{
				string er = s.top();
				//inp_vec[i].erase(1, 1);
				if (Compare_Tags(er, inp_vec[i]))                // if tags are equal
				{
					s.pop();
					corrected_vec.push_back(inp_vec[i]);
				}
				else
				{
					current = i;
					string er = s.top();
					string app = er.insert(1, "/");
					corrected_vec.push_back(app);
					s.pop();
					if (!flag)
					{
						error_vec.push_back(i);
						Error_count++;
					}
					flag = true;
				}
			}
			else
			{
				string kor = inp_vec[i];
				kor.erase(kor.begin() + 1);
				corrected_vec.push_back(kor);
				corrected_vec.push_back(inp_vec[i]);

			}
		}
	}
	for (unsigned int i = 0; i < inp_vec.size(); i++)
	{
		if (s.empty())
			break;
		string m = s.top();
		m.insert(1, "/");
		corrected_vec.push_back(m);
		s.pop();
	}
	return Error_count;
}

//we check 2 kinds of errors
//1 if the start tag <open> is not proceded by a tag 
//for example if data <open> data 
//here we see that there is an error and we try to fix it by pushing to the corrected vector the top of the stack with / at index 1
//the second error is that the vector of data has a end tag that is not matching the top of the stack that contain the opening tags
// we fix it the same way as the first case
//then after the for loop finishes we make another for loop to make sure that the stack is empty
//if its not then it will add end tags matching the elements in the stack.