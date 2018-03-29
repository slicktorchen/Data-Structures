#include <iostream>
#include <string>
#include "time.h"
using namespace std;

Time::Time() {
	hour = 0;
	minute = 0;
	second = 0;
}

Time::Time(int aHour,int aMinute, int aSecond) {
	hour = aHour;
	minute = aMinute;
	second = aSecond;

}

int Time::getHour() const {
	return hour;
}

int Time::getMinute() const {
	return minute;
}

int Time::getSecond() const {
	return second;
}

void Time::setHour(int h) {
	hour = h;
}

void Time::setMinute(int m) {
	minute = m;
}

void Time::setSecond(int s) {
	second = s;
}

void Time::PrintAmPm() const {
	string AMorPM;
	if (hour == 0) {
		AMorPM = "AM";
		cout << 12 << ":"; //<< minute << ":" << second << " " << AMorPM << endl;
	} else if (hour == 12) {
		AMorPM = "PM";
		cout << 12 << ":"; //<< minute << ":" << second << " " << AMorPM << endl;
	} else if (hour < 12) {
		AMorPM = "AM";
		cout << hour << ":"; //<< minute << ":" << second << " " << AMorPM << endl;
	} else {
		AMorPM = "PM";
		cout << hour%12 << ":"; //<< minute << ":" << second << " " << AMorPM << endl;
	}

	if (minute < 10) {
		cout << 0 << minute << ":";
	} else {
		cout << minute << ":";
	}

	if (second < 10) {
		cout << 0 << second << " " << AMorPM << endl;
	} else {
		cout << second << " " << AMorPM << endl;
	}
}

bool IsEarlierThan (const Time& t1,const Time& t2) {
	if (t1.getHour() > t2.getHour()) {
		return true;
	} else if (t1.getHour() < t2.getHour()) {
		return false;
	} else {
		if (t1.getMinute() > t2.getMinute()) 
		{
			return true;
		} else if (t1.getMinute() < t2.getMinute()) 
		{
			return false;
		} else 
		{
			if (t1.getSecond() > t2.getSecond()) {
				return true;
			} else if (t1.getSecond() < t2.getSecond()) {
				return false;
			} else {
				return "Same time";
			}
		}
	}
}




