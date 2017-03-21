#include <iostream>
#include <time.h>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;


typedef vector<int>::const_iterator CIntIt;

void init_rand();
vector<int> gen_list(int, int);
void test(vector<int>&);
void print(vector<int> const&, const CIntIt&);


int main(int argc, char* argv[]) {
	init_rand();
	vector<int> v = gen_list(50, 10);
	test(v);

	return 0;
}

void init_rand() {
	unsigned int t = static_cast<unsigned int>(time(NULL));
	srand(t);
}

vector<int> gen_list(int n, int max) {
	vector<int> v;
	v.reserve(n);

	while(n--)
		v.push_back(rand() % max);
	return v;
}

bool is_odd(int a) {
	return a % 2 == 1;
}

void test(vector<int> &v) {
	cout << "unpartitioned:" << endl;
	print(v, v.end());

	CIntIt p_end = partition(v.begin(), v.end(), is_odd);

	cout << "partitioned by odd / even:" << endl;
	print(v, p_end);
}

void print(vector<int> const &v, const CIntIt &p_end) {
	for(vector<int>::const_iterator it = v.begin(); it < v.end(); it++) {
		if (it == p_end)
			cout << endl;
		cout << *it << " ";
	}
	cout << endl;
}

