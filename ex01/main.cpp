/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:31:54 by frromero          #+#    #+#             */
/*   Updated: 2026/01/12 18:23:12 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Error: Invalid input" << std::endl
                  << "Try: ./RPN \"8 9 * 9 - 9 - 9 - 4 - 1 +\"" << std::endl;
        return 1;
    }
    try
    {
        RPN calculate(argv[1]);
        std::cout << calculate.calculateRPN() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

/*
#Valid Test
./RPN "1 2 +"
./RPN "3 4 *"
./RPN "9 5 -"
./RPN "8 2 /"
./RPN "2 3 + 4 *"
./RPN "1 2 + 3 +"
./RPN "7 2 - 3 *"
./RPN "6 2 / 1 +"
./RPN "3 3 + 2 * 4 -"
./RPN "5 1 2 + *"
./RPN "2 2 + 3 * 4 +"
./RPN "1 2 + 3 4 + *"

#Error Test
./RPN "12"
./RPN "+"
./RPN "1 +"
./RPN "3 4 + +"
./RPN "5 5 5 +"
./RPN "a b +"
./RPN "1 2 / 0 /"
./RPN "1 2 3"
./RPN "4 5 + *"
./RPN ""
./RPN " "

Results:
3
12
4
4
20
6
15
4
8
15
16
21
Error
Error
Error
Error
Error
Error
Error
Error
Error
Error
Error

*/