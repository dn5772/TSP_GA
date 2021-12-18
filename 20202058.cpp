#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>

using namespace std;

vector<vector<double>> vertex;

inline double dist(vector<double> &x, vector<double> &y){
	return sqrt(pow(x[0] - y[0], 2) + pow(x[1] - y[1], 2));
}

class Path{
	private :
	vector<int> x;
	double tot_cost;
	int best_index;
	double best_cost;

	public :
	Path();
	Path(vector<int> a);
	~Path();

	double getcost();
	int get_x(int index);

	void cal_cost();

	bool operator> (Path& pa);
	bool operator>= (Path& pa);
};

Path::Path(){
	x.resize(1000);
	best_index = 0;
	tot_cost = 0;
	best_cost - 0;
}

Path::Path(vector<int> a){
	x = a;
	best_index = 0;
	tot_cost = 0;
	best_cost = 0;
	cal_cost();
}

Path::~Path(){
	x.~vector();
}

double Path::getcost(){return tot_cost;}

int Path::get_x(int index){return x[index];}

void Path::cal_cost(){
	tot_cost = dist(vertex[x[0]], vertex[x[999]]);
	for (int i=0; i<999; i++){
		int city_1 = x[i];
		int city_2 = x[i+1];

		tot_cost += dist(vertex[city_1], vertex[city_2]);
	}
}

bool Path::operator> (Path& pa){
	if (this->tot_cost > pa.tot_cost) {return true;}
	else {return false;}
}

bool Path::operator>= (Path& pa){
	if (this->tot_cost < pa.tot_cost) {return false;}
	else {return true;}
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

	// for (int i=0; i<1000; i++){
	// 	printf("%.16f %.16f\n", arr[i][0], arr[i][1]);
	// }

	printf("%.16f \n", dist(vertex[0], vertex[1]));
	
	data.close();

	return 0;
}