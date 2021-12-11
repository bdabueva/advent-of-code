#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <sstream>
#include <string>


int main()
{
    std::string line;
    std::stringstream lineStream;

    // read input
    std::ifstream input;
    input.open("input.txt");
    if (input.is_open())
    {
        while (std::getline (input, line))
        {
            lineStream << line;
            std::string position;
            while (std::getline(lineStream, position, ','))
            {
                // do something with the positions
            }
        }
    }

    // Part 1: How much fuel must they spend to align to the optimal position?
}