/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 12:05:42 by frromero          #+#    #+#             */
/*   Updated: 2026/01/03 20:38:49 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP
#include <stack>
#include <string>

enum e_token
{
    INT,
    ADD,
    SUBT,
    MULT,
    DIV,
    ERROR
};

class RPN
{
private:
    std::stack<float> _rpnStack;
    e_token validateTokens(char c);

public:
    RPN(void);
    RPN(const std::string &str);
    RPN(RPN const &copy);
    ~RPN(void);
    RPN &operator=(RPN const &other);
    float calculateRPN();
};

#endif
