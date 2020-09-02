#include <iostream>
#include <vector>

using namespace std;

vector<vector<int> > a,b,res;

void multiply(int r) {
  for(int i=0;i<b[0].size();i++) {
    for(int j=0;j<b.size();j++) {
      res[r][i] += a[r][j]*b[j][i];
    }
  }
}

void printres() {
  for(int i=0;i<res.size();i++) {
    for(int j=0;j<res[i].size();j++) {
      cout << res[i][j] << "\t";
    }
    cout << "\n";
  }
}

int main() {

	int r1,r2,c1,c2;
	cout << "enter dimensions of matrix a : \n";
	cin >> r1 >> c1;
	cout << "enter dimensions of matrix b : \n";
	cin >> r2 >> c2;

	if(c1 != r2) {
	   cout << "multiplication not possible !";
	} else {
	   a.resize(r1,vector<int> (c1,0));
     b.resize(r2,vector<int> (c2,0));
     res.resize(r1,vector<int> (c2,0));
     cout << "enter a matrix : ";
     for(int i=0;i<r1;i++) {
       for(int j=0;j<c1;j++) {
         cin >> a[i][j];
       }
     }

     cout << "enter b matrix : ";
     for(int i=0;i<r2;i++) {
       for(int j=0;j<c2;j++) {
         cin >> b[i][j];
       }
     }

     for(int i=0;i<r1;i++) {
       cout << "multiplication of row : " << i << "\n";
       multiply(i);
       printres();
     }
	}

  return 0;
}
