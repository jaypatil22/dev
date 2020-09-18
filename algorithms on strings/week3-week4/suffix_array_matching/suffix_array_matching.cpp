#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using std::cin;
using std::string;
using std::vector;
using namespace std;

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

vector<int> compute_class(vector<int> order,vector<int> cl,int L) {
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


vector<int> BuildSuffixArray(const string& text) {
  vector<int> order(text.size());

  // write your code here
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


vector<int> FindOccurrences(const string& pattern, const string& text, const vector<int>& suffix_array) {
  vector<int> result;

  // write your code here
  int left = 0,right = text.size()-1,mid;
  bool flag =0;
  while(left <= right) {
    mid = left + (right - left)/2;
    int res = strncmp(&pattern[0],&text[suffix_array[mid]],pattern.size());
    if(res == 0) {
      result.push_back(suffix_array[mid]);
      flag = 1;
      break;
    }
    if(res < 0) right = mid - 1;
    else left = mid +1;
  }
  if(flag) {
    int current = mid - 1;
    while(current>0 && strncmp(&pattern[0],&text[suffix_array[current]],pattern.size())==0) {
      result.push_back(suffix_array[current]);
      current--;
    }
    current = mid + 1;
    while(current < text.size() && strncmp(&pattern[0],&text[suffix_array[current]],pattern.size())==0) {
      result.push_back(suffix_array[current]);
      current++;
    }
  }

  return result;
}

int main() {
  char buffer[100001];
  scanf("%s", buffer);
  string text = buffer;
  text += '$';
  vector<int> suffix_array = BuildSuffixArray(text);
  int pattern_count;
  scanf("%d", &pattern_count);
  vector<bool> occurs(text.length(), false);
  for (int pattern_index = 0; pattern_index < pattern_count; ++pattern_index) {
    scanf("%s", buffer);
    string pattern = buffer;
    vector<int> occurrences = FindOccurrences(pattern, text, suffix_array);
    for (int j = 0; j < occurrences.size(); ++j) {
      occurs[occurrences[j]] = true;
    }
  }
  for (int i = 0; i < occurs.size(); ++i) {
    if (occurs[i]) {
      printf("%d ", i);
    }
  }
  printf("\n");
  return 0;
}
