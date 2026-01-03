/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 12:34:42 by frromero          #+#    #+#             */
/*   Updated: 2026/01/03 20:45:32 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <exception>
#include <stdexcept>
#include <cctype>

RPN::RPN(void) {}

RPN::RPN(const std::string &str)
{
    double a = 0;
    double b = 0;
    for (size_t i = 0; i < str.length(); i++)
    {
        char c = str[i];

        if (c == ' ' || c == '\t')
            continue;

        e_token token = validateTokens(c);

        switch (token)
        {
        case INT:
            _rpnStack.push(static_cast<float>(c - '0'));
            break;

        case ADD:
            if (_rpnStack.size() >= 2)
            {
                b = _rpnStack.top();
                _rpnStack.pop();
                a = _rpnStack.top();
                _rpnStack.pop();
                _rpnStack.push(a + b);
            }
            else
                throw std::runtime_error("Error");
            break;

        case SUBT:
            if (_rpnStack.size() >= 2)
            {
                b = _rpnStack.top();
                _rpnStack.pop();
                a = _rpnStack.top();
                _rpnStack.pop();
                _rpnStack.push(a - b);
            }
            else
                throw std::runtime_error("Error");
            break;

        case MULT:
            if (_rpnStack.size() >= 2)
            {
                b = _rpnStack.top();
                _rpnStack.pop();
                a = _rpnStack.top();
                _rpnStack.pop();
                _rpnStack.push(a * b);
            }
            else
                throw std::runtime_error("Error");
            break;

        case DIV:
            if (_rpnStack.size() >= 2)
            {
                b = _rpnStack.top();
                _rpnStack.pop();
                if (b == 0)
                    throw std::runtime_error("Error");
                a = _rpnStack.top();
                _rpnStack.pop();
                _rpnStack.push(a / b);
            }
            else
                throw std::runtime_error("Error");
            break;

        case ERROR:
        default:
            throw std::runtime_error("Error");
        }
    }
}

RPN::RPN(RPN const &copy) : _rpnStack(copy._rpnStack) {}

RPN::~RPN(void) {}

RPN &RPN::operator=(RPN const &other)
{
    if (this != &other)
        _rpnStack = other._rpnStack;
    return *this;
}

float RPN::calculateRPN()
{
    if (_rpnStack.size() != 1)
        throw std::runtime_error("Error");
    float result = 0;
    result = _rpnStack.top();
    _rpnStack.pop();
    return result;
}

e_token RPN::validateTokens(char c)
{
    if (isdigit(c))
        return INT;
    else if (c == '+')
        return ADD;
    else if (c == '-')
        return SUBT;
    else if (c == '*')
        return MULT;
    else if (c == '/')
        return DIV;
    return ERROR;
}
