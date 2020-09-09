#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];

	Node ()
	{
		fill (next, next + Letters, NA);
	}

	bool isLeaf () const
	{
	    return (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA);
	}
};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}

vector<Node> makeTrie(const vector<string> patterns) {
	vector<Node> res;
	Node nn;
	res.push_back(nn);
	int count = 0;
	for(int i=0;i<patterns.size();i++) {
		int current = 0;
		for(int j=0;j<patterns[i].size();j++) {
			int letter = letterToIndex(patterns[i][j]);
			if(res[current].next[letter] == NA) {
				res[current].next[letter] = ++count;
				Node t;
				res.push_back(t);
				current = count;
			} else {
				current  = res[current].next[letter];
			}
		}
	}

	return res;
}


bool isPresent(vector<Node> &trie, string text) {
	int current = 0;
	int c =0;
	int letter = letterToIndex(text[c]);
	while(c<text.size()) {
		if(trie[current].isLeaf()) {
			return true;
		} else if(trie[current].next[letter] != NA) {
			current = trie[current].next[letter];
			c++;
			if(c < text.size()) {
				letter = letterToIndex(text[c]);
			} else {
				if(trie[current].isLeaf())
					return true;
				else
						return false;
			}
		} else {
			if (trie[current].isLeaf()) {
				return true;
			} else {
				return false;
			}
		}
	}
	return false;

}


vector <int> solve (const string& text, int n, const vector <string>& patterns)
{
	vector <int> result;
	vector<Node> trie = makeTrie(patterns);

	for(int i=0;i<text.size();i++) {
		if(isPresent(trie,text.substr(i,text.size()-i))) {
			result.push_back(i);
		}
	}

	// write your code here

	return result;
}

int main (void)
{
	string text;
	cin >> text;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (text, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
