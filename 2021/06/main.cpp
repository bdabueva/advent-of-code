#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <sstream>
#include <string>

class School
{
public:
    std::vector<long long> fish_count_by_age;

    School()
        :fish_count_by_age({0,0,0,0,0,0,0,0,0})
    {}

    School(std::vector<long long> new_count_by_age)
        :fish_count_by_age(new_count_by_age)
    {}

    void AddFish(int age)
    {
        fish_count_by_age[age] += 1;
    }

    void AgeByXDays(int num_days)
    {
        for (int day = 1; day <= num_days; day++)
        {
            long long birther_count = fish_count_by_age[0];
            for (int i = 0; i < 8; i++)
            {
                fish_count_by_age[i] = fish_count_by_age[i+1];
            }
            fish_count_by_age[8] = birther_count;
            fish_count_by_age[6] += birther_count;
        }
    }

    long long SchoolSize()
    {
        long long total = 0;
        for (int i = 0; i <= 8; i++)
        {
            total += fish_count_by_age[i];
        }
        return total;
    }
};

int main()
{
    std::string line;
    std::stringstream lineStream;
    School school, school2;
    int DAY_COUNT = 80;
    int DAY_COUNT_PT2 = 256;

    // read input
    std::ifstream input;
    input.open("input.txt");
    if (input.is_open())
    {
        while (std::getline (input, line))
        {
            lineStream << line;
            std::string fish_age;
            while (std::getline(lineStream, fish_age, ','))
            {
                school.AddFish(stoi(fish_age));
                school2.AddFish(stoi(fish_age));
            }
        }
    }

    // School school2;
    // school2 = school;

    // Part 1: How many lanternfish would there be after 80 days?
    school.AgeByXDays(DAY_COUNT);
    std::cout << "After " << DAY_COUNT << " days, there will be " << school.SchoolSize() << " fish" << std::endl;

    // Part 2: How many lanternfish would there be after 256 days?
    school2.AgeByXDays(DAY_COUNT_PT2);
    std::cout << "After " << DAY_COUNT_PT2 << " days, there will be " << school2.SchoolSize() << " fish" << std::endl;

}