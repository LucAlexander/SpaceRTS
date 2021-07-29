#ifndef ALARM_H
#define ALARM_H

class Alarm{
public:
	Alarm();
	Alarm(int t);
	void tick();
	bool ring();
	bool active();
	void reset();
	void set(int t);
private:
	enum STATE{
		INACTIVE=-1,
		RING=0
	};
	int time;
	int resetTime;
};

#endif
