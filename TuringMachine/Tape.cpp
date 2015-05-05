#include "Tape.h"


Tape::Tape()
{
	_position = 0;
	_tape.clear();
}

void Tape::writeChar(char c)
{
	_tape[_position] = c;
}

char Tape::readChar()
{
	if (_tape[_position] == NULL)
		_tape[_position] = '_';
	return _tape[_position];
}

void Tape::moveHead(int i)
{
	_position += i;
}

int Tape::getPosition()
{
	return _position;
}

char Tape::getChar(int x)
{
	if (_tape[x] == NULL)
		_tape[x] = '_';
	return _tape[x];
}

int Tape::getTapeSize()
{
	return _tape.size();
}

int Tape::front()
{
	return _tape.begin()->first;
}

int Tape::back()
{
	return _tape.end()->first;
}

void Tape::resetHead()
{
	_position = 0;
}