#ifndef TERMINAL_COLOURS_H
#define TERMINAL_COLOURS_H

//Macros for printing coloured letters (support for Windows and Linux) in the console window.
//Every print/cout inside a COLOUR_REGION has the correpsonding colour.
#ifdef LINUX
#define COLOUR_REGION_GREEN cout << "\033[1;32m";
#define COLOUR_REGION_RED cout << "\033[1;31m";
#define COLOUR_REGION_END cout << "\033[0m\n";
#elif WINDOWS
#include <windows.h>
#define COLOUR_REGION_GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
#define COLOUR_REGION_RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
#define COLOUR_REGION_END SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
#endif

#endif // TERMINAL_COLOURS_H
