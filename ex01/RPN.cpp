/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 12:34:42 by frromero          #+#    #+#             */
/*   Updated: 2026/01/12 18:24:30 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <stdexcept>
#include <cctype>
#include <cstdlib>
#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const std::string &expression)
{
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token)
    {
        if (token.length() == 1 && std::isdigit(token[0]))
        {
            int num = token[0] - '0';
            if (num < 0 || num >= 10)
                throw std::runtime_error("Error");

            _rpnStack.push(static_cast<float>(num));
        }
        else if (token.length() == 1 && (token[0] == '+' || token[0] == '-' ||
                                         token[0] == '*' || token[0] == '/'))
        {
            if (_rpnStack.size() < 2)
                throw std::runtime_error("Error");

            float b = _rpnStack.top();
            _rpnStack.pop();
            float a = _rpnStack.top();
            _rpnStack.pop();

            switch (token[0])
            {
            case '+':
                _rpnStack.push(a + b);
                break;
            case '-':
                _rpnStack.push(a - b);
                break;
            case '*':
                _rpnStack.push(a * b);
                break;
            case '/':
                if (b == 0)
                    throw std::runtime_error("Error");
                _rpnStack.push(a / b);
                break;
            }
        }
        else
            throw std::runtime_error("Error");
    }
}

RPN::RPN(const RPN &other) : _rpnStack(other._rpnStack) {}

RPN::~RPN() {}

RPN &RPN::operator=(const RPN &other)
{
    if (this != &other)
        _rpnStack = other._rpnStack;
    return *this;
}

float RPN::calculateRPN()
{
    if (_rpnStack.size() != 1)
        throw std::runtime_error("Error");

    float result = _rpnStack.top();
    _rpnStack.pop();
    return result;
}