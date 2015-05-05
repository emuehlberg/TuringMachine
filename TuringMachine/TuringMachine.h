#pragma once

#include <iostream>

#include "Tape.h"

struct State
{
	std::string _state;
	char _value;
	char _action;
};

class TuringMachine
{
public:
	TuringMachine();
	TuringMachine(Tape tape);
	void setAcceptingState(std::string astate);
	void setCurrentState(std::string cstate);
	void addState(std::string cstate, char v, State nstate);
	void nextState();
	void printTape();
	void printState();
	bool completed();
	Tape getTape();

private:
	std::string _cstate;
	std::string _astate;
	std::map<std::pair<std::string, char>,State> _smap;
	Tape _tape;
};