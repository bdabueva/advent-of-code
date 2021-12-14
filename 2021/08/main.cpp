#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <sstream>
#include <string>

class Pattern
{
public:
    std::string pattern;
    int value;
    
    Pattern(std::string p)
    {
        std::sort(p.begin(), p.end());
        pattern = p;
        value = GetValue();
    }
private:
    int GetValue()
    {
        int ret_val;
        switch (pattern.size())
        {
        case 2:
            ret_val = 1;
            break;
        case 3:
            ret_val = 7;
            break;
        case 4:
            ret_val = 4;
            break;
        case 7:
            ret_val = 8;
            break;
        default:
            ret_val = -1;
            break;
        }
        return ret_val;
    }
};


int main(int argc, char * argv[])
{
    std::string filename = "input.txt";
    if (argc > 1)
    {
        filename = argv[1];
    }

    std::string line;
    std::stringstream lineStream;
    std::vector<std::vector<Pattern> > patterns;
    std::vector<std::vector<std::string> > output_values;

    // read input
    std::ifstream input;
    input.open(filename);
    if (input.is_open())
    {
        int line_num = 0;
        std::string pattern;
        std::vector<Pattern> temp_pattern_vec;
        std::vector<std::string> temp_vec;
        while (std::getline (input, line))
        {
            std::size_t delim_pos = line.find('|');
            std::stringstream pattern_ss(line.substr(0, delim_pos));
            std::stringstream output_values_ss(line.substr(delim_pos + 2));

            while (pattern_ss >> pattern)
            {
                Pattern p = pattern;
                temp_pattern_vec.push_back(p);
            }
            patterns.push_back(temp_pattern_vec);
            temp_pattern_vec.clear();

            while (output_values_ss >> pattern)
            {
                temp_vec.push_back(pattern);
            }
            output_values.push_back(temp_vec);

            temp_vec.clear();
            line_num += 1;
        }
    }

    // // Part 1: In the output values, how many times do digits 1, 4, 7, or 8 appear?
    // std::cout << "output_values.size(): " << output_values.size() << std::endl;
    // int count = 0;
    // for (int row_num = 0; row_num < output_values.size(); row_num++)
    // {
    //     std::cout << "row_num: " << row_num << std::endl;
    //     std::vector<std::string> row = output_values[row_num];
    //     for (std::string value : row)
    //     {
    //         std::cout << "current value: " << value;
    //         int output = IdentifyDigit(patterns[row_num], value);
    //         if (output >= 0)
    //         {
    //             std::cout << " <= counter incremented";
    //             count += 1;
    //         }
    //         std::cout << std::endl;
    //     }
    // }
    // std::cout << "There are " << count << " 1s, 4s, 7s, and 8s in the output" << std::endl;

}