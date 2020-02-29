#include <assert.h>
#include <iomanip>
#include <unistd.h>
#include "printer.h"
#include "terminal_colours.h"

#ifdef LINUX
#include <sys/ioctl.h>
#elif WINDOWS
#include <windows.h>
#endif

using namespace std;

int Printer::verticalLength = 0;
int Printer::width = 0;
vector<string> Printer::buffer;

//Adds a string to the buffer. Should be called verticalLength amount of times to add a data-instance.
void Printer::AddStringToBuffer(std::string s)
{
    if(verticalLength == 0)
    {
        assert(false); //Vertical length not set.
    }
    buffer.push_back(s);
}

//To-Do: Add more parameters (amount of spaces between data).
void Printer::PrintBuffer(string colour)
{
    assert(width > 0);

    if(colour == "RED")
    {
        COLOUR_REGION_RED
    }else if(colour == "GREEN")
    {
        COLOUR_REGION_GREEN
    }
	
	int columns, h, prints = 0, offset;
	
	#ifdef LINUX
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	columns = w.ws_col;
	#elif WINDOWS
	CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	#endif

    while(prints < buffer.size())
    {
        offset = prints;
        for(int i = 0; i < verticalLength; i++)
        {
            h = 0;
            for(int j = i + offset; j < buffer.size(); j += verticalLength)
            {
                if(h + width < columns) //check if you have the horizontal space needed
                {
                    cout << "|";
                    cout << setw(width - 1) << buffer.at(j); //-1 because I add the | on the previous line
                    h += width;
                    cout << "    "; //four spaces
                    h += 4;
                    prints++;
                }else
                {
                    break;
                }
            }
            cout << endl;
        }
        cout << endl;
    }
    verticalLength = 0;
    width = 0;
    buffer.clear();
    COLOUR_REGION_END
}


//Both vertical length and width must be set before printing!
void Printer::setVerticalLength(int value)
{
    if(verticalLength != 0)
    {
        assert(false);//You have another type of object in the buffer. Print that first.
    }
    verticalLength = value;
    width = 0;
}


void Printer::setWidth(int value)
{
    width = value;
}
