/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 19:17:33 by frromero          #+#    #+#             */
/*   Updated: 2026/01/03 11:33:34 by frromero         ###   ########.fr       */
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
        BitcoinExchange historicalPrices("data.csv");

        std::ifstream inputFile(argv[1]);
        if (!inputFile.is_open())
        {
            std::cerr << "Error: could not open file." << std::endl;
            return 1;
        }

        std::string line;

        while (std::getline(inputFile, line) && line.empty())
        {
            // Void lines
        }

        /*Testing header*/
        if (line != "date | value")
        {
            std::cerr << "Error: invalid file format. Missing or incorrect header." << std::endl;
            return 1;
        }

        while (std::getline(inputFile, line))
        {
            if (line.empty())
                continue;

            try
            {
                std::pair<std::string, float> dateAndValueParsed = parseInputLine(line);
                float rate = historicalPrices.getRate(dateAndValueParsed.first);
                float result = dateAndValueParsed.second * rate;

                std::cout << dateAndValueParsed.first << " => "
                          << dateAndValueParsed.second << " = "
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