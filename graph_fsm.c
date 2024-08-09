// ***************************************************************************************
//    Project: Lexical Analysis in C with Graphs and Matrices
//    File: graph_fsm.c
//    Date: 2024-08-09
//    Author: Navid Dezashibi
//    Contact: navid@dezashibi.com
//    Website: https://www.dezashibi.com | https://github.com/dezashibi
//    License:
//     Please refer to the LICENSE file, repository or website for more information about
//     the licensing of this work. If you have any questions or concerns,
//     please feel free to contact me at the email address provided above.
// ***************************************************************************************
// *  Description: Refer to the readme file
// ***************************************************************************************

#include <stdbool.h>
#include <stdio.h>

#define N 5

// State transitions:
//  row = current state,
//  col = input (digit, +, -, other)
int fsm[N][4] = {
    {1, 3, 3, 4}, // state 0: initial state
    {1, 2, 2, 4}, // state 1: accepting state for digits
    {1, 4, 4, 4}, // state 2: after operator, expect digit
    {4, 4, 4, 4}, // state 3: error state
    {4, 4, 4, 4}  // state 4: error state
};

int char_to_column(char ch)
{
    if (ch >= '0' && ch <= '9')
        return 0;
    if (ch == '+')
        return 1;
    if (ch == '-')
        return 2;

    return 3; // other characters
}

bool is_valid_expression(const char* input)
{
    int state = 0;

    for (int i = 0; input[i] != '\0'; i++)
    {
        int col = char_to_column(input[i]);
        state = fsm[state][col];
        if (state == 4)
            break; // move to error state for invalid input
    }

    return state == 1 || state == 2; // return true if ending in accepting states
}

int main()
{
    const char* test1 = "3+2-1";
    const char* test2 = "3++2";

    printf("Is \"%s\" a valid expression? %s\n", test1, is_valid_expression(test1) ? "Yes" : "No");
    printf("Is \"%s\" a valid expression? %s\n", test2, is_valid_expression(test2) ? "Yes" : "No");

    return 0;
}
