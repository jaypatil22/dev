#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using namespace std;

string BWT(const string& text) {
  string result = "";
  vector<string> m;
  // write your code here
  for(int i=0;i<text.size();i++) {
    string n = "";
    for(int j=0;j<text.size();j++) {
      n += text[(i+j)%text.size()];
    }
    m.push_back(n);
  }

  stable_sort(m.begin(),m.end());

  for(auto t : m) {
    result += t[t.size()-1];
  }

  return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}
