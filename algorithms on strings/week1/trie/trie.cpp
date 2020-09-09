// #include <string>
// #include <iostream>
// #include <vector>
// #include <map>
//
// using std::map;
// using std::vector;
// using std::string;
//
// typedef map<char, int> edges;
// typedef vector<edges> trie;
//
// trie build_trie(vector<string> & patterns) {
//   trie t;
//   // write your code here
//   return t;
// }
//
// int main() {
//   size_t n;
//   std::cin >> n;
//   vector<string> patterns;
//   for (size_t i = 0; i < n; i++) {
//     string s;
//     std::cin >> s;
//     patterns.push_back(s);
//   }
//
//   trie t = build_trie(patterns);
//   for (size_t i = 0; i < t.size(); ++i) {
//     for (const auto & j : t[i]) {
//       std::cout << i << "->" << j.second << ":" << j.first << "\n";
//     }
//   }
//
//   return 0;
// }
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class trieNode
{
public:
	char val;
	vector<trieNode *> children;
	int parent,self;

	trieNode(char a,int parent,int self) : val(a), parent(parent), self(self) {}
};

void solve (vector<string> &input) {
	trieNode *root = new trieNode('0',-1,0);
	int count=1;
	for(int j=0;j<input.size();j++) {
		trieNode *current = root;
		for(int i=0;i<input[j].size();i++) {
			bool flag=0;
			for(int k=0;k<current->children.size();k++) {
				if(current->children[k]->val == input[j][i]) {
					current = current->children[k];
					flag = 1;
					break;
				}
			}
			if(flag == 1)
				continue;
			cout << current->self << "->" << count << ":" << input[j][i] << '\n';
			trieNode *nn = new trieNode(input[j][i],current->self,count);
			current->children.push_back(nn);
			current = nn;
			count++;
		}
	}
}

int main (void)
{
	vector<string> input;
	int n;
	cin >> n;
	input.resize(n);
	for(int i=0;i<n;i++) {
		cin >> input[i];
	}
	solve(input);
	return 0;
}
