/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 12:05:42 by frromero          #+#    #+#             */
/*   Updated: 2026/01/03 21:27:39 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP
#include <stack>
#include <string>

class RPN
{
private:
    std::stack<float> _rpnStack;

public:
    RPN(void);
    RPN(const std::string &str);
    RPN(RPN const &copy);
    ~RPN(void);
    RPN &operator=(RPN const &other);
    float calculateRPN();
};

#endif
