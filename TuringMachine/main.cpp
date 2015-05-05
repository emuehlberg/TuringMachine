#include <fstream>

#include "TuringMachine.h"

TuringMachine tm;
Tape Solution;
bool steps;
int cycles;

bool compareTapes()
{
	Tape tmtape = tm.getTape();
	for (int x = Solution.front(); x <= Solution.back(); x++)
	{
		if (Solution.getChar(x) != tmtape.getChar(x))
			return false;
	}
	return true;
}

Tape loadTape(std::string tape)
{
	std::cout << "Loading Tape..." << std::endl;

	Tape t = Tape();

	for (int x = 0; x < tape.size(); x++)
	{
		t.writeChar(tape[x]);
		t.moveHead(1);
	}
	
	t.resetHead();
	
	std::cout << "Tape Loaded!" << std::endl;

	return t;
}

bool loadMachine(std::string filename)
{
	std::ifstream ifile;
	ifile.open(filename);

	std::string line;
	std::string accept;
	std::string start;
	if (ifile.is_open())
	{
		std::cout << "File opened successfully. Loading Machine..." << std::endl;

		//Grab solution state
		std::getline(ifile, line);
		if (line != "NA")
			Solution = loadTape(line);

		//ignore second two lines
		std::getline(ifile, line);
		std::getline(ifile, line);
		
		//accepting and starting states
		std::getline(ifile, start);
		std::getline(ifile, accept);

		//Tape line
		std::getline(ifile, line);

		//Create machine
		tm = TuringMachine(loadTape(line));

		tm.setAcceptingState(accept);
		tm.setCurrentState(start);

		while (std::getline(ifile, line))
		{
			std::cout << "Loading State -> " << line << std::endl;
			//Split line in half
			int epos = line.find("=");
			std::string first = line.substr(0, epos - 1);
			std::string second = line.substr(epos + 1);

			//Get first state values
			epos = first.find(" ");
			std::string cstate = first.substr(0, epos);
			char cval = first[epos + 1];
			//std::cout << "Current State: " << cstate << " Current Value: " << cval << std::endl;

			//Create state out of second half
			second = second.substr(1);
			State s;
			epos = second.find(" ");
			s._state = second.substr(0, epos);
			s._value = second[epos + 1];
			s._action = second[epos + 3];
			//std::cout << "Next State: " << s._state << " Next Value: " << s._value << " Action: " << s._action << std::endl;

			//insert state
			tm.addState(cstate, cval, s);
			std::cout << "State Loaded" << std::endl;
		}

		std::cout << "Machine Loaded!" << std::endl;
		return true;
	}
	else
	{
		std::cout << "Failed to open file, could not load Machine!" << std::endl;
		return false;
	}
}

void run()
{
	while (!tm.completed())
	{
		tm.nextState();
		cycles++;
		if (steps)
		{
			tm.printState();
			tm.printTape();
			std::cout << std::endl;
		}
	}
	std::cout << "Machine halted after "<< cycles << "cycles. Resulting state: " << std::endl;
	tm.printState();
	tm.printTape();
	/*if (compareTapes())
	{
		std::cout << "Halt state matches provided solution!" << std::endl;
	}*/
}

void main()
{
	steps = false;
	std::string input;
	while (true)
	{
		std::cout << "Display steps?: ";
		std::cin >> input;
		if (input == "y")
			steps = true;
		else
			steps = false;
		std::cout << "Please enter filename of the machine: ";
		std::cin >> input;

		if (input == "exit")
			return;

		if (loadMachine(input))
		{
			cycles = 0;
			std::cout << "Machine is ready. Starting state of machine: " << std::endl;
			tm.printState();
			tm.printTape();

			run();
		}
	}
}