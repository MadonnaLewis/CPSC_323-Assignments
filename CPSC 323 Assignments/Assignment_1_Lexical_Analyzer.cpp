#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cmath>
using namespace std;

// KEYWORDS will contain all keywords that can be used when perofmring Lexical analysis on the txt files
const char KEYWORDS[21][10] = {"int", "float", "bool", "true", "false", "if",
                                 "else", "then", "endif", "while", "while", "whileend",
                                 "do", "doend", "for", "forend", "input",
                                 "output", "and", "or", "not"};

// SEPERATORS will contain all separators that can be used when perofmring Lexical analysis on the txt files
const char SEPARATORS[] = "(){}[],.:;";

// OPERATORS will contain all operators that can be used when perofmring Lexical analysis on the txt files
const char OPERATORS[] = "*+-=/><%";

/*
isKeyword will take in the current buffer of char and compare againts every KEYWORD. If there are no KEYWORDS that match buffer then buffer is flagged as
an identifier
*/
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

/*
isSeperator will take in the current char and compare againts every SEPERATOR. If there are SEPERATOR that match char then char is flagged as
a seperator
*/
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

/*
isNumber will take in the current buffer and convert to an integer. It will then check if this is an integer 
*/
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
    // Assign variables
    ifstream fin("input3.txt");
    int i,j = 0;
    char ch;
    char buffer[20]; 

    //Check if fin can be opened
    if(!fin.is_open())
    {
        cout << "Error opening file!\n";
        exit(0);
    }
    
    //output header
    cout << "TOKEN\t\t\tLEXEMS\n\n";

    //While loop to read in the text file and begin the lexical analysis
    while(!fin.eof())
    {
        //Read in character
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

        // A quick check if the Char is an operator
        for(i=0; i < 8; i++)
        {
            if(ch == OPERATORS[i])
                cout << "OPERATOR\t=\t"<<ch<<endl;

        }

        //Checks if the character is an alphanumeric or $. If it is then we add it to the buffer and conitnue reading in the next char
        //Else we output the buffer and classify as Keyword, integer, identifier, etc.
        if(isalnum(ch) || ch == '$')
        {
            
            buffer[j++] = ch;
        }
        else if((ch == ' ' || ch == '\n' || !isalnum(ch)) && (j != 0 || isSeperator(ch)))
        {
                // Adds null terminator at the end of buffer for logical reasons
   				buffer[j] = '\0';
                // Resets j for buffer positioning
   				j = 0;
                
                // Checks if buffer is a number
                if(isNumber(buffer)==1)
                {
                    cout <<"INTEGER\t\t=\t" << buffer<<endl;
                }

                // Checks if buffer is a keyword
   				if(isKeyword(buffer) == 1)
                {
                    cout<<"KEYWORD\t\t=\t"<<buffer<<endl;
                }
                //if buffer is NOT a keyword then it is classified as an identifier   					
   				else if(isKeyword(buffer) == 0 && atoi(buffer) == 0 && buffer[0] != '\0')
                {
                    cout<<"IDENTIFIER\t=\t"<<buffer<<endl;
                }

                //Checks for any sperators after creating a varible, making a statement, etc.
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