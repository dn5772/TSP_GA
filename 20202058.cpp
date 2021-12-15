#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

double dist(vector<double> &x, vector<double> &y){
	return sqrt(pow(x[0] - y[0], 2) + pow(x[1] - y[1], 2));
}

int main(){
	ifstream fs;
	string f_buf, s_buf;

	ifstream data("TSP.csv");
    string line;
    vector<vector<double>> arr;
    while(getline(data,line)){
        stringstream lineStream(line);
        string cell;
        vector<double> row;
        while(getline(lineStream,cell,',')){
            row.push_back(stod(cell));
        }
        arr.push_back(row);
    }


	// for (int i=0; i<1000; i++){
	// 	printf("%.16f %.16f\n", arr[i][0], arr[i][1]);
	// }

	printf("%.16f \n", dist(arr[0], arr[1]));
	
	fs.close();

	return 0;
}