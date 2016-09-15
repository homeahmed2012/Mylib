#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int high, hash_ind;
struct stnode {
  stnode* ptr[6];
  int start;
  int end;
  stnode(int s, int e) {
    for (int i = 0; i < 6; ++i) {
      ptr[i] = NULL;
    }
    start = s;
    end = e;
  }
};

stnode* root;
int f(char ch) {
  switch (ch) {
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
    case '#':
      return 5;
      break;
    default:
      return 0;
      break;
  }
}
stnode* fun(stnode* child, string& str, int ind) {
  int s = child->start;
  while (s <= child->end && str.at(s) == str.at(ind)) {
    s++;
    ind++;
  }

  if (s <= child->end) {  // not match before end
    stnode* new_node = new stnode(child->start, s - 1);
    child->start = s;
    new_node->ptr[f(str[ind])] = new stnode(ind, high);
    new_node->ptr[f(str[s])] = child;
    return new_node;
  } else if (child->ptr[f(str[ind])] == NULL) {
    child->ptr[f(str[ind])] = new stnode(ind, high);
    return child;
  } else {
    child->ptr[f(str[ind])] = fun(child->ptr[f(str[ind])], str, ind);
    return child;
  }
}

bool my_func(pair<int, int> a, pair<int, int> b){
  return (a.second-a.first) < (b.second-b.first);
}
void create(int ind, string& str) {
  if (root->ptr[f(str[ind])] == NULL) {
    root->ptr[f(str[ind])] = new stnode(ind, high);
    return;
  }
  root->ptr[f(str[ind])] = fun(root->ptr[f(str[ind])], str, ind);
}
vector<pair<int, int> > candi;

bool solve(stnode* node, string& str, int len) {
  if (node->end == high && node->start < hash_ind) {  // leaf
    candi.push_back(make_pair(node->start - len, node->start));
    return true;
  }else if(node->end == high){
    return (node->start == hash_ind);
  }else {
    bool b = true;
    for (int i = 0; i < 6; i++) {
      if(node->ptr[i] != NULL){
        int my_len = node->end-node->start +1;
        if(node->start == -1) my_len = 0;
        b &= solve(node->ptr[i], str, my_len+len);
      }
      
    }
    if(b){
      candi.push_back(make_pair(node->start-len,node->start));
    }
    return b;
  }

}


void ComputeSuffixTreeEdges(string& text) {
  root = new stnode(-1, -1);
  for (int i = 0; i < text.length(); i++) {
    create(i, text);
  }
  solve(root, text, 0);
  sort(candi.begin(), candi.end(), my_func);
}

int main() {
  //freopen("c.in", "r", stdin);
  //freopen("c.out", "w", stdout);
  string text1, text2, text;
  cin >> text1 >> text2;
  text = text1 + "#" + text2 + "$";
  high = text.length() - 1;
  hash_ind = text1.length();
  ComputeSuffixTreeEdges(text);
  pair<int, int> small = candi[0];
  for(int i= small.first; i <= small.second; i++)
    cout << text[i];
  cout << "\n";
  return 0;
}
