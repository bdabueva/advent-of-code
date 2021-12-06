#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <sstream>
#include <string>

#include "main.h"

std::vector<int> Card::draw;

int main()
{
    // int num_lines = 1000;
    int iter = 0;
    Card card;
    std::vector< Card > card_set;
    int card_row;
    std::string line;
    std::size_t pos;
    // std::vector<int> draw;

    // read input
    std::ifstream input;
    input.open("input.txt");
    if (input.is_open())
    {
        while (std::getline (input, line))
        {
            // std::cout << line << std::endl;
            if (iter == 0)
            {
                // std::cout << "Read draw" << std::endl;
                // std::string draw = line;

                std::stringstream draw_ss;
                draw_ss << line;
                int x;
                while (draw_ss >> x)
                {
                    Card::draw.push_back(x);
                    if (draw_ss.peek() == ',')
                        draw_ss.ignore();
                }
            }
            else if (line.size() == 0)
            {
                // std::cout << "Read empty line" << std::endl;
                card_row = 0;
            }
            else
            {
                // std::cout << "Read card row: " << card_row << std::endl;
                std::vector<int>   lineData;
                std::stringstream  lineStream(line);
                int value;
                while(lineStream >> value)
                {
                    // std::cout << value << std::endl;
                    lineData.push_back(value);
                }
                card.push_back(lineData);

                card_row += 1;
            }

            if (card_row == 5)
            {
                card_set.push_back(card);
                card.clear();
            }
            iter += 1;
        }
    }

    // Part 1: What will the final score of the best card be?
    int fewest_turns = 500;
    int winning_card_index;
    for (int i = 0; i < card_set.size(); i++)
    {
        card_set[i].TurnsToBingo();
        card_set[i].ScoreCard();
        if (card_set[i].turns_to_bingo < fewest_turns)
        {
            fewest_turns = card_set[i].turns_to_bingo;
            winning_card_index = i;
        }
    }
    Card winning_card = card_set[winning_card_index];
    // winning_card.PrintCard();

    std::cout << "Winning Card's Final Score: " << winning_card.score << std::endl;

    // Part 2: What will the final score of the worst card be?
    int most_turns = 0;
    int losing_card_index;
    for (int i = 0; i < card_set.size(); i++)
    {
        if (card_set[i].turns_to_bingo > most_turns)
        {
            most_turns = card_set[i].turns_to_bingo;
            losing_card_index = i;
        }
    }
    Card losing_card = card_set[losing_card_index];
    // losing_card.PrintCard();

    std::cout << "Losing Card's Final Score: " << losing_card.score << std::endl;

}