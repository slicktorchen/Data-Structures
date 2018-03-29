#include <iostream>
using namespace std;


int main() {
	int number;
	float total,average;
	cout << "Number of numbers to average: ";
	cin >> number;
	float A[number];
	cout << endl << "Enter " << number << " numbers" << endl;
	for (int i = 0; i < number ; i++) {
		cin >> A[i];
		total += A[i];
	}
	average = total/number;
	cout << "The average is " << average << endl;
	cout << "Numbers below the average: ";
	for (int i = 0; i < number ; i++) {
		if (A[i] < average) {
			cout << A[i] << " ";
		}
	}


	return 0;
}
