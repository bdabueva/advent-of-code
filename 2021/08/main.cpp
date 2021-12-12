#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <sstream>
#include <string>

// int IdentifyDigit(std::vector<std::string> pattern, std::string output_digit)
// {
//     int return_val = -1;
//     switch (output_digit.size())
//     {
//     case 2:
//         return_val = 1;
//         break;
//     case 3:
//         return_val = 7;
//         break;
//     case 4:
//         return_val = 4;
//         break;
//     case 7:
//         return_val = 8;
//     default:
//         break;
//     }
//     return return_val;
// }

int main(int argc, char * argv[])
{
    std::string filename = "input.txt";
    if (argc > 1)
    {
        filename = argv[1];
    }

    std::string line;
    std::stringstream lineStream;
    std::vector<std::vector<std::string> > patterns;
    std::vector<std::vector<std::string> > output_values;

    // read input
    std::ifstream input;
    input.open(filename);
    if (input.is_open())
    {
        int line_num = 0;
        while (std::getline (input, line))
        {
            lineStream << line;
            std::string pattern;
            std::vector<std::string> patterns_current_row, output_values_current_row;
            bool is_pipe_found = false;
            while (std::getline(lineStream, pattern, ' '))
            {
                if (pattern.compare("|") == 0)
                {
                    is_pipe_found = true;
                }
                else if (!is_pipe_found)
                {
                    patterns_current_row.push_back(pattern);
                }
                else
                {
                    output_values_current_row.push_back(pattern);
                }
            }
            patterns.push_back(patterns_current_row);
            output_values.push_back(output_values_current_row);
            line_num += 1;
        }
    }

    // Part 1: In the output values, how many times do digits 1, 4, 7, or 8 appear?
    // int count = 0;
    // for (int row_num = 0; row_num < output_values.size(); row_num++)
    // {
    //     std::vector<std::string> row = output_values[row_num];
    //     for (std::string value : row)
    //     {
    //         int output = IdentifyDigit(patterns[row_num], value);
    //         if (output >= 0)
    //         {
    //             count += 1;
    //         }
    //     }
    // }

}