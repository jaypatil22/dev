#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;
using std::make_pair;
using std::pair;

struct Node {
	vector<pair<int, int> > edges;
	vector<Node*> next;
};

int getCommonStrLen(const string &text, int startpos1, int startpos2, int stringLen) {
	int same = 0;
	while(text[startpos1+same] == text[startpos2+same]) {
		same++;
		if((same==stringLen) || (startpos2 + same) == text.size())
			break;
	}

	return same;
}

void update(Node *root, const string &text, int subStri) {
	if(subStri >= text.size()) {
		return;
	}
	for(int i=0;i<root->next.size();i++) {
		int starting = root->edges[i].first;
		int commonStrLen = getCommonStrLen(text,starting, subStri,root->edges[i].second);
		if((commonStrLen>0) && (commonStrLen<root->edges[i].second)) {
			Node *oldNode = root->next[i];
			Node *nn = new Node;
			pair<int, int> partOldEdge (starting+commonStrLen, root->edges[i].second-commonStrLen);
			pair<int, int> nnEdge (subStri+commonStrLen,text.size()-subStri-commonStrLen);
			Node *middle = new Node;
			middle->next.push_back(oldNode);
			middle->next.push_back(nn);
			middle->edges.push_back(partOldEdge);
			middle->edges.push_back(nnEdge);
			root->next[i] = middle;
			root->edges[i].second = commonStrLen;
			return;
		} else if(commonStrLen==root->edges[i].second) {
			Node *nextNode = root->next[i];
			update(nextNode, text, subStri+commonStrLen);
			return;
		} else if((commonStrLen==0) && (i==root->next.size()-1)) {
			Node *newNode = new Node;
			root->next.push_back(newNode);
			pair<int, int> newEdge(subStri, text.size()-subStri);
			root->edges.push_back(newEdge);
			return;
		}
	}
	Node *nextNode = new Node;
	root->next.push_back(nextNode);
	pair<int, int> stringIndex (subStri,text.size()-subStri);
	root->edges.push_back(stringIndex);
	return;
}

void getSubStrings(Node *root, const string &text, vector<string> &result) {
	for(int i=0;i<root->next.size();i++) {
		result.push_back(text.substr(root->edges[i].first,root->edges[i].second));
		Node *nextNode = root->next[i];
		getSubStrings(nextNode, text,result);
	}
}

// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding
// substrings of the text) in any order.
vector<string> ComputeSuffixTreeEdges(const string& text) {
  vector<string> result;
  // Implement this function yourself
	Node *root = new Node;
	for(int i=0;i<text.size();i++) {
		update(root,text,i);
	}
	getSubStrings(root,text,result);
  return result;
}

int main() {
  string text;
  cin >> text;
  vector<string> edges = ComputeSuffixTreeEdges(text);
  for (int i = 0; i < edges.size(); ++i) {
    cout << edges[i] << endl;
  }
  return 0;
}
