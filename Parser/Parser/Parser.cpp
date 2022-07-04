// Parser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    std::string line;
    ifstream in("file.xml");

    bool begin_tag = false;
    std::string strtag;
    std::string content;
    std::string endtag;

    while (getline(in, line))
    {
        std::string tmp; // strip whitespaces from the beginning
        for (int i = 0; i < line.length(); i++)
        {
            
            if (line[i] == ' ' && tmp.size() == 0)
            {
            }
            else
            {
                tmp += line[i];
            }
        }

        int j = 1;

        for (int i = 0; i < tmp.length(); i++)
        {
            if (tmp[i] == '<' && tmp[i + 1] != '/')
            {
                for (j = i; j < tmp.length() && tmp[j] != '>'; j++)
                {
                    strtag += tmp[j];
                }
                cout << "Start tag: " << strtag << ">" << endl;
                i = j;
            }
            
            if (tmp[i] == '>')
            {
                for (j = i + 1; j < tmp.length() && tmp[j] != '<'; j++)
                {
                    content += tmp[j];
                }
                cout << "Content:" << content << endl;
                i = j ;
            }

            if (tmp[i] == '<' && tmp[i + 1] == '/')
            {
                for (j = i; j < tmp.length() && tmp[j] != '>'; j++)
                {
                    endtag += tmp[j];
                }
                cout << "End tag: " << endtag << ">" << endl;
                i = j;
            }
           

            strtag.clear();
            content.clear();
            endtag.clear();
        }
    }
}