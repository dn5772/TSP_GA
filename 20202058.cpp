#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

double arr[1000][2];

int main(){
	ifstream fs;
	string f_buf, s_buf;
	int i = 0;

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


	for (i=0; i<1000; i++){
		printf("%.16f %.16f\n", arr[i][0], arr[i][1]);
		// cout << arr[i][0] << " " << arr[i][1] << endl;
	}
	
	fs.close();

	return 0;
}