#include <iostream>
#include <time.h>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;


void init_rand();
vector<int> gen_list(int, int);
void test(vector<int>&, int);
void print(vector<int> const&, int);


int main(int argc, char* argv[]) {
	init_rand();
	vector<int> v = gen_list(50, 100);
	test(v, 10);

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

void test(vector<int> &v, int n) {
	vector<int> v2(v);

	cout << "unsorted:" << endl;
	print(v, -1);

	partial_sort(v.begin(), v.begin() + n, v.end());
	cout << "partial_sort (" << n << "):" << endl;
	print(v, n);

	nth_element(v2.begin(), v2.begin() + n, v2.end());
	cout << "nth_element (" << n << "):" << endl;
	print(v2, n);
}

void print(vector<int> const &v, int n) {
	int i = 0;
	for(vector<int>::const_iterator it = v.begin(); it < v.end(); it++) {
		if (i == n)
			cout << "# ";
		i++;
		cout << *it << " ";
	}
	cout << endl;
}

