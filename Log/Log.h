#ifndef LOG_H_
#define LOG_H_

#include <iostream>

using namespace std;

class Log
{
public:
	Log();
    enum CMD {skyd, alarm, aktiver, deaktiver, uart, advarsel};
	void writeLog(CMD cmd);
	string timestamp();

private:
    string cmdArr[6];
};

#endif
