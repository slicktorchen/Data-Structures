#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "time.h"
using namespace std;


int main() {
	Time t1(13,30,59);
	Time t2(15,30,12);
	Time t3(3,25,11);

	vector <Time> times;
	times.push_back(t1);
	times.push_back(t2);
	times.push_back(t3);
	/*cout << "Please enter the time:\n" << "Please enter the hour, minute, and second:" << endl;
	int hour,minute,second;
	cin >> hour >> minute >> second;
	Time now(hour,minute,second);*/


	sort(times.begin(),times.end(),IsEarlierThan);

	for (unsigned int i; i < times.size(); ++i) {
		times[i].PrintAmPm();
	}
	//now.PrintAmPm();
	//string Hour = to_string(hour);
	//cout << Hour;
	//cout << hour.size();

	//t1.PrintAmPm();
	//t3.PrintAmPm();
	//cout << t1.getHour() << ":" << t1.getMinute() << ":" << t1.getSecond() << string AMorPM << endl;
	//cout << t3.getHour() << ":" << t3.getMinute() << ":" << t3.getSecond() << string AMorPM << endl;




	return 0;

}
