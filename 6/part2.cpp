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
    indices_arr[indices_len - 1] = max_line_len + 1;
}

int count_number_rows(std::ifstream& file)
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

    if (!inputFile.is_open())
    {
        std::cout << "File no work" << std::endl;
        return 1;
    }

    const int problems = count_problems(inputFile);
    const int number_rows = count_number_rows(inputFile);


    int indices[problems+1];
    get_indices(indices, problems+1, number_rows, inputFile);


    //split file into lines
    std::vector<std::string> lines;
    inputFile.clear();
    inputFile.seekg(0);
    std::string tline;
    while(std::getline(inputFile, tline))
    {
        lines.push_back(tline);
    }


    double total_sum = 0;
    for(int pi = 0; pi < problems; pi++)
    {
        char operand = get_operand(pi, number_rows, inputFile);

        double out_val = 0;
        if(operand == '*')
            out_val = 1;


        int start_index = indices[pi];
        int end_index = indices[pi+1] - 1;
        std::vector<double> prob_values;
        for(int line_i = start_index; line_i < end_index; line_i++)
        {
            //for each value, we need to build a string from the numbers top to bottom of each place value
            std::stringstream ss;
            for(int j = 0; j < number_rows; j++)
            {
                if(line_i < lines[j].length() && std::isdigit(lines[j][line_i]))
                    ss << lines[j][line_i];
            }
            prob_values.push_back(std::stod(ss.str()));
        }

        for(auto pval : prob_values)
        {
            switch(operand)
            {
            case '*':
                out_val *= pval;
                break;
            case '+':
                out_val += pval;
                break;
            }
        }
        total_sum += out_val;
    }

    std::cout << std::fixed << std::setprecision(8);
    std::cout << "Total: " << total_sum << std::endl;
    return 0;
}