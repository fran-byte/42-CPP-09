/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:58:43 by frromero          #+#    #+#             */
/*   Updated: 2026/01/02 20:32:15 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <exception>
#include <sstream>

BitcoinExchange::BitcoinExchange(void)
{
    // Creates empty BitcoinExchange object
    // Use BitcoinExchange("data.csv") for proper initialization
}

BitcoinExchange::BitcoinExchange(const std::string &strFile)
{

    if (parseCsv() == false)
    {
        throw std::runtime_error("Error: Invalid CSV file format");
    }

    if (parseInput() == false)
    {
        throw std::runtime_error("Error: Invalid Input file format");
    }

    std::ifstream file(strFile.c_str());
    std::ifstream csvFile(CSV_FILE);

    if (!file.is_open())
        throw std::runtime_error("Error: could not open file.");
    if (!csvFile.is_open())
        throw std::runtime_error("Error: could not open CSV file.");

    std::string line;
    std::getline(csvFile, line); // Skip first line

    while (std::getline(csvFile, line))
    {
        std::string date;
        float value = 0.0f;

        std::string::size_type pos = line.find(',');

        date = line.substr(0, pos);
        std::string valueStr = line.substr(pos + 1);
        std::stringstream ss(valueStr);
        ss >> value;

        _bitCoinDatabase[date] = value;
    }
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &copy) : _bitCoinDatabase(copy._bitCoinDatabase)
{
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &other)
{
    if (this != &other)
        _bitCoinDatabase = other._bitCoinDatabase;

    return *this;
}

void BitcoinExchange::tester()
{
    std::map<std::string, float>::const_iterator it;
    for (it = _bitCoinDatabase.begin(); it != _bitCoinDatabase.end(); ++it)
    {
        std::cout << it->first << " -> " << it->second << std::endl;
    }
}
