// INSERT COMMENT
#include <iostream>
#include <string>
#include <sstream>

std::string getPostfixExpr() {
    std::string validOps = "+-*/^";
    std::string validNums = "123";
    std::string validVars = "xyz";

    bool loop = false;
    std::string pfInput{};
    do {
        pfInput.clear();
        std::cout << "Enter an arithmetic expression in postfix form: \n";
        std::getline(std::cin, pfInput);

        std::stringstream ss(pfInput);
        std::string word{};
        while (ss >> word) {
            bool valid = true;
            for (char c : word) {
                if (validOps.find(c)  == std::string::npos &&
                    validNums.find(c) == std::string::npos &&
                    validVars.find(c) == std::string::npos) { valid = false; }

            }
            if (!valid) {
                std::cout << "Input Invalid\n";
                loop = true;
                break;
            }
        }
    } while (loop);

    return pfInput;

}

int main() {
    std::string postfix = getPostfixExpr();
    std::cout << postfix << std::endl;
}