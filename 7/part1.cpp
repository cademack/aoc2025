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
#include <cctype>

//Func to write output at end to see how simulation ran.
void write_lines(std::vector<std::string>& data_lines)
{
    std::ofstream outputFile("output.txt");
    for(auto l : data_lines)
    {
        outputFile << l << std::endl;
    }
    outputFile.close();
}

int main()
{
    // std::ifstream inputFile("example.txt");
    std::ifstream inputFile("input.txt");

    if (!inputFile.is_open())
    {
        std::cout << "File no work" << std::endl;
        return 1;
    }

    //split file into lines
    std::vector<std::string> lines;
    inputFile.clear();
    inputFile.seekg(0);
    std::string tline;
    while(std::getline(inputFile, tline))
    {
        lines.push_back(tline);
    }

    size_t line_length = lines[0].length();
    size_t num_lines = lines.size();
    std::cout << "Num lines: " << num_lines << std::endl;
    std::cout << "Line length: " << line_length << std::endl;

    double total_sum = 0;

    for(size_t line_i = 1; line_i < num_lines; line_i++)
    {
        //gonna use the vec of strings as the data structure, gonna update it drawing the lines as we should.
        std::string cur_line = lines[line_i];
        std::string prev_line = lines[line_i - 1];

        //first do a pass to carry down all lasers we can
        for(size_t char_i = 0; char_i < line_length; char_i++)
        {
            char cur_char = cur_line[char_i];
            char above_char = prev_line[char_i];
            if(cur_char == '.' && (above_char == '|' || above_char == 'S'))
            {
                cur_line[char_i] = '|';
            }
        }

        //then do a pass to handle the splitting
        for(size_t char_i = 0; char_i < line_length; char_i++)
        {
            char cur_char = cur_line[char_i];
            char above_char = prev_line[char_i];
            if(cur_char == '^' && above_char == '|')
            {
                total_sum += 1;
                if(char_i > 0)
                {
                    if(cur_line[char_i-1] != '|')
                    {
                        cur_line[char_i-1] = '|';
                    }
                }
                if(char_i < line_length - 1)
                {
                    if(cur_line[char_i+1] != '|')
                    {
                        cur_line[char_i+1] = '|';
                    }
                }
            }
        }
        //update lines
        lines[line_i] = cur_line;
    }

    write_lines(lines);

    std::cout << std::fixed << std::setprecision(0);
    std::cout << "Total: " << total_sum << std::endl;
    return 0;
}
