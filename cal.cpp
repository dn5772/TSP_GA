#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

vector<vector<double>> vertex;

inline double dist(vector<double> &x, vector<double> &y){
	return sqrt(pow(x[0] - y[0], 2) + pow(x[1] - y[1], 2));
}

int main(){
	ifstream data("TSP.csv");
    string line;

    while(getline(data,line)){
        stringstream lineStream(line);
        string cell;
        vector<double> row;
        while(getline(lineStream,cell,',')){
            row.push_back(stod(cell));
        }
        vertex.push_back(row);
    }

	data.close();

	ifstream path("ex.csv");

	vector<int> a;

	while (getline(path,line)){
		a.push_back(stoi(line));
	}

	double cost = 0;

	for (int i=0; i<999; i++){
		cost += dist(vertex[a[i]], vertex[a[i]]);
	}

	cost += dist(vertex[a[999]], vertex[a[0]]);

	cout << cost << endl;
	
}