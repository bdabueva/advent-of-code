#include <iostream>
#include <fstream>

int main()
{
    int num_lines = 2000;
    int iter = 0;
    int array[num_lines];

    // read input
    std::ifstream input;
    input.open("input.txt");
    if (input.is_open())
    {
        while (! input.eof())
        {
            input >> array[iter++];
        }
    }

    // Part 1: find the number of times the measurement increases
    int count = 0;
    for (int i = 1; i < num_lines; i++)
    {
        if (array[i] > array[i-1])
        {
            count += 1;
        }
    }
    std::cout << "There are " << count << " measurements larger than the previous measurement." << std::endl;

    // Part 2: find the number of times a 3 measurement sum increases
    int count_filtered = 0;
    for (int i = 3; i < num_lines; i++)
    {
        if ((array[i-2] + array[i-1] + array[i]) > (array[i-3] + array[i-2] + array[i-1]))
        {
            count_filtered += 1;
        }
    }
    std::cout << "There are " << count_filtered << " three-measurement sums larger than the previous sum." << std::endl;
}