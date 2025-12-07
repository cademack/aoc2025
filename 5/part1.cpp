#include <iostream>
#include <fstream>

#include <sstream>
#include <string>
#include <vector>
#include <utility>

struct Range {
    double min;
    double max;
};

Range get_range(std::string& line)
{
    int line_len = line.size();
    int split_idx = line.find('-');
    if(split_idx == -1)
    {
        std::cout << "Oh no!!!" << line << std::endl;
        return Range{0, 0};
    }
    double min_bound = std::stod(line.substr(0, split_idx));
    double max_bound = std::stod(line.substr(split_idx+1, line_len - split_idx - 1));

    return Range{min_bound, max_bound};
}

int main()
{
    std::ifstream inputFile("input.txt");

    if (!inputFile.is_open())
    {
        std::cout << "File no work" << std::endl;
        return 1;
    }


    std::vector<Range> ranges;

    std::string line;
    //parse each range and add to vec
    while(true)
    {
        std::getline(inputFile, line);

        if(line.length() == 0)
            break;
        Range line_range = get_range(line);
        // std::cout << "Line: " << line << std::endl;
        // std::cout << "Min: " << line_range.min << std::endl;
        // std::cout << "Max: " << line_range.max << std::endl;
        ranges.push_back(line_range);
    }

    int valid_ids = 0;
    //parse each value and check if in between any ranges
    while(true)
    {
        std::getline(inputFile, line);

        if(line.length() == 0)
            break;

        double line_id = std::stod(line);

        bool found_acceptable_range = false;
        for(auto const range_i : ranges)
        {
            if (line_id >= range_i.min && line_id <= range_i.max)
            {
                found_acceptable_range = true;
                break;
            }
        }

        if(found_acceptable_range)
            valid_ids++;
    }

    inputFile.close();
    std::cout << "Valid ids:" << valid_ids << std::endl;
    return 0;
}