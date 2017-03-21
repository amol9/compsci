//g++ <filename> -std=c++11 -w
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <memory>
#include <stdlib.h>

using namespace std;


#define SIZE 30

auto_ptr<int> ap();
void print_a(auto_ptr<int> (&a)[SIZE]);
void print_s(shared_ptr<int> (&a)[SIZE]);
int cmp(const void*, const void*);
bool cmp_a(auto_ptr<int> a, auto_ptr<int> b);
bool cmp_s(shared_ptr<int> a, shared_ptr<int> b);


int main(int argc, char* argv[]) {
	auto_ptr<int> a[SIZE];
	auto_ptr<int> a2[SIZE];
	shared_ptr<int> b[SIZE];

       	for (int i = 0; i < SIZE; i++) {
		a[i] = ap();
		a2[i] = auto_ptr<int>(new int(*a[i]));
		b[i] = shared_ptr<int>(new int(*a[i]));
	}
	
	cout << "unsorted:" << endl;
	print_a(a);

	cout << "sorted shared_ptr array using std::sort:" << endl;
	sort(begin(b), end(b), cmp_s);
	print_s(b);

	cout << "sorted auto_ptr array using qsort:" << endl;
	qsort(a, SIZE, sizeof(auto_ptr<int>), cmp);
	print_a(a);

	cout << "sorted auto_ptr array using std::sort:" << endl;
	sort(begin(a2), end(a2), cmp_a);
	print_a(a2);

	return 0;
}

auto_ptr<int> ap() {
	return auto_ptr<int>(new int(rand() % 100));
}

int cmp(const void* a, const void* b) {
	return **(auto_ptr<int>*)a - **(auto_ptr<int>*)b;
}

bool cmp_a(auto_ptr<int> a, auto_ptr<int> b) {
	return *a < *b;
}

bool cmp_s(shared_ptr<int> a, shared_ptr<int> b) {
	return *a < *b;
}

void print_a(auto_ptr<int> (&a)[SIZE]) {
	for (int i = 0; i < SIZE; i++ )
		cout << *a[i] << " ";
	cout << endl;
}

void print_s(shared_ptr<int> (&a)[SIZE]) {
	for (int i = 0; i < SIZE; i++ )
		cout << *a[i] << " ";
	cout << endl;
}

