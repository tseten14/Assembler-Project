#include "stdafx.h"
#include "Emulator.h"
#include "Errors.h"

/**/
/*
bool emulator::insertMemory(int a_location, int a_contents)

NAME

	emulator::insertMemory(int a_location, int a_contents)) - Inserts the machine language contents into the memory location

SYNOPSIS

	bool emulator::insertMemory(int a_location, int a_contents)
	a_location		-->			location of the machine language
	a_contents		-->			content of the machine language

DESCRIPTION

	This function inserts the contents into VC 5000 Computer.

RETURNS

	Returns true if successfully inserted in memory and false if not.

AUTHOR

	Tseten Sherpa

DATE

	2:42 PM 05/11/2021
*/
/**/


bool emulator::insertMemory(int a_location, int a_contents)
{
	if (a_location >= 0 && a_location < MEMSZ)
	{
		m_memory[a_location] = a_contents;
		return true;
	}

}  /* bool emulator::insertMemory(int a_location, int a_contents) */




/**/
/*
bool emulator::runProgram()

NAME

	emulator:: runProgram - Runs the VC5000 program 

SYNOPSIS

	bool emulator::runProgram();

DESCRIPTION

	This function will run the emulator for VC 5000 Computer.

RETURNS

	Returns true if the program executed successfully and false otherwise.

AUTHOR

	Tseten Sherpa

DATE

	4:20 PM 05/12/2021
*/
/**/
bool emulator::runProgram()
{

	int loc = 100;			//Variable to store location
	std::string user_input;		// Variable to store user input
	char sign = 'n';	 //Variable to store sign

	while (true)
	{
		//Instruction at the given location
		int instr = m_memory[loc]; 
		//Taking opcode from machine code
		int opCode = instr / 10000000;		
		//Taking register number from machine code
		int regNum = instr / 1000000 % 10;	
		//Taking address from machine code 
		int address = instr % 1000000;		
		switch (opCode)
		{
		case 1:
		//To add
			m_reg[regNum] += m_memory[address];
			++loc;
			break;
		case 2:
		//To substract
			m_reg[regNum] -= m_memory[address];
			++loc;
			break;
		case 3:
		//To multiply
			m_reg[regNum] *= m_memory[address];
			++loc;
			break;
		case 4:
		//To divide
			m_reg[regNum] /= m_memory[address];
			++loc;
			break;
		case 5:
		//To load
			m_reg[regNum] = m_memory[address];
			++loc;
			break;
		case 6:
		//To store
			address = m_reg[regNum];
			++loc;
			break;
		case 7:
		//To read
			std::cout << "?";
			std::cin >> user_input;
			loc++;
			break;
		case 8:
		//To write
			std::cout << m_memory[address] << std::endl;
			loc++;
			break;
		case 9:
		//To branch  
			loc = address;
			break;
		case 10:
		//To branch minus
			if (m_reg[regNum] < 0)
			{
				loc = address;
			}
			else
			{
				loc++;
			}
			break;
		case 11:
			//BRANCH ZERO
			if (m_reg[regNum] == 0)
			{
				loc = address;
			}
			else
			{
				loc++;
			}
			break;
		case 12:
		//To branch positive
			if (m_reg[regNum] > 0)
			{
				loc = address;
			}
			else
			{
				loc++;
			}
			break;
		case 13:
		//To halt
			exit(1);

		default:
			std::cerr << "Illegal Opcode" << std::endl;
			return false;
		}
		
	}
	return false;
} /* bool emulator::runProgram() */