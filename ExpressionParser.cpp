#include "ExpressionParser.h"

/// @author Alexander Pinkerton

std::unordered_map<std::string, ExpressionParser::Operator> ExpressionParser::ops =
        {
                {"=", Operator::EQUALS},
                {"+", Operator::ADD},
                {"-", Operator::SUBTRACT},
                {"*", Operator::MULTIPLY},
                {"/", Operator::DIVIDE},
                {"^", Operator::POWER},
                {"(", Operator::LEFTPARENTHESIS},
                {")", Operator::RIGHTPARENTHESIS}
        };

ExpressionParser::ExpressionParser()
{
}

ExpressionParser::~ExpressionParser()
{
}

std::string ExpressionParser::generateRPN(std::string &infix)
{
    std::string output;
    std::string formatted;
    std::stack<std::string> operatorStack;

    //Remove the whitespace from the string
    std::string::iterator end_pos = std::remove(infix.begin(), infix.end(), ' ');
    infix.erase(end_pos, infix.end());

    bool lastOp = false;

    //Format the infix to be easier read.
    for (unsigned int i = 0; i < infix.length(); i++) {
        std::string character = infix.substr(i, 1);
        if (ops.find(character) != ops.end()) {
            //Character is a operator
            if (!lastOp) {
                formatted += " ";
                formatted += infix.at(i);
                formatted += " ";
            } else {
                formatted += infix.at(i);
                formatted += " ";
            }
            lastOp = true;
        } else {
            //Character is a operand
            formatted += infix.at(i);
            lastOp = false;
        }
    }

    infix = formatted;
    //-----------

    //Parse the expression.
    for (std::string token : FileUtility::split(infix, ' ')) {
        // Found Operator
        if (ops.find(token) != ops.end()) {
            switch (token.at(0)) {
                case '(':
                    // Found Left Parenthesis
                    operatorStack.push(token);
                    break;
                case ')':
                    // Found Right Parenthesis
                    while (operatorStack.top() != "(") {
                        //Append each operator until left parenthesis.
                        output += operatorStack.top();
                        output += " ";
                        operatorStack.pop();
                        //Throw away left parenthesis
                    }
                    operatorStack.pop();
                    break;
                default:
                    while (!operatorStack.empty() && ExpressionParser::isHigherPrec(token, operatorStack.top())) {
                        output += operatorStack.top();
                        output += " ";
                        operatorStack.pop();
                    }
                    operatorStack.push(token);
                    break;
            }
        } else {
            // Found Digit or term.
            //output.append(token).append(' ');
            output += token;
            output += " ";
        }
    }

    while (!operatorStack.empty()) {
        output += operatorStack.top();
        output += " ";
        operatorStack.pop();
    }

    //-------------------

    return output;
}

float ExpressionParser::evaluateExpression(std::vector<std::string> &cells, std::string &postfix)
{
    //Evaluate the postfix expression on the columns one row at a time.
    std::stack<float> operandStack;

    for (std::string token : FileUtility::split(postfix, ' ')) {
        if (ops.find(token) != ops.end()) {
            // Found Operator
            //TODO: Use something other than this
            float intermediate = -666.9876543211234567890f;
            float rightOperand = operandStack.top();
            operandStack.pop();
            float leftOperand = operandStack.top();
            operandStack.pop();

            switch (token.at(0)) {
                case '=':
                    //??
                    break;
                case '+':
                    intermediate = leftOperand + rightOperand;
                    break;
                case '-':
                    intermediate = leftOperand - rightOperand;
                    break;
                case '*':
                    intermediate = leftOperand * rightOperand;
                    break;
                case '/':
                    intermediate = leftOperand / rightOperand;
                    break;
                case '^':
                    intermediate = std::pow(leftOperand, rightOperand);
                    break;
            }
            operandStack.push(intermediate);

        } else {
            // Found Digit or term.
            //TODO Allow variables to allow for more complex terms.
            if (token != "") {
                float num = 0;
                int index = 0;
                try {
                    index = std::stoi(token);
                    num = std::stof(cells[index]);
                }
                catch (std::invalid_argument &e) {
                    // if no conversion could be performed
                    std::cout << "Unable to parse expression" << std::endl;
                }
                catch (std::out_of_range &e) {

                }
                operandStack.push(num);
            }
        }
    }

    return operandStack.top();
}

//Function to check order of operations.
bool ExpressionParser::isHigherPrec(std::string &op, std::string &sub)
{
    return (ops.find(sub) != ops.end() && ops.at(sub) >= ops.at(op));
}
