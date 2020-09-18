#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;

void compute_prefix_array(vector<int> &prefix_array,string &text) {
  prefix_array.push_back(0);
  int order = 0;
  for(int i=1;i<text.size();i++) {
    while(order > 0 && text[order] != text[i]) {
      order = prefix_array[order-1];
    }
    if(text[i] == text[order])
      order = order + 1;
    else
      order = 0;
    prefix_array.push_back(order);
  }
}

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where
// the pattern starts in the text.
vector<int> find_pattern(const string& pattern, const string& text) {
  vector<int> result;
  // Implement this function yourself
  string text1 = pattern + "$" + text;
  vector<int> prefix_array;
  compute_prefix_array(prefix_array,text1);
  for(int i=pattern.size();i < prefix_array.size();i++) {
    if(prefix_array[i] >= pattern.size()) {
      result.push_back(i-2*pattern.size());
    }
  }
  return result;
}

int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}
