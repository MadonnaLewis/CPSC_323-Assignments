#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cmath>


using namespace std;



const char KEYWORDS[21][10] = {"int", "float", "bool", "true", "false", "if",
                                 "else", "then", "endif", "while", "while", "whileend",
                                 "do", "doend", "for", "forend", "input",
                                 "output", "and", "or", "not"};

const char SEPARATORS[] = "(){}[],.:;";

const char OPERATORS[] = "*+-=/><%";

int isKeyword(char buffer[])
{
    int i,flag = 0;

    for(i=0; i<21; i++)
    {
        if(strcmp(KEYWORDS[i], buffer) == 0)
        {
            flag = 1;
            break;
        }
    }
    return flag;
}

bool isSeperator(char ch)
{
    bool k = false;
    int i;
    for(i=0; i < 10; i++)
    {
        if(ch == SEPARATORS[i])
        {
            k = true;
            return k;
        }
    }

    return k;
}

int isNumber(char buffer[])
{
    int flag =1;
    int i = atoi(buffer);
    if(isnan(i) || i == 0)
    {
        flag = 0;
    }
    return flag;

}

int main()
{
    ifstream fin("input2.txt");
    int i,j = 0;
    char ch;
    char buffer[20]; 

    if(!fin.is_open())
    {
        cout << "Error opening file!\n";
        exit(0);
    }
    
    cout << "TOKEN\t\t\tLEXEMS\n\n";

    while(!fin.eof())
    {
        ch = fin.get();

        // This is to disregard comments by first identifying the first '!' then performing a while
        // loop unitl the second '!' is found. 
        if(ch == '!')
        {
            ch = fin.get();
            while(ch != '!')
            {
                ch = fin.get();
            }
        }

        for(i=0; i < 8; i++)
        {
            if(ch == OPERATORS[i])
                cout << "OPERATOR\t=\t"<<ch<<endl;

        }
        if(isalnum(ch) || ch == '$')
        {
            
            buffer[j++] = ch;
        }
        else if((ch == ' ' || ch == '\n' || !isalnum(ch)) && (j != 0 || isSeperator(ch)))
        {
   				buffer[j] = '\0';
   				j = 0;
                
                if(isNumber(buffer)==1)
                {
                    cout <<"INTEGER\t\t=\t" << buffer<<endl;
                }
   				if(isKeyword(buffer) == 1)
                {
                    cout<<"KEYWORD\t\t=\t"<<buffer<<endl;
                }   					
   				else if(isKeyword(buffer) == 0 && atoi(buffer) == 0 && buffer[0] != '\0')
                {
                    cout<<"IDENTIFIER\t=\t"<<buffer<<endl;
                }  
                for(i=0; i < 10; i++)
                {
                    if(ch == SEPARATORS[i])
                    {
                        cout <<"SEPARATOR\t=\t"<<ch<<endl;
                    }
                }
   		}
    }
    return 0;
}