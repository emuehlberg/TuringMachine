#include "TuringMachine.h"


TuringMachine::TuringMachine(Tape tape)
{
	_tape = tape;
	_cstate = "";
	_smap.clear();
}

TuringMachine::TuringMachine()
{
	_tape = Tape();
	_cstate = "";
	_smap.clear();
}

void TuringMachine::addState(std::string cstate, char v, State nstate)
{
	std::pair<std::string, char> pair (cstate, v);
	_smap[pair] = nstate;
}

void TuringMachine::nextState()
{
	std::pair<std::string, char> pair(_cstate, _tape.readChar());
	State nstate = _smap[pair];

	_tape.writeChar(nstate._value);
	_cstate = nstate._state;
	if (nstate._action == '>')
		_tape.moveHead(1);
	else if (nstate._action == '<')
		_tape.moveHead(-1);
}

void TuringMachine::printTape()
{
	int cursor = _tape.getPosition();
	int leftbound = cursor - 20;
	int rightbound = cursor + 20;
	for (cursor = leftbound; cursor <= rightbound; cursor++)
	{
		std::cout << _tape.getChar(cursor);
	}
	std::cout << std::endl;
	for (cursor = leftbound; cursor <= rightbound; cursor++)
	{
		if (cursor == 0)
		{
			std::cout << "|";
		}
		else
		{
			if (cursor == _tape.getPosition())
				std::cout << "^";
			else
				std::cout << "_";
		}
	}
	std::cout << std::endl;
}

void TuringMachine::printState()
{
	std::cout << "State: " << _cstate << " Head Position: " << _tape.getPosition() << std::endl;
}

bool TuringMachine::completed()
{
	if (_cstate == _astate)
		return true;
	else
		return false;
}

void TuringMachine::setAcceptingState(std::string astate)
{
	_astate = astate;
}

void TuringMachine::setCurrentState(std::string cstate)
{
	_cstate = cstate;
}

Tape TuringMachine::getTape()
{
	return _tape;
}