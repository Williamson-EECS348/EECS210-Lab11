
#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <vector>

/**
 * @brief Converts a postfix expression to prefix notation
 * 
 * @param postfix The postfix expression as a string
 * @return std::string The converted prefix expression
 */
std::string postfixToPrefix(const std::string& postfix) {
    std::stack<std::string> stack; // Stack to hold operands and intermediate results; use a stack of strings because we want a first-in last-out behavior
    std::stringstream ss(postfix); // String stream to parse the postfix expression
    std::string token; // Variable to hold each token

    while (ss >> token) { // Read each token from the postfix expression
        // Check if token is an operator
        if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^") {
            if (stack.size() < 2) { // Ensure there are at least two operands to pop
                std::cout << "Error: Invalid postfix expression\n"; // Inform user of error
                return ""; // Return empty string to indicate error
            }

            // Pop two operands
            std::string operand2 = stack.top(); // get the second operand; it is popped first because of first-in last-out order
            stack.pop(); // remove it from the stack since we are using it now
            std::string operand1 = stack.top(); // get the first operand
            stack.pop(); // remove it from the stack since we are using it now

            // Create prefix expression: operator operand1 operand2
            std::string prefixExpr = token + " " + operand1 + " " + operand2;
            // Push the new prefix expression back onto the stack so that it can be used in further operations
            // this will allow us to build more complex expressions as we continue parsing
            stack.push(prefixExpr);
        } else {
            // Token is an operand (variable or number)
            stack.push(token); // Push operand onto the stack
        }
    }

    // The stack should contain exactly one element (the final prefix expression)
    if (stack.size() != 1) { // Validate final stack size
        std::cout << "Error: Invalid postfix expression\n"; // Inform user of error
        return ""; // Return empty string to indicate error
    }

    return stack.top(); // Return the final prefix expression
}

/**
 * @brief Get the Postfix Expr object; this was translated from the given python code
 * 
 * @return std::string 
 */
std::string getPostfixExpr() {
    std::string validOps = "+-*/^"; // Valid operators string; we can loop through chars to check
    std::string validNums = "123"; // Valid numbers string
    std::string validVars = "xyz"; // Valid variable string

    bool loop = true; // Loop control variable
    std::string pfInput{}; // Postfix input string
    do { // Loop until valid input is received; use do-while to ensure at least one execution
        pfInput.clear(); // Clear previous input in case of reloop
        std::cout << "Enter an arithmetic expression in postfix form: \n"; // Prompt user for input
        std::getline(std::cin, pfInput); // Get entire line of input; allows spaces

        std::stringstream ss(pfInput); // String stream to parse input
        std::string word{}; // Variable to hold each word/token
        bool allValid = true; // Flag to track overall validity
        while (ss >> word) { // Read each word/token from the input
            bool valid = true; // Flag to track validity of current word/token
            for (char c : word) { // Check each character in the word/token
                if (validOps.find(c)  == std::string::npos && // Not found in operators
                    validNums.find(c) == std::string::npos && // Not found in numbers
                    validVars.find(c) == std::string::npos) { // Not found in variables
                    valid = false; // Mark as invalid
                    break; // No need to check further characters so break from loop
                }
            }

            if (!valid) { // If any word/token is invalid
                std::cout << "Input Invalid\n"; // Inform user of invalid input
                allValid = false; // Mark overall validity as false
                break; // Exit the while loop early
            }
        }
        if (allValid) { // If all tokens are valid
            loop = false; // Exit the input loop
        }
    } while (loop); // Continue looping until valid input is received

    return pfInput; // Return the valid postfix input
}

int main() {
    std::string postfix = getPostfixExpr(); // Get valid postfix expression from user
    std::string prefix = postfixToPrefix(postfix); // Convert postfix to prefix

    if (!prefix.empty()) // If conversion was successful
        std::cout << prefix << std::endl; // Display prefix expression
}