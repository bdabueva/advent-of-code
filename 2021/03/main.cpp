#include <iostream>
#include <fstream>
#include <vector>

int OnesCount(std::vector<int> v, int bit_position)
{
    int count = 0;
    for (int x : v)
    {
        if (((x >> bit_position) & 1) == 1)
        {
            count += 1;
        }
    }
    return count;
}

std::vector<int> FilterValues(std::vector<int> v_in, int bit_position, bool is_most_popular)
{
    // Get the ones count at the desired bit position, this will be used as the size for vec_out
    int ones_count = OnesCount(v_in, bit_position);
    int num_rows, fltr;
    if ((ones_count * 2 >= v_in.size() && is_most_popular) || (ones_count * 2 < v_in.size() && !is_most_popular))
    {
        num_rows = ones_count;
        fltr = 1;
    }
    else
    {
        num_rows = v_in.size() - ones_count;
        fltr = 0;
    }

    // Filter v_in to get v_out
    std::vector<int> v_out(num_rows);
    int i = 0;
    for (int x : v_in)
    {
        if (((x >> bit_position) & 1) == fltr)
        {
            v_out[i++] = x;
        }
    }

    // If num_rows > 1 recursively call FilterValues, otherwise return
    if (num_rows > 1)
    {
        v_out = FilterValues(v_out, bit_position-1, is_most_popular);
    }
    return v_out;
}

int main()
{
    int num_lines = 1000;
    int num_bits = 12;
    int iter = 0;
    std::vector<int> vec(num_lines);
    std::string line;
    std::size_t pos;

    // read input
    std::ifstream input;
    input.open("input.txt");
    if (input.is_open())
    {
        while (std::getline (input, line))
        {
            vec[iter++] = stoi(line, nullptr, 2);
        }
    }

    // Part 1: What is the power consumption of the submarine?
    int ones_count;
    int gamma = 0;
    int epsilon = 0;
    for (int i = num_bits - 1; i >= 0; i--)
    {
        ones_count = OnesCount(vec, i);
        if (ones_count * 2 > num_lines)
        {
            gamma += 1 << i;
        }
        else
        {
            epsilon += 1 << i;
        }
    }
    std::cout << "Gamma: " << gamma << ", Epsilon: " << epsilon << std::endl;
    std::cout << "Product: " << (gamma * epsilon) << std::endl;

    // Part 2: What is the life support rating of the submarine?
    std::cout << std::endl;
    std::vector<int> o2_generator_rating = FilterValues(vec, num_bits-1, true);
    std::vector<int> co2_scrubber_rating = FilterValues(vec, num_bits-1, false);
    std::cout << "O2: " << o2_generator_rating[0] << ", CO2: " << co2_scrubber_rating[0] << std::endl;
    std::cout << "Product: " << (o2_generator_rating[0] * co2_scrubber_rating[0]) << std::endl;
}