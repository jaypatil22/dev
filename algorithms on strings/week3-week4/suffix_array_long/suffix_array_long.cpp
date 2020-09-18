#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

vector<int> compute_class(const string &text,vector<int> &order) {
  vector<int> cl(text.size(),0);
  cl[order[0]] = 0;
  for(int i=1;i<text.size();i++) {
    char c = text[order[i]],prev = text[order[i-1]];
    if(c != prev) {
      cl[order[i]] = cl[order[i-1]] + 1;
    } else {
      cl[order[i]] = cl[order[i-1]];
    }
  }
  return cl;
}

vector<int> sort_doubled(const string text, int L, vector<int> order,vector<int> cl) {
  vector<int> new_order(text.size(),0);
  vector<int> count(text.size(),0);
  for(int i=0;i<cl.size();i++) {
    count[cl[i]] = count[cl[i]] +1;
  }
  for(int i=1;i<cl.size();i++) {
    count[i] += count[i-1];
  }
  for(int i=text.size()-1;i>=0;i--) {
    int start = (order[i] - L +text.size()) % text.size();
    int cla = cl[start];
    count[cla] = count[cla] - 1;
    new_order[count[cla]] = start;
  }
  return new_order;
}

vector<int> compute_class(vector<int> &order,vector<int> cl,int L) {
  int n = order.size();
  vector<int> new_class(n,0);
  new_class[order[0]] = 0;
  for(int i=1;i<n;i++) {
    int current = order[i],prev = order[i-1];
    int mid = (current + L)%n,mid_prev = (prev+L)%n;
    if(cl[current] != cl[prev] || cl[mid] != cl[mid_prev]) {
      new_class[current] = new_class[prev] + 1;
    } else {
      new_class[current] = new_class[prev];
    }
  }
  return new_class;
}

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> BuildSuffixArray(const string& text) {
  vector<int> result;
  // Implement this function yourself
  vector<int> order(text.size(),0);
  vector<int> cl;
  vector<int> count(256,0);
  for(int i=0;i<text.size();i++) {
    count[text[i]]++;
  }
  for(int i=1;i<count.size();i++) {
    count[i] += count[i-1];
  }
  for(int i =text.size()-1;i>= 0;i--) {
    int ch = text[i];
    count[ch] = count[ch] - 1;
    order[count[ch]] = i;
  }
  cl = compute_class(text,order);
  int L = 1;
  while(L < text.size()) {
    order = sort_doubled(text,L,order,cl);
    cl = compute_class(order,cl,L);
    L *= 2;
  }
  return order;
}

int main() {
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}
