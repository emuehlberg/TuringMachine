#pragma once

#include <map>
#include <string>

class Tape
{
public:
	Tape();
	void writeChar(char c);
	char readChar();
	void moveHead(int i);
	int getPosition();
	char getChar(int x);
	int getTapeSize();
	int front();
	int back();
	void resetHead();

private:
	std::map<int, char> _tape;
	int _position;
};