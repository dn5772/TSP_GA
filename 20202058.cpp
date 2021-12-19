#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <cmath>
#include <random>

#define S 250 // promising size

using namespace std;

vector<vector<double>> vertex;
double W[1000][1000];

inline double dist(vector<double> &x, vector<double> &y){
	return sqrt(pow(x[0] - y[0], 2) + pow(x[1] - y[1], 2));
}

///////////////////////  Class Path  //////////////////////////

class Path{
	private :
	double tot_cost;
	int best_index;
	double best_cost;


	public :
	vector<int> x;
	vector<double> cost;
	Path();
	Path(vector<int> a);
	~Path();

	double get_cost();
	double get_bestcost();
	int get_bestindex();

	void repath(vector<int> a);

	void cal_cost();

	bool operator> (Path& pa);
	bool operator>= (Path& pa);
	bool operator== (Path& pa);
};

Path::Path(){
	x.resize(1000);
	cost.resize(100);
	best_index = 0;
	tot_cost = 0;
	best_cost = 0;
}

Path::Path(vector<int> a){
	x = a;
	cost.resize(100);
	cal_cost();
}

Path::~Path(){
	// x.~vector();
}

double Path::get_cost(){return tot_cost;}

double Path::get_bestcost(){return best_cost;}

int Path::get_bestindex(){return best_index;}

void Path::repath(vector<int> a){
	x.~vector();
	x = a;
	cal_cost();
}

void Path::cal_cost(){
	tot_cost = 0;
	best_index = 0;
	best_cost = 0;
	double curcost = 0;

	int j = 0, k = 0;

	for (int i=0; i<S; i++){
		tot_cost += W[j][x[j]];
		cost[k] += W[j][x[j]];
		if ((i+1)%10 == 0){
			k++;
		}
		j = x[j];
	}

	best_cost = curcost = tot_cost;
	int firstIndex = 0;

	for (int i=S; i<1000; i++){
		int curdist = W[j][x[j]];
		tot_cost += curdist;
		
		cost[k] += curdist;
		if ((i+1)%10 == 0){
			k++;
		}


		curcost += curdist - W[firstIndex][x[firstIndex]];
		if (curcost<best_cost){
			best_cost = curcost;
			best_index = j;
		}

		j = x[j];
		firstIndex = x[firstIndex];
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

bool comper(Path a, Path b){
	return b>a;
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

	for (int i=0; i<1000; i++){
		for (int j=i+1; j<1000; j++){
			W[i][j] = W[j][i] = dist(vertex[i], vertex[j]);
		}
	}

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 999);

	list<Path> p;
	list<Path>::iterator itor = p.begin();

	vector<int> aa(1000);
	for (int i=0; i<999; i++){
		aa[i] = i+1;
	}
	aa[999] = 0;

	for (int i=0; i<10; i++){
		for (int j=0; j<2000; j++){
			int a = dis(gen);
			int b = dis(gen);

			int tmp = aa[a];
			aa[a] = aa[b];
			aa[b] = tmp;
		}

		Path pp(aa);
		p.push_back(pp);
	}

	p.sort(comper);

	for (itor=p.begin(); itor!=p.end(); itor++){
		printf("%.16f, %.16f\n", itor->get_cost(), itor->get_bestcost());
		double tcost = 0;
		for (int i=0; i<100; i++){tcost += itor->cost[i];}
		printf("%.16f ,\n", tcost);
	}

	data.close();
	return 0;
}