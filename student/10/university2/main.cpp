/*
 * University
 *
 * Overview:
 *
 *   This application serves as a management tool for a University system,
 * handling courses and student accounts. It provides the capability to create
 * courses and student accounts, enroll students and staff in courses, manage
 * course completion, and output information about courses and accounts.
 *   Interactivity is maintained through command prompts, where users can
 * input specific commands, visible through the 'help' or 'h' option.
 * The University class employs both the Account and Course classes to manage
 * the student data and respond to user commands effectively.
 *   The user can terminate the program by inputting a quit command ('q' or 'Q').
 *
 * Program author ( Fill with your own info )
 * Name: Aynur Rahman Talukdar
 * Student number: 150189473
 * UserID: qkayta
 * E-Mail: aynurrahman.talukdar@tuni.fi
 *
 * Notes about the program and it's implementation (if any):
 *
 * */

//#include "utils.hh"
#include "cli.hh"
#include "university.hh"
//#include <iostream>
//#include <string>
//#include <vector>
//#include <fstream>

const std::string PROMPT = "Uni> ";


int main()
{
    University* university = new University("tuni.fi");
    Cli cli(university, PROMPT);
    while ( cli.exec() ){}

    delete university;
    return EXIT_SUCCESS;
}
