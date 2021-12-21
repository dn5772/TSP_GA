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
	int firstIndex;
	int lastIndex;
	double best_cost;


	public :
	vector<int> x;
	// vector<double> cost;
	Path();
	Path(vector<int> a);
	~Path();

	double get_cost();
	double get_bestcost();
	int get_firstIndex();
	int get_lastIndex();

	void repath(vector<int> a);

	void cal_cost();

	bool operator> (Path& pa);
	bool operator>= (Path& pa);
	bool operator== (Path& pa);
};

Path::Path(){
	x.resize(1000);
	// cost.resize(100);
	firstIndex = -1;
	lastIndex = -1;
	tot_cost = 0;
	best_cost = 0;
}

Path::Path(vector<int> a){
	x.swap(a);
	// cost.resize(100);
	cal_cost();
}

Path::~Path(){
	// x.~vector();
}

double Path::get_cost(){return tot_cost;}

double Path::get_bestcost(){return best_cost;}

int Path::get_firstIndex(){return firstIndex;}

int Path::get_lastIndex(){return lastIndex;}

void Path::repath(vector<int> a){
	x.swap(a);
	cal_cost();
}

void Path::cal_cost(){
	printf("index sum : ");
	tot_cost = 0;
	firstIndex = 0;
	lastIndex = S-1;
	best_cost = 0;
	double curcost = 0;

	int totsum=0;

	int j = 0, k = 0;

	for (int i=0; i<S; i++){
		totsum+=j;
		tot_cost += W[j][x[j]];
		j = x[j];
	}

	best_cost = curcost = tot_cost;
	lastIndex = j;

	int newfirst = 0;
	for (int i=S; i<1000; i++){
		totsum+=j;
		int curdist = W[j][x[j]];
		tot_cost += curdist;

		curcost = curcost + curdist - W[newfirst][x[newfirst]];

		if (curcost<best_cost){
			best_cost = curcost;
			firstIndex = x[newfirst];
			lastIndex = x[j];
		}
		j = x[j];
		newfirst = x[newfirst];
	}

	printf("%d\n", totsum);
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

bool comper(Path &a, Path &b){
	return b>a;
}

double checkCost(Path &pa, int index){
	double costSum = 0.0;
	for (int i=0; i<10; i++){
		costSum += W[index][pa.x[index]];
		index = pa.x[index];
	}
	return costSum;
}

Path crossover(Path &a, Path &b){  // a < b
	vector<int> newX;
	newX.assign(1000, -1);

	int totsum=0;
	
	int index = a.get_firstIndex();

	for (int i=0; i<S; i++){
		totsum+=index;
		newX[index] = a.x[index];
		index = a.x[index];
	}

	for (int k=0; k<75; k++){
		double a_cost = checkCost(a, index);
		double b_cost = checkCost(b, index);

		if (a_cost < b_cost){
			for (int i=0; i<10; i++){
				totsum+=index;
				if (newX[a.x[index]] == -1){
					newX[index] = a.x[index];
					index = a.x[index];
				}else if (newX[b.x[index]] == -1){
					newX[index] = b.x[index];
					index = b.x[index];
				}else {
					double minimum = 200;
					int minindex = a.get_firstIndex();
					for (int j=0; j<1000; j++){
						if ((W[index][j]<minimum)&&(index!=j)&&(newX[j]==-1)){
							minimum = W[index][j];
							minindex = j;
						}
					}
					newX[index] = minindex;
					index = minindex;
				}
			}
		}else {
			for (int i=0; i<10; i++){
				totsum += index;
				if (newX[b.x[index]] == -1){
					newX[index] = b.x[index];
					index = b.x[index];	
				}else if (newX[a.x[index]] == -1){
					newX[index] = a.x[index];
					index = a.x[index];
				}else {
					double minimum = 200;
					int minindex = a.get_firstIndex();
					for (int j=0; j<1000; j++){
						if ((W[index][j]<minimum)&&(index!=j)&&(newX[j]==-1)){
							minimum = W[index][j];
							minindex = j;
						}
					}
					newX[index] = minindex;
					index = minindex;
				}
			}
		}
	}
	// for (int i=0; i<1000; i++){
	// 	printf("%d -> ", newX[i]);
	// }
	printf("sum : %d \n", totsum);

	Path pa(newX);
	return pa;
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

	list<Path> p;
	list<Path>::iterator itor = p.begin();
	list<Path>::iterator itor2;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 999);

	vector<int> aa;
	// for (int i=0; i<999; i++){
	// 	aa.push_back(i+1);
	// }
	// aa.push_back(0);
	// Path pa(aa); // 0~999 순서대로
	// p.push_back(pa);

	Path pa;
	for (int k=0; k<10; k++){
		aa.assign(1000, -1);
		int index = dis(gen);
		int firstI = index;
		for (int i=0; i<1000; i++){
			double minimum = 200;
			int minindex = firstI;
			for (int j=0; j<1000; j++){
				if ((W[index][j]<minimum)&&(index!=j)&&(aa[j]==-1)){
					minimum = W[index][j];
					minindex = j;
				}
			}
			aa[index] = minindex;
			index = minindex;
		}
		pa.repath(aa);
		p.push_back(pa);
	}

	p.sort(comper);
///////////////////////////////////////////////////////////
	for (itor=p.begin(); itor!=p.end(); itor++){
		printf("%.16f, %.16f\n", itor->get_cost(), itor->get_bestcost());
		// double tcost = 0;
		// for (int i=0; i<100; i++){tcost += itor->cost[i];}
		// printf("%.16f ,\n", tcost);
		// printf("%d %d\n", itor->get_firstIndex(), itor->get_lastIndex());
	}
///////////////////////////////////////////////////////////
	for (int c=0; c<10; c++){
		itor = itor2 = p.begin();
		itor2++;
		for (int i=0; i<5; i++){
			printf("%.16f, %.16f\n", itor->get_cost(), itor2->get_cost());
			p.push_back(crossover(*itor, *itor2));
			printf("---Crossover--- : %.16f\n", p.back().get_cost());
			itor++;
			itor2++;
		}
		p.sort(comper);
		for (int i=0; i<5; i++) {p.pop_back();}

		printf("GEN%d : %.16f\n", c, p.front().get_cost());
	}

	// free(W);
	data.close();
	return 0;
}