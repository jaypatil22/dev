#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using namespace std;

string InverseBWT(const string& bwt) {
  string text = "";
  string nn = "";

  // write your code here
  int arr[256];
  memset(arr, 0, sizeof arr);
  for (size_t i = 0; i < bwt.size(); i++) {
    arr[bwt[i]]++;
  }

  for(int i=1;i<256;i++) {
    arr[i] += arr[i-1];
  }
  char firstr[bwt.size()+1];
  for(int i=0;i<bwt.size();i++) {
    firstr[arr[bwt[i]]--] = bwt[i];
  }
  for(int i=1;i<=bwt.size();i++) {
    nn += firstr[i];
  }
  int count[256];
  memset(count,0,sizeof count);
  vector<pair<int, int> > lastc;
  for(int i=0;i<bwt.size();i++) {
    lastc.push_back(make_pair(bwt[i],count[bwt[i]]++));
  }
  memset(count,0,sizeof count);
  map<pair<int,int>, int> m;
  for(int i=0;i<bwt.size();i++) {
    m.insert(make_pair(make_pair(nn[i],count[nn[i]]++),i));
  }
  int last = 0;
  for(int i=0;i<bwt.size();i++) {
    text += nn[last];
    last = m[lastc[last]];
  }
  reverse(text.begin(),text.end());

  return text;
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
