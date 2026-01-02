/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 19:17:33 by frromero          #+#    #+#             */
/*   Updated: 2026/01/02 19:35:26 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << std::endl
                  << "Error: could not open file." << std::endl
                  << std::endl;
        return 1;
    }

    try
    {
        BitcoinExchange a(argv[1]);
        a.tester();
    }
    catch (const std::exception &e)
    {
        std::cout << std::endl
                  << e.what() << std::endl
                  << std::endl;
    }
    return 0;
}