#include <iostream>

using namespace std;

class Log
{
public:
	Log();
	enum CMD {skyd, alarm, aktiver, deaktiver, uart};
	void writeLog(CMD cmd);
	string timestamp();

private:
	string cmdArr[5];
};