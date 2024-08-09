# Lexical Analysis in C with Graphs and Matrices

In C programming, graphs and matrices are often used to represent relationships between elements. A graph is a set of nodes (or vertices) connected by edges. A matrix can represent a graph, showing which nodes are connected to which others.

Graphs are used in many applications, including social networks, computer networks, and route planning. In the context of lexical analysis or parsing, graphs can represent the relationships between states in a finite state machine, helping to determine how tokens are recognized in a programming language.

## Graph Representation in C

A graph can be represented in several ways, but one common approach is using an adjacency matrix. An adjacency matrix is a 2D array where the element at row `i` and column `j` is `1` if there's an edge from node `i` to node `j`, and `0` otherwise.

Here's a simple example:

```c
#include <stdio.h>

#define N 4

void print_matrix(int matrix[N][N]) 
{
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }

        printf("\n");
    }
}

int main() 
{
    int graph[N][N] = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };

    print_matrix(graph);

    return 0;
}
```

In this example, we define a graph with 4 nodes. The adjacency matrix shows the connections between these nodes. For instance, node `0` is connected to nodes `1` and `3`, as indicated by the `1`s in the matrix.

### Practical Example: Lexical Analysis

Lexical analysis, or tokenization, involves breaking down a sequence of characters into tokens that can be used for further processing, such as parsing in a compiler. Here, a graph can represent states in a finite state machine (FSM) used to recognize tokens.

Let's implement a simple FSM for recognizing binary numbers (sequences of `0`s and `1`s):

```c
#include <stdio.h>
#include <stdbool.h>

#define N 3

// State transitions:
//  row = current state
//  col = input (0 or 1)
int fsm[N][2] = {
    {1, 2},  // state 0: initial state
    {1, 1},  // state 1: accepting state for binary numbers
    {2, 2}   // state 2: error state
};

bool is_binary_number(const char *input) 
{
    int state = 0;

    for (int i = 0; input[i] != '\0'; i++) 
    {
        int input_value = input[i] - '0';

        if (input_value < 0 || input_value > 1) 
        {
            state = 2; // move to error state for invalid input
            break;
        }
        state = fsm[state][input_value];
    }

    return state == 1; // return true if ending in accepting state
}

int main() {
    const char *test1 = "101";
    const char *test2 = "102";

    printf("Is %s a binary number? %s\n", test1, is_binary_number(test1) ? "Yes" : "No");
    printf("Is %s a binary number? %s\n", test2, is_binary_number(test2) ? "Yes" : "No");

    return 0;
}
```

I've defined a simple FSM with three states. The adjacency matrix `fsm` shows state transitions based on input characters (`0` or `1`). The `is_binary_number` function processes an input string and uses the FSM to determine if the string is a valid binary number.

## Another Example in Lexical Analysis

**Get the file [here](/graph_fsm.c).**

I would like to explore a simple example of how to use a finite state machine (FSM) in C programming to validate basic arithmetic expressions. The goal is to determine whether a string of characters, like "3+2-1", is a valid arithmetic expression using digits and the operators `+` and `-`.

### Defining the Finite State Machine

The FSM is represented by a 2D array called an adjacency matrix. Each row in this matrix corresponds to a state, and each column corresponds to an input type (e.g., digit, `+`, `-`, or any other character). The value in each cell indicates the next state the machine will transition to when it reads a specific input in a given state.

For example, consider the FSM matrix:

```c
int fsm[N][4] = {
    {1, 3, 3, 4}, // state 0: initial state
    {1, 2, 2, 4}, // state 1: accepting state for digits
    {1, 4, 4, 4}, // state 2: after operator, expect digit
    {4, 4, 4, 4}, // state 3: error state
    {4, 4, 4, 4}  // state 4: error state
};
```

Here, there are five states (from 0 to 4). State 0 is the initial state, where the FSM expects to read a digit. If it does, it transitions to state 1. If the FSM reads a `+` or `-` while in state 1, it transitions to state 2, expecting another digit. States 3 and 4 are error states that represent invalid expressions.

### Handling Input Characters

To process the input string, a function is needed to map each character to the appropriate column in the FSM matrix. This function, `char_to_column`, converts a character to its corresponding column index:

```c
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
```

This function ensures that digits map to column 0, `+` maps to column 1, `-` maps to column 2, and any other character (such as letters or punctuation) maps to column 3.

### Validating the Expression

The core of the program is the `is_valid_expression` function. It starts in the initial state (state 0) and processes each character of the input string one by one:

```c
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
```

As the function reads each character, it determines the next state using the FSM matrix. If the FSM reaches state 4, it stops processing because the expression is invalid. After processing all characters, the function returns `true` if the FSM ends in either state 1 or 2 (valid states), and `false` otherwise.

### Testing the FSM

Finally, in the `main` function, I could test the FSM with two example expressions like this:

```c
int main() 
{
    const char* test1 = "3+2-1";
    const char* test2 = "3++2";

    printf("Is \"%s\" a valid expression? %s\n", test1, is_valid_expression(test1) ? "Yes" : "No");
    printf("Is \"%s\" a valid expression? %s\n", test2, is_valid_expression(test2) ? "Yes" : "No");

    return 0;
}
```

The output for `test1` ("3+2-1") will be "Yes" because it's a valid arithmetic expression. However, `test2` ("3++2") will output "No" because it contains consecutive operators, which the FSM correctly identifies as invalid.

### Conclusion

This simple example showed how to implement and use a finite state machine in C to validate arithmetic expressions. By mapping inputs to states and defining transitions, the FSM can efficiently determine whether a string follows the rules of a simple arithmetic language. This approach can be extended to more complex languages and is a fundamental concept in lexical analysis and parsing.

**👉 Using graphs and matrices in this way allowed me to create efficient and understandable solutions for lexical analysis and parsing, making it easier to build complex language processing tools.**

## License

This project is licensed under the CC BY-NC 4.0 License. See the [LICENSE](LICENSE) file for details.## License

This project is licensed under the Creative Commons Attribution-NonCommercial 4.0 International (CC BY-NC 4.0) License.

You are free to:

- Share — copy and redistribute the material in any medium or format
- Adapt — remix, transform, and build upon the material

Under the following terms:

- Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.
- NonCommercial — You may not use the material for commercial purposes.

No additional restrictions — You may not apply legal terms or technological measures that legally restrict others from doing anything the license permits.

For more details, refer to the [LICENSE](./LICENSE) file.

### Author

Navid Dezashibi  
<navid@dezashibi.com>
