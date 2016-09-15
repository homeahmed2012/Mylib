#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int high;
struct stnode {
  stnode* ptr[5];
  int start;
  int end;
  stnode(int s, int e) {
    for (int i = 0; i < 5; ++i) {
      ptr[i] = NULL;
    }
    start = s;
    end = e;
  }
};

stnode *root;
int f(char ch){
	switch(ch){
		case 'A':
			return 1;
			break;
		case 'C':
			return 2;
			break;
		case 'G':
			return 3;
			break;
		case 'T':
			return 4;
			break;
		default:
			return 0;
			break;
	}
}
stnode* fun(stnode* child, string &str, int ind) {
  int s = child->start;
  while (s <= child->end && str.at(s) == str.at(ind)) {
    s++;
    ind++;
  }
  
  if (s <= child->end) { //not match before end
  	stnode* new_node = new stnode(child->start, s-1);
    child->start = s;
    new_node->ptr[f(str[ind])] = new stnode(ind, high);
    new_node->ptr[f(str[s])] = child;
    return new_node;
  } else if(child->ptr[f(str[ind])] == NULL){
  	child->ptr[f(str[ind])] = new stnode(ind, high);
  	return child;
  }else{
    child->ptr[f(str[ind])] = fun(child->ptr[f(str[ind])], str, ind);
    return child;
  }
}

void create(int ind, string &str) {
    
  if (root->ptr[f(str[ind])] == NULL) {
    root->ptr[f(str[ind])] = new stnode(ind, high);
    return;
  }
  root->ptr[f(str[ind])] = fun(root->ptr[f(str[ind])], str, ind);
}

void display(stnode* node, string &str) {
  if (node == NULL) return;
  if (node->start != -1) {
    for (int i = node->start; i <= node->end; i++) {
      cout << str.at(i);
    }
    cout << "\n";
  }
  for (int i = 0; i < 5; i++) {
    display(node->ptr[i], str);
  }
}

void ComputeSuffixTreeEdges(string& text) {
  root = new stnode(-1, -1);
  for(int i = 0; i < text.length(); i++){
  	create(i, text);
  }
  display(root, text);
}

int main() {
  //freopen("c.in", "r", stdin);
  //freopen("c.out", "w", stdout);
  string text;
  cin >> text;
  high = text.length()-1;
  ComputeSuffixTreeEdges(text);
  return 0;
}
