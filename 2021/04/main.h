class Card
{
public:
    static std::vector<int> draw;
    std::vector< std::vector<int> > layout;
    std::vector< std::vector<int> > marker;
    int turns_to_bingo;
    int score;

    Card()
        : marker(5, std::vector<int>(5, 0)), turns_to_bingo(500)
    {
    }

    void clear()
    {
        layout.clear();
    }

    void push_back(std::vector<int> line)
    {
        layout.push_back(line);
    }

    void PrintCard()
    {
        for (std::vector<int> row : layout)
        {
            for (int i : row)
                std::cout << i << " ";
            std::cout << std::endl;
        }
    }

    void PrintMarker()
    {
        for (std::vector<int> row : marker)
        {
            for (int i : row)
                std::cout << i << " ";
            std::cout << std::endl;
        }
    }

    bool IsBingo(int row, int col)
    {
        // Check for Bingo in just marked row
        int rowScore = 0;
        for (int i = 0 ; i < 5; i++)
        {
            rowScore += marker[row][i];
            if (rowScore == 5)
            {
                return true;
            }
        }
        // Check for Bingo in just marked column
        int colScore = 0;
        for (int i = 0; i < 5; i++)
        {
            colScore += marker[i][col];
            if (colScore == 5)
            {
                return true;
            }
        }
        return false;
    }

    void TurnsToBingo()
    {
        bool is_marker_placed;
        for (int i = 0; i < draw.size(); i++)
        {
            // std::cout << "drawn number: " << draw[i] << std::endl;
            is_marker_placed = false;
            for (int j = 0; j < 5; j++)
            {
                if (is_marker_placed)
                    continue;
                for (int k = 0; k < 5; k++)
                {
                    if (is_marker_placed)
                        continue;
                    // std::cout << "i: " << i << ", j: " << j << ", k: " << k << ", spot: " << layout[j][k] << std::endl;
                    if (layout[j][k] == draw[i])
                    {
                        // std::cout << "place marker" << std::endl;
                        marker[j][k] = 1;
                        is_marker_placed = true;
                        // PrintCard(marker);
                        if (IsBingo(j,k))
                        {
                            turns_to_bingo = i + 1;
                            return;
                        }
                    }
                }
            }
        }
    }

    void ScoreCard()
    {
        int tempScore = 0;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (marker[i][j] == 0)
                {
                    tempScore += layout[i][j];
                }
            }
        }
        score = tempScore * draw[turns_to_bingo - 1];
    }
};