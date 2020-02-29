#ifndef PRINTER_H
#define PRINTER_H

#include <iostream>
#include <vector>

using std::string;
using std::vector;

/* A class used to print cards horizontally (instead of the default vertical implementation).
 * An important restriction is that you have to print a set amount of lines for each data-instance that you want to print.
 * Essentially, you add all the strings that you want to print to a buffer and then iterate over those strings by adding the verticalLength.
 * e.g. for a verticalLength of 3 and 4 data-instances (12 strings in total):
 * print string 0
 * print string 3
 * print string 6
 * print string 9
 * print string 1
 * print string 4
 * print string 7
 * print string 10
 * ...
 */

class Printer
{
private:
    static int verticalLength; //The height(in lines) of the data that you want to print (e.g. height of a card). Used to iterate through the buffer vector.
    static int width; //The horizontal size of the data that you want to print (e.g. width of a card).
                      //Used to fit the data in the terminal (calculates the required width and changes row if needed)
    static vector<string> buffer;
public:
    Printer(){};
    static void AddStringToBuffer(string s);
    static void PrintBuffer(string colour);
    static void setVerticalLength(int value);
    static void setWidth(int value);
};

#endif // PRINTER_H
