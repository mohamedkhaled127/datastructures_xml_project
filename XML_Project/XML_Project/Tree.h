#pragma once
#ifndef TREE_H
#define TREE_H

#include "Headers.h"
#include "aux_func.h"

struct Attribute {
	string Name, Value;
};

class TreeNode {
public:
	bool Data, Error, visited;
	vector<TreeNode*> children;
	vector<Attribute> attributes;
	string Tag_Name, Tag_Value;
	TreeNode* Parent;

	TreeNode(string n = "", string v = "") {
		Tag_Name = n;
		Tag_Value = v;
		if (Tag_Value == "")	Data = false;
		else Data = true;
		Error = false;
		visited = false;
	}

	void insert_TreeNode(string Open_Tag) {
		Tag_Name = "";
		string temp_str;
		Attribute temp_atr;
		for (unsigned int i = 1; i < Open_Tag.length(); i++) {
			while (Open_Tag[i] != ' ' && Open_Tag[i] != '>') {
				Tag_Name += Open_Tag[i++];
			}
			while (i + 1 < Open_Tag.length()) {
				temp_str = "";
				while (Open_Tag[i] == ' ')	i++;
				while (Open_Tag[i] != ' ' && Open_Tag[i] != '=')	temp_str += Open_Tag[i++];
				temp_atr.Name = temp_str;
				temp_str = "";
				while (Open_Tag[i] == ' ' || Open_Tag[i] == '=' || Open_Tag[i] == '\'' || Open_Tag[i] == '"' || Open_Tag[i] == '\\') i++;
				while (Open_Tag[i] != '\'' && Open_Tag[i] != '"' && Open_Tag[i] != '\\')	temp_str += Open_Tag[i++];
				temp_atr.Value = temp_str;
				i++;
				attributes.push_back(temp_atr);
			}
		}
	}
};

class Tree {
private:
	TreeNode* root;
	string ptr_xml_2_json(TreeNode* node, string& obj, bool x, int level);
	void Pre_Order_Traverse(TreeNode* node, string& str, int level);
public:
	Tree();
	bool is_empty();
	int count_children(TreeNode* node);
	int count_similiar(TreeNode* node, string tag_n, stack<TreeNode*>& Similiars);
	int count_attributes(TreeNode* node);
	void insert_node_2_tree(vector<string> Data, vector<int> Error);
	void form_json(stack<TreeNode*>& Similiars, int& g, string& obj, int level);
	string xml_2_json();
	int Get_Siblings(TreeNode* node);
	TreeNode* get_Root() const;
	void set_Root(TreeNode* value);
	string Pre_Order();
};

#endif // TREE_H
