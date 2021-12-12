#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <sstream>
#include <string>

int FindMinimumMoves(std::vector<int> v)
{
    int min_moves = 270000000;
    int total_moves;
    // std::pair<int, int> result = std::minmax(v);
    int min = *std::min_element(v.begin(), v.end());
    int max = *std::max_element(v.begin(), v.end());
    for (int i = min; i <= max; i++)
    {
        total_moves = 0;
        for (int x : v)
        {
            total_moves += std::abs(x - i);
        }
        min_moves = std::min(min_moves, total_moves);
    }
    return min_moves;
}

int OptimizeFuel(std::vector<int> v)
{
    int min_fuel = 270000000;
    int move, total_fuel;
    int min = *std::min_element(v.begin(), v.end());
    int max = *std::max_element(v.begin(), v.end());
    for (int i = min; i <= max; i++)
    {
        total_fuel = 0;
        for (int x : v)
        {
            move = std::abs(x - i);
            total_fuel += (move * (move+1) / 2);
        }
        min_fuel = std::min(min_fuel, total_fuel);
    }
    return min_fuel;
}

int main()
{
    std::string line, position;
    std::stringstream lineStream;
    std::vector<int> positions;

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
                positions.push_back(stoi(position));
            }
        }
    }

    // Part 1: How much fuel must they spend to align to the optimal position?
    int minimum_moves = FindMinimumMoves(positions);
    std::cout << "The minimum amount of fuel is: " << minimum_moves << std::endl;

    // Part 2: Linear fuel usage
    int optimal_fuel = OptimizeFuel(positions);
    std::cout << "The minimum amount of fuel is: " << optimal_fuel << std::endl;
}