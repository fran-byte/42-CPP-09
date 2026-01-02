/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 19:17:33 by frromero          #+#    #+#             */
/*   Updated: 2026/01/02 20:49:25 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << std::endl
                  << "Error: Could not open file." << std::endl
                  << std::endl;
        return 1;
    }

    try
    {
        BitcoinExchange data(argv[1]);
        data.tester();
    }
    catch (const std::exception &e)
    {
        std::cout << std::endl
                  << e.what() << std::endl
                  << std::endl;
    }
    return 0;
}