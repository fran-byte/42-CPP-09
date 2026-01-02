/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 19:17:33 by frromero          #+#    #+#             */
/*   Updated: 2026/01/03 00:41:39 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    try
    {
        BitcoinExchange exchange("data.csv"); /*Load data.csv*/

        std::ifstream inputFile(argv[1]);
        if (!inputFile.is_open())
        {
            std::cerr << "Error: could not open file." << std::endl;
            return 1;
        }

        std::string line;

        if (!std::getline(inputFile, line) || line != "date | value")
        {
            std::cerr << "Error: invalid file format. Missing header." << std::endl;
            return 1;
        }

        while (std::getline(inputFile, line))
        {
            if (line.empty())
                continue;

            try
            {
                std::pair<std::string, float> transaction = parseInputLine(line);
                float rate = exchange.getRate(transaction.first);
                float result = transaction.second * rate;

                std::cout << transaction.first << " => "
                          << transaction.second << " = "
                          << result << std::endl;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}