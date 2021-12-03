#include <iostream>
#include <fstream>


int main()
{
    int num_lines = 1000;
    int iter = 0;
    char direction[num_lines];
    int distance[num_lines];
    std::string line;
    std::size_t pos;

    // read input
    std::ifstream input;
    input.open("input.txt");
    if (input.is_open())
    {
        while (std::getline (input, line))
        {
            direction[iter] = line[0];
            pos = line.find(" ");
            distance[iter++] = std::stoi (line.substr(pos));
        }
    }

    // Part 1: What do you get if you multiply your final horizontal position by your final depth?
    int horiz, depth = 0;
    for (int i = 0; i < num_lines; i++)
    {
        switch (direction[i])
        {
            case 'd':
                depth += distance[i];
                break;
            case 'f':
                horiz += distance[i];
                break;
            case 'u':
                depth -= distance[i];
                break;
            default:
                std::cout << "How did you end up here?" << std::endl;
                break;
        }
    }
    std::cout << "Horiz: " << horiz << ", Depth: " << depth << ", Product: " << (horiz * depth) << std::endl;

    // Part 2: Incorporate aim
    horiz = 0;
    depth = 0;
    int aim = 0;
    for (int i = 0; i < num_lines; i++)
    {
        switch (direction[i])
        {
            case 'd':
                aim += distance[i];
                break;
            case 'f':
                horiz += distance[i];
                depth += aim * distance[i];
                break;
            case 'u':
                aim -= distance[i];
                break;
            default:
                std::cout << "How did you end up here?" << std::endl;
                break;
        }
    }
    std::cout << "Horiz: " << horiz << ", Depth: " << depth << ", Product: " << (horiz * depth) << std::endl;
}