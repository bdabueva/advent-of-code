#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <sstream>
#include <string>

void PrintMap(const std::vector< std::vector<int> >& map)
{
    for (int i = 0; i <= 9; i++)
    {
        for (int j = 0; j <= 9; j++)
        {
            std::cout << map[j][i] << " ";
        }
        std::cout << std::endl;
    }
}

class VertexPair
{
public:
    int x1;
    int y1;
    int x2;
    int y2;

    VertexPair(int xa, int ya, int xb, int yb)
        : x1(xa), y1(ya), x2(xb), y2(yb)
    {
    }

    void Print()
    {
        std::cout << x1 << "," << y1 << " -> " << x2 << "," << y2 << std::endl;
    }

    void PlotLine(std::vector< std:: vector<int> >& map, bool ignore_diagnols)
    {
        if (x1 == x2)
        {
            // Plot horizontal line
            auto result = std::minmax({y1, y2});
            for (int i = result.first; i <= result.second; i++)
            {
                map[x1][i] += 1;
            }
        }
        else if (y1 == y2)
        {
            // Plot horizontal line
            auto result = std::minmax({x1, x2});
            for (int i = result.first; i <= result.second; i++)
            {
                map[i][y1] += 1;
            }
        }
        else if (!ignore_diagnols)
        {
            // Plot diagonal line
            auto result_x = std::minmax({x1, x2});
            auto result_y = std::minmax({y1, y2});
            if (((x1 < x2) && (y1 < y2)) || ((x1 > x2) && (y1 > y2)))
            {
                // process NW-SE line
                for (int i = 0; i <= result_x.second - result_x.first; i++)
                {
                    map[result_x.first+i][result_y.first+i] += 1;
                }
            }
            else if (((x1 > x2) && (y1 < y2)) || ((x1 < x2) && (y1 > y2)))
            {
                // process SE-NW line
                for (int i = 0; i <= result_x.second - result_x.first; i++)
                {
                    map[result_x.first+i][result_y.second-i] += 1;
                }
            }
        }
    }
};

struct Vertex {
    int x;
    int y;
};

Vertex GetMaxXY(std::vector<VertexPair> v_list)
{
    Vertex max;
    max.x = 0;
    max.y = 0;
    for (VertexPair v : v_list)
    {
        max.x = std::max(max.x, std::max(v.x1, v.x2));
        max.y = std::max(max.y, std::max(v.y1, v.y2));
    }
    return max;
}




int main()
{
    std::string line;
    std::size_t pos_arrow, pos_comma1, pos_comma2;
    int x1, y1, x2, y2;
    std::stringstream ss;
    std::vector<VertexPair> vertices;

    // read input
    std::ifstream input;
    input.open("input.txt");
    if (input.is_open())
    {
        while (std::getline (input, line))
        {
            // split string into various parts
            pos_arrow = line.find(" -> ");
            pos_comma1 = line.find(",");
            pos_comma2 = line.find(",", pos_arrow);
            x1 = stoi(line.substr(0,pos_comma1));
            y1 = stoi(line.substr(pos_comma1+1, pos_arrow-pos_comma1-1));
            x2 = stoi(line.substr(pos_arrow+4,pos_comma2-pos_arrow-4));
            y2 = stoi(line.substr(pos_comma2+1));
            VertexPair vertex_pair(x1, y1, x2, y2);
            vertices.push_back(vertex_pair);
        }
    }

    // Part 1: At how many points do at least two lines overlap?

    // Initialize map
    Vertex max = GetMaxXY(vertices);
    std::vector< std::vector<int> > map(max.x + 1, std::vector<int>(max.y + 1));

    // "Plot" lines on map
    for (VertexPair vp : vertices)
    {
        vp.PlotLine(map, true);
    }

    
    int count = 0;
    for (std::vector<int> row : map)
    {
        for (int x : row)
        {
            if (x > 1)
            {
                count += 1;
            }
        }
    }
    std::cout << "Number of points with more than one line (ignore diagnols): " << count << std::endl;

    // Part 2: Including diagnol lines, at how many points do at least two lines overlap?
    
    // Initialize map
    std::vector< std::vector<int> > map_with_diagnols(max.x + 1, std::vector<int>(max.y + 1));

    // "Plot" lines on map
    for (VertexPair vp : vertices)
    {
        vp.PlotLine(map_with_diagnols, false);
    }

    count = 0;
    for (std::vector<int> row : map_with_diagnols)
    {
        for (int x : row)
        {
            if (x > 1)
            {
                count += 1;
            }
        }
    }
    std::cout << "Number of points with more than one line (with diagnols): " << count << std::endl;
}