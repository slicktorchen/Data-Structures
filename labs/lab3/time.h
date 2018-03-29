
class Time {

public:
	Time();
	Time(uintptr_t aHour,uintptr_t aMinute, uintptr_t aSecond);

	uintptr_t getHour() const {return hour;} 
	uintptr_t getMinute() const {return minute;} 
	uintptr_t getSecond() const {return second;} 

	void setHour(uintptr_t aHour);
	void setMinute(uintptr_t aMinute);
	void setSecond(uintptr_t aSecond);

	void PrintAmPm() const;

private:
	uintptr_t hour;
	uintptr_t minute;
	uintptr_t second;
	//string AMorPM;

};


bool IsEarlierThan (const Time& t1, const Time& t2);