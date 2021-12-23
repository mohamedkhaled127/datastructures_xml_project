#include "Tree.h"

Tree::Tree() {
    root = nullptr;
}


bool Tree::is_empty() {
    return root == nullptr;
}

int Tree::count_children(TreeNode* node) {
    return node->children.size();
}

int Tree::Get_Siblings(TreeNode* node) {
    if (node->Parent == nullptr)
        return 0;
    else
        return Tree::count_children(node->Parent) - 1;
}

int Tree::count_similiar(TreeNode* node, string tag_n, stack<TreeNode*>& Similiars) {
    int inc_num = 0;
    for (int i = 0; i < count_children(node); i++) {
        if (node->children[i]->Tag_Name == tag_n) {
            Similiars.push(node->children[i]);
            inc_num++;
        }
    }
    return inc_num;
}

int Tree::count_attributes(TreeNode* node) {
    return node->attributes.size();
}

void Tree::insert_node_2_tree(vector<string> Data, vector<int> Error) {
    TreeNode* current_N = root;
    int inc_num = 0;
    for (unsigned int i = 0; i < Data.size(); i++) {
        // Adding Node with Openning Tag 
        if (Get_Type(Data[i]) == 'O') {
            // If Root is empty (First element comes)
            if (current_N == nullptr) {
                current_N = new TreeNode;
                root = current_N;
                current_N->insert_TreeNode(Data[i]);
                current_N->Parent = nullptr;
                if (!Error.empty()) {
                    if (Error[inc_num] == i) {
                        current_N->Error = true;
                        inc_num++;
                    }
                }
            }
            // Adding General Node
            else {
                TreeNode* child = new TreeNode;
                child->insert_TreeNode(Data[i]);
                child->Parent = current_N;
                current_N->children.push_back(child);
                current_N->Data = false;
                current_N->Tag_Value = "";
                current_N = child;
                if (!Error.empty()) {
                    if (Error[inc_num] == i) {
                        current_N->Error = true;
                        inc_num++;
                    }
                }
            }
        }
        // Adding Data(Tag Value) to current Node
        else if (Get_Type(Data[i]) == 'V') {
            current_N->Tag_Value = Data[i];
            current_N->Data = true;
        }
        // Return to Parent Node when comes closing Tag
        else if (Get_Type(Data[i]) == 'C') {
            current_N = current_N->Parent;
            if (!Error.empty()) {
                if (Error[inc_num] == i) {
                    current_N->Error = true;
                    inc_num++;
                }
            }
        }
    }
}

TreeNode* Tree::get_Root() const
{
    return root;
}

void Tree::set_Root(TreeNode* value)
{
    root = value;
}

string Tree::ptr_xml_2_json(TreeNode* node, string& str, bool x, int level) {
    stack<TreeNode*> Similiars;
    int child_count = count_children(node);
    int attr_count = count_attributes(node);
    int sib_count = Get_Siblings(node);
    //int flag=g;
    if (x) {
        str += "\n";
        str += Tabs(level);
    }
    str += "\"" + node->Tag_Name + "\": ";
    if (child_count > 0) str += "{";
    if (attr_count >= 0)
    {
        for (int i = 0; i < attr_count; i++)
        {
            if (i == 0) { str += "\n"; }
            str += Tabs(level + 1);
            str += "\"";
            str += 64;
            str += node->attributes[i].Name + "\"" + ": ";
            str += "\"" + node->attributes[i].Value + "\"";
            str += ",";
            if (i != attr_count - 1) { str += "\n"; }
        }
    }
    if (node->Tag_Value != "") {
        str += "\"" + node->Tag_Value + "\"";
        if (sib_count > 0) {//h>1
            str += ",";
            str += "\n";
        }
    }
    if (child_count == 0)	return str;
    for (int i = 0; i < child_count; i++) {
        int m = count_similiar(node, node->children[i]->Tag_Name, Similiars);
        if (m == 1) {
            Similiars.pop();
            ptr_xml_2_json(node->children[i], str, true, level + 1);
        }
        else if (m > 1 && (node->children[i]->visited == false)) {
            form_json(Similiars, child_count, str, level + 1);
        }
    }
    if (child_count > 0)	str += Tabs(level + 1) + "}\n";
    return str;

}

void Tree::form_json(stack<TreeNode*>& Similiars, int& child_count, string& obj, int level) {
    int i = 0;
    obj += "\n" + Tabs(level) + "\"" + Similiars.top()->Tag_Name + "\" :";
    obj += "\n" + Tabs(level) + "[";
    obj += "\n";
    while (!(Similiars.empty())) {
        int n = count_attributes(Similiars.top());
        int f = count_children(Similiars.top());
        if (i == 0) { obj += Tabs(level + 1); }
        obj += "{";
        if (n >= 0) {
            for (int i = 0; i < n; i++) {
                if (i == 0) { obj += "\n"; }
                obj += Tabs(level + 1);
                obj += "\"";
                obj += 64;
                obj += Similiars.top()->attributes[i].Name + "\"";
                obj += "\"" + Similiars.top()->attributes[i].Value + "\"";
                obj += ",";
                if (i != n - 1) { obj += "\n"; }
            }
        }
        if (f > 0) {
            for (int i = 0; i < f; i++) {
                ptr_xml_2_json(Similiars.top()->children[i], obj, false, level + 1);
            }
        }
        if (Similiars.top()->Tag_Value == "") {
            obj += "}";
        }
        else {
            obj += "\"";
            obj += 35;
            obj += "text";
            obj += "\"";
            obj += ": ";
            obj += "\"" + Similiars.top()->Tag_Value + "\"" + "}";
        }
        Similiars.top()->visited = true;
        Similiars.pop();
        i++;
        if (!Similiars.empty()) obj += ", ";
    }
    obj += "\n" + Tabs(level) + "]\n";
}

string Tree::xml_2_json() {
    string str = "";
    return "{\n" + Tree::ptr_xml_2_json(Tree::root, str, true, 1) + "}\n";
}

string Tree::Pre_Order() {
    string str = "";
    Tree::Pre_Order_Traverse(root, str, 0);
    return str;
}

void Tree::Pre_Order_Traverse(TreeNode* node, string& str, int level) {
    if (node == nullptr) return;
    if (node->Data == true) {
        str += Tabs(level) + "<" + node->Tag_Name;
        if (node->attributes.size() != 0) str += " ";
        for (unsigned i = 0; i < node->attributes.size(); i++) {
            str += "\"" + node->attributes[i].Name + "\"=\"" + node->attributes[i].Value + "\"";
            if (i < node->attributes.size() - 1) str += " ";
        }
        str += ">" + node->Tag_Value + "</" + node->Tag_Name + ">\n";
    }
    else {
        str += Tabs(level) + "<" + node->Tag_Name;
        if (node->attributes.size() != 0) str += " ";
        for (unsigned i = 0; i < node->attributes.size(); i++) {
            str += "\"" + node->attributes[i].Name + "\"=\"" + node->attributes[i].Value + "\"";
            if (i < node->attributes.size() - 1) str += " ";
        }
        str += ">\n";
        for (unsigned int i = 0; i < node->children.size(); i++) {
            Tree::Pre_Order_Traverse(node->children[i], str, level + 1);
        }
        str += Tabs(level) + "</" + node->Tag_Name + ">\n";
    }
}

