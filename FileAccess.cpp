//
//  Implementation of file access class.
//
#include "stdafx.h"
#include "FileAccess.h"

/*
FileAccess::FileAccess( int argc, char *argv[] )


NAME

    FileAccess::FileAccess( int argc, char *argv[] ) - Opens the Source file for Reading

SYNOPSIS

    FileAccess::FileAccess( int argc, char *argv[] );
    argc		-->			Total number of command line arguments
    argv		-->			Pointer to the array of arguments passed through the command line

DESCRIPTION

    This constructor will open the file passed as command line argument for reading.
    
RETURNS


AUTHOR

    Tseten Sherpa

DATE

    11:51 PM 05/05/2021


*/
/**/
FileAccess::FileAccess( int argc, char *argv[] )
{
    // Check that there is exactly one run time parameter.
    if( argc != 2 ) {
        std::cerr << "Usage: Assem <FileName>" << std::endl;
        exit( 1 );
    }

    // Open the file.
    m_sfile.open( argv[1], std::ios::in );

    // If the open failed, terminate.
    if( ! m_sfile ) {
        std::cerr << "Source file could not be opened, assembler terminated."<< std::endl;
        exit( 1 ); 
    }
}
//Destructor for FileAccess class
FileAccess::~FileAccess( )
{
    // Not that necessary since the file will be closed when the program terminates, but good form.
    m_sfile.close( );
}/* FileAccess::FileAccess( int argc, char *argv[] ); */


/**/
/*
bool FileAccess::GetNextLine( string &a_line )

NAME

    FileAccess::GetNextLine - gets the next line from the source file

SYNOPSIS

    bool FileAccess::GetNextLine( string &a_line )
    a_line	-> string that will contain instructions to read

DESCRIPTION

   This function returns true if it successfully read the next line from the provided source code

RETURNS

    Returns true if read was successful. If it was not it returns false

AUTHOR

    Tseten Sherpa

DATE

    11:51 PM 5/6/2020
*/
/**/
bool FileAccess::GetNextLine( std::string &a_line )
{
    // If there is no more data, return false.
    if( m_sfile.eof() )
    {
        return false;
    }
    getline( m_sfile, a_line );
    
    // Return indicating success.
    return true;
}/* bool FileAccess::GetNextLine( std::string &a_line ); */


/**/
/*
void FileAccess::rewind( )

NAME

    FileAccess::rewind - resets file pointer and eof flag

SYNOPSIS

    void FileAccess::rewind( );

DESCRIPTION

    This function clears the eof flag and moves file pointer to the beginning of the file.

RETURNS

    VOID

AUTHOR

    Tseten Sherpa

DATE

    11:51 PM 5/7/2021

*/
/**/
void FileAccess::rewind( )
{
    // Clean all file flags and go back to the beginning of the file.
    m_sfile.clear();
    m_sfile.seekg( 0, std::ios::beg );
}/* void FileAccess::rewind( ); */