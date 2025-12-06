#include <iostream>
#include <fstream>

#include <sstream>
#include <string>


int main()
{
    std::ifstream inputFile("input.txt");

    if (!inputFile.is_open())
    {
        std::cout << "File no work" << std::endl;
        return 1;
    }


    std::stringstream buffer;
    buffer << inputFile.rdbuf();

    std::string fileString = buffer.str();
    inputFile.close();

    // find first \n to get line width, then length by width for num rows
    int width = fileString.find("\n") + 1;
    int length = fileString.length() / width;

    int total_count = 0;
    for (int string_i = 0; string_i < fileString.length(); string_i++)
    {
        int row = string_i / width;
        int col = string_i % width;

        char c = fileString[string_i];
        if(col == width - 1 || c != '@')
        {
            //This is either the newline character, or not a paper roll (@)
            continue;
        }

        std::cout << row << ", " << col <<  ", " << c << std::endl;

        int adjacent_rolls = 0;
        for(int h_offset = -1; h_offset < 2; h_offset++)
        {
           for(int v_offset = -1; v_offset < 2; v_offset++)
            {
                if(h_offset == 0 && v_offset == 0)
                    //current char does not matter
                    continue;

                int q_row = row + v_offset;
                int q_col = col + h_offset;

                //bounds checks
                if (q_col < 0 || q_col >= width)
                    continue;
                else if(q_row < 0 || q_row >= length)
                    continue;

                int q_string_i = (q_row * width) + q_col;
                char q_c = fileString[q_string_i];

                if(q_c == '@')
                    adjacent_rolls++;
            }
        }

        if(adjacent_rolls < 4)
        {
            total_count++;
        }
    }

    std::cout << "Total count: " << total_count << std::endl;
    return 0;
}