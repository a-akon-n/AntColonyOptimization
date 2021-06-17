#pragma
#include <iostream>
#include <exception>

using namespace std;

class MyException {
private:
	string message;
public:
	MyException(string msg) : message(msg) {}

	string toString()
	{
		return message;
	}
};