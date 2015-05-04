#include "Log.h"
#include <string>
#include <fstream>
#include <istream>
#include <ctime>


Log::Log()
{
	cmdArr[skyd] = "Der blev affyret skud\n";
	cmdArr[alarm] = "Alarmen blev aktiveret\n";
	cmdArr[aktiver] = "Systemet blev aktiveret\n";
	cmdArr[deaktiver] = "Systemet blev deaktiveret\n";
	cmdArr[uart] = "Der opstod en fejl ved oprettelse af forbindelse til UART\n";
}

string Log::timestamp()
{
	time_t t = time(0);
	struct tm tstruct = *localtime(&t);
	char buf[80];
	strftime(buf, sizeof(buf), "%Y%m%d %X - ", &tstruct);

	return buf;

}

void Log::writeLog(CMD cmd)
{

	ofstream file;
	file.open("Log.txt", ios_base::app | ios_base::out);
	file << timestamp() << cmdArr[cmd];
	file.close();
	
}
