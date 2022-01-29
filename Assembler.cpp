
//    Implementation of the Assembler class.

#include "stdafx.h"
#include "Assembler.h"

/**/
/*
Assembler::Assembler( int argc, char *argv[] )

NAME

   This function is the constructor of Assembler class. Note: we are passing argc and argv to the file access constructor.

SYNOPSIS

    Assembler::Assembler(int argc, char *argv[]);
    argc		-->			Total number of arguments in the command line
    argv		-->			Pointer to the array of arguments passed through the command line

DESCRIPTION

    This function is the constructor for the Assembler class. 
    We are passing argc and argv to the file access constructor.

RETURNS


AUTHOR

    Tseten Sherpa

DATE

    11:51 PM 04/24/2021
*/
/**/ 



Assembler::Assembler( int argc, char *argv[] )
: m_facc( argc, argv )
{
    // Nothing else to do here
}

// Destructor currently does nothing.  You might need to add something as you develop this project.
Assembler::~Assembler( ) 
{
}/* Assembler::Assembler( int argc, char *argv[] ) */

/**/
/*
void Assembler::PassI( )

NAME

    Assembler::PassI() - Initiates the first pass which adds symbols in symbol table

SYNOPSIS

    void Assembler::PassI()

DESCRIPTION

    This function establishes the location of the labels. It will store the location of all the labels required for
    the assembler.

RETURNS

    VOID

AUTHOR

    Tseten Sherpa

DATE

    12:00 AM 04/26/2021
*/
/**/


void Assembler::PassI( ) 
{
    // Tracks the location of the upcoming instructions 
    int loc = 0;     

    // Processes each line of source code.
   while ( true ) {

        // Read the next line from the source file.
        std::string line; 
        if( ! m_facc.GetNextLine(line) ) 
        {
            return;
        }

        // Parses the line and gets the instruction type.
        Instruction::InstructionType st =m_inst.ParseInstruction( line );
               
        // If this is an end statement, there is nothing left to do in pass I. Pass II will determine if the end is the last statement.
        if( st == Instruction::ST_End ) return;

        // Labels can only be on machine language and assembler language instructions.  So, skip other instruction types.  
        if( st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr ) 
        {
        	continue;
        }

        // If the instruction has a label, record it and its location in the symbol table.
        if( m_inst.isLabel( ) ) 
        {
            m_symtab.AddSymbol( m_inst.GetLabel( ), loc );
        }
        // Compute the location of the next instruction.
        loc = m_inst.LocationNextInstruction( loc );
    }
}/* void Assembler::PassI( ) ; */


/**/
/*
void Assembler::PassII( )

NAME

    This function uses symbol table of previous Pass and directs the translation of the source code for VC-5000 Computer. 
    Pass II directs translation, and stores the translated instructions in a vector of pair.

SYNOPSIS

    void Assembler::PassII();

DESCRIPTION

    This function translates the assembly language code into machine code for the VC5000 computer.

RETURNS

    VOID

AUTHOR

    Tseten Sherpa

DATE

    2:00 PM 04/27/2021
*/
/**/

void Assembler::PassII()
{
    // Flags where code has reaches the end statement
    bool is_end = false;
    // Tracks the location of the upcoming instructions.
    int loc = 0;

    // Moves file pointer to the beginning of the file and clear the eof flag
    m_facc.rewind();

    //Clears the vector 
    m_machineCode.clear();

    //Outputs message for translation 
    std::cout << "\nTranslation of Program: " << std::endl;
    std::cout << "Location" << "   " << "Contents" << "   " << "Original Statement" << std::endl;

    // Processes each line of source code
   while (true){
        // Read the next line from the source file.
        std::string line;
        if (!m_facc.GetNextLine(line))
        {
            if (is_end == true)
            {
                break;
            }
        }

        //Pairs to store machine language instruction
        std::pair<int, std::string> translation = m_inst.TranslateInstruction(line, loc);

        //Sets end flag to true when end statement appears
        if (translation == std::pair <int, std::string>(0, "end"))
            is_end = true;

        //If there is no valid machine code
        else if (translation != std::pair<int, std::string>(0, "n/a"))
        {
           m_machineCode.push_back(translation);
        }

        if (m_inst.computeType(line) == m_inst.ST_Comment || m_inst.computeType(line) == m_inst.ST_End)
        {
            continue;
        }
        else
        {
            //Get the location of next instruction
            loc = m_inst.LocationNextInstruction(loc);
        }
    }
    
    //Prompt for user to press enter
    std::cout << "--------------------------------------------------\n\n";
    std::cout << "Press Enter to Continue...";
    std::cin.get();
    return;
}/* void Assembler::PassII(); */

