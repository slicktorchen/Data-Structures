#include <iostream>
#include <string>
#include <vector>
using namespace std;


void compute_squares(unsigned int *a,unsigned int *b, int n)
{
	for(int i = 0; i < n; ++i, ++a, ++b) { //a[i] = *(a + 1)
		*b = (*a) * (*a);
	}
}

int main() {
	int i, n = 10; 
	unsigned int A[10], B[10];
	for (i =0;  i< n; ++i)
	{
		A[i] = i; 
		//cout << A[i] << "# ";
	}
	//cout << A << " " << B << endl;

    compute_squares(A,B,n);
	for (i =0;  i< n; ++i)
	{
		cout << B[i] << " ";
	}

	return 0;
}