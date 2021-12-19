#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <random>

#define S 250 // promising size

using namespace std;

vector<vector<double>> vertex;

inline double dist(vector<double> &x, vector<double> &y){
	return sqrt(pow(x[0] - y[0], 2) + pow(x[1] - y[1], 2));
}

///////////////////////  Class Path  //////////////////////////
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

	double get_cost();
	double get_bestcost();
	int get_bestindex();
	int get_x(int index);

	void redefine(vector<int> a);

	void cal_cost();

	bool operator> (Path& pa);
	bool operator>= (Path& pa);
	bool operator== (Path& pa);
};

Path::Path(){
	x.resize(1000);
	best_index = 0;
	tot_cost = 0;
	best_cost = 0;
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

double Path::get_cost(){return tot_cost;}

double Path::get_bestcost(){return best_cost;}

int Path::get_bestindex(){return best_index;}

int Path::get_x(int index){return x[index];}

void Path::redefine(vector<int> a){
	x.~vector();
	x = a;
}

void Path::cal_cost(){
	tot_cost = 0;
	best_index = 0;
	best_cost = 0;

	for (int i=0; i<S; i++){

		int city_1 = i;
		int city_2 = x[i];

		tot_cost += dist(vertex[city_1], vertex[city_2]);
	}

	best_cost = tot_cost;

	for (int i=S; i<1000; i++){
		int city_1 = i;
		int city_2 = x[i];

		int curdist = dist(vertex[city_1], vertex[city_2]);
		tot_cost += curdist;

		double a = best_cost + curdist - dist(vertex[i-S], vertex[x[i-S]]);

		if (a<best_cost){
			best_cost = a;
			best_index = i;
		}
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

bool Path::operator== (Path& pa){
	if (this->tot_cost == pa.tot_cost) {return true;}
	else {return false;}
}


//////////////////////////////////////////////////////





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

	Path p[10];

	vector<int> aa(1000);
	for (int i=0; i<999; i++){
		aa[i] = i+1;
	}
	aa[999] = 0;

	for (int i=0; i<10; i++){

	}


	data.close();
	return 0;
}