/*
 * Assembler main program.
 */
#include "stdafx.h"     // This must be present if you use precompiled headers which you will use. 
#include <stdio.h>

#include "Assembler.h"

int main( int argc, char *argv[] )
{
    Assembler assem( argc, argv );

    // Establish the location of the labels:
    assem.PassI( );

    // Display the symbol table.
    assem.DisplaySymbolTable();

    // Output the translation.
    assem.PassII( );
    
    // Run the emulator on theVC5000 program that was generated in Pass II.
    assem.RunProgramInEmulator();
   
    // Terminate indicating all is well.  
    return 0;
}
