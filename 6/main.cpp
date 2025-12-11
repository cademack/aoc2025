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


char get_operand(int prob, int op_line, std::ifstream& file)
{
    file.clear();
    file.seekg(0);
    char c;
    for(int i = 0; i < op_line; i++)
    {
        file.get(c);
        while(c != '\n')
            file.get(c);
    }

    file.get(c);
    for(int i = 0; i < prob; i++)
    {
        while(c == ' ')
        {
            file.get(c);
        }

        while(c != ' ')
        {
            file.get(c);
        }

        while(c == ' ')
        {
            file.get(c);
        }
    }

    return c;
}

int count_problems(std::ifstream& file)
{
    int out = 0;
    file.clear();
    file.seekg(0);
    bool inNumber = false;
    char c;
    while (file.get(c))
    {
        if(std::isdigit(c))
        {
            inNumber = true;
        }
        else
        {
            //should be some form of white space
            if(inNumber)
            {
                out++;
                inNumber = false;
            }
            if(c == '\n')
            {
                return out;
            }

        }
    }
    return -1;
}

void get_indices(int* indices_arr, int indices_len, int op_line, std::ifstream& file)
{
    file.clear();
    file.seekg(0);

    indices_arr[0] = 0;
    //skip to operand line
    char c;
    int max_line_len = -1;
    for(int i = 0; i < op_line; i++)
    {
        int line_len = 0;
        file.get(c);
        while(c != '\n')
        {
            file.get(c);
            line_len++;
        }

        if(line_len > max_line_len)
            max_line_len = line_len;
    }

    //can skip the first
    file.get(c);
    int cur_line_idx = 1;
    int cur_arr_idx = 1;
    while(file.get(c))
    {
        if(c == '*' || c == '+')
        {
            indices_arr[cur_arr_idx] = cur_line_idx;
            cur_arr_idx++;
        }
        cur_line_idx++;
    }
    indices_arr[indices_len - 1] = max_line_len;
}

int count_values(std::ifstream& file)
{
    int out = 0;
    file.clear();
    file.seekg(0);
    char c;
    while (file.get(c))
    {
        if(c == '\n')
        {
            out++;
        }
    }
    return out - 1;
}


int main()
{
    // std::ifstream inputFile("example.txt");
    std::ifstream inputFile("input.txt");
    std::stringstream ss;

    if (!inputFile.is_open())
    {
        std::cout << "File no work" << std::endl;
        return 1;
    }

    const int problems = count_problems(inputFile);
    const int values = count_values(inputFile);

    std::cout << "problems: "  << problems << std::endl;
    std::cout << "values: "  << values << std::endl;

    std::cout << "==============================================" << std::endl;

    int indices[problems+1];
    get_indices(indices, problems+1, values, inputFile);

    for(int i = 0; i < problems+1; i++)
    {
        std::cout << "index: "  << indices[i] << std::endl;
    }


    // double total_sum = 0;
    // for(int pi = 0; pi < problems; pi++)
    // {
    //     //get the operand and do the stuff. should be homefree from here.
    //     char operand = get_operand(pi, values, inputFile);
    //     // std::cout << "op: "  << operand << std::endl;

    //     double out_val = 0;
    //     if(operand == '*')
    //         out_val = 1;

    //     std::string num_strings[values];
    //     for(int i = 0; i < values; i++)
    //     {
    //         std::ostringstream oss;
    //         oss << std::fixed << std::setprecision(0) << numbers[i][pi];
    //         num_strings[i] = oss.str();
    //     }


    //     switch(operand)
    //     {
    //     case '*':
    //         for(int vi = 1; vi < values; vi++)
    //         {
    //             out_val *= numbers[vi][pi];
    //         }
    //         break;
    //     case '+':
    //         for(int vi = 1; vi < values; vi++)
    //         {
    //             out_val += numbers[vi][pi];
    //         }
    //         break;
    //     }
    //     total_sum += out_val;
    // }

    // std::cout << std::fixed << std::setprecision(8);
    // std::cout << "Total: " << total_sum << std::endl;
    return 0;
}