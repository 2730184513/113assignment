#include <iostream>
#include <ctime>
using namespace std;
int main()
{
	time_t now = time(0);
	tm* local_time = localtime(&now);
	char buffer1[80];
	strftime(buffer1,80,"%Y-%B-%d-%A",local_time);
	string date = buffer1;
	cout<<date;
}

