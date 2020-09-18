#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

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

void printSuffixTree(Node *root, const string &text, int depth){
  for(int i=0;i<root->next.size();i++){
    cout<< depth << " " << i << " " << text.substr(root->edges[i].first,root->edges[i].second)<<endl;
    printSuffixTree(root->next[i],text,depth+1);
  }
}

bool shortest_unstring(Node *root, int p_len, int q_len,int &mini, int &start) {
	for(int i=0;i<root->next.size();i++) {
		if(root->edges[i].first<p_len) {
			if(!shortest_unstring(root->next[i],p_len,q_len,mini,start)) {
				start = root->edges[i].first;
				int current = root->edges[i].second + root->edges[i].first;
				current = (current > p_len)?p_len:current;
				if(current <mini) {
					mini = current;
				}
			} else if(root->edges[i].first > p_len) {
				return true;
			}
		}
	}
	return false;
}

// Node *shortest_unstring(Node *root, int p_len, int q_len, int &mini, int &start) {
//
// 	return nullptr;
//
// }

string solve (string p, string q)
{
	string result = p;
	string text = p + '#' + q + '$';

	Node *root = new Node;
	for(int i=0;i<text.size();i++) {
		update(root,text,i);
	}
	int mini = 10000, start=0;
	printSuffixTree(root,text,0);
	shortest_unstring(root,p.size(),q.size(),mini,start);
	cout << mini << "\n";
	//result = text.substr(start, mini);
	return result;
}

int main (void)
{
	ios::sync_with_stdio(false);
	string p;
	cin >> p;
	string q;
	cin >> q;

	string ans = solve (p, q);

	cout << ans << endl;

	return 0;
}
