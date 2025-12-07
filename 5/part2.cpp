#include <iostream>
#include <fstream>

#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <utility>
#include <limits>
#include <algorithm>
#include <iomanip>

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

Range combine_ranges(std::vector<Range> rs)
{
    double new_min = std::numeric_limits<double>::max();
    double new_max = std::numeric_limits<double>::min();

    for(auto const r : rs)
    {
        if(r.min < new_min)
            new_min = r.min;
        if(r.max > new_max)
            new_max = r.max;
    }
    return Range{new_min, new_max};
};

bool overlap(Range r1, Range r2)
{
    return (r1.min <= r2.max && r1.max >= r2.min);
};

int main()
{
    std::ifstream inputFile("input.txt");

    if (!inputFile.is_open())
    {
        std::cout << "File no work" << std::endl;
        return 1;
    }


    std::vector<Range> remaining_ranges;

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
        remaining_ranges.push_back(line_range);
    }

    //build a list of "disjoint" ranges (no overlap).
    //start with first one, then try to add each remaining by checking
    // if it overlaps with any ranges involved (possibly multiple!. combine all overlapping and merge them into one)
    std::vector<Range> disjoint_ranges;
    disjoint_ranges.push_back(remaining_ranges.back());
    remaining_ranges.pop_back();

    while(!remaining_ranges.empty())
    {
        Range q_range = remaining_ranges.back();
        remaining_ranges.pop_back();

        std::vector<int> overlapping_indices;
        std::vector<Range> overlapping_ranges;
        for(int i = 0; i < disjoint_ranges.size(); i++)
        {
            if(overlap(q_range, disjoint_ranges.at(i)))
            {
                overlapping_indices.push_back(i);
                overlapping_ranges.push_back(disjoint_ranges.at(i));
            }
        }


        if(overlapping_indices.size())
        {
            overlapping_ranges.push_back(q_range);
            Range new_range = combine_ranges(overlapping_ranges);
            std::sort(overlapping_indices.rbegin(), overlapping_indices.rend());
            for(int idx : overlapping_indices)
            {
                disjoint_ranges.erase(disjoint_ranges.begin() + idx);
            }
            disjoint_ranges.push_back(new_range);
        }
        else
        {
            disjoint_ranges.push_back(q_range);
        }
    }

    double available_ids = 0;
    for(auto r : disjoint_ranges)
    {
        available_ids += (r.max - r.min) + 1;
    }
    std::cout << std::fixed << std::setprecision(8);
    std::cout << "Available IDs: " << available_ids << std::endl;
    return 0;
}