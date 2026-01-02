/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:58:43 by frromero          #+#    #+#             */
/*   Updated: 2026/01/02 22:01:48 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <exception>
#include <sstream>
#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
    // Creates empty BitcoinExchange object
    // Use BitcoinExchange("data.csv") for proper initialization
}

BitcoinExchange::BitcoinExchange(const std::string &strFile)
{
    if (!parseCsv())
    {
        throw std::runtime_error("Error: Invalid CSV file");
    }

    if (!parseInput(strFile))
    {
        throw std::runtime_error("Error: Invalid Input file");
    }
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &copy)
    : _bitCoinDatabase(copy._bitCoinDatabase)
{
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &other)
{
    if (this != &other)
        _bitCoinDatabase = other._bitCoinDatabase;
    return *this;
}

bool BitcoinExchange::parseCsv()
{
    std::ifstream csvFile(CSV_FILE);
    if (!csvFile.is_open())
        return false;

    std::string line;

    if (!std::getline(csvFile, line) || line != "date,exchange_rate") // Metadata CSV
        return false;

    while (std::getline(csvFile, line))
    {
        if (line.empty())
            continue;

        size_t firstComma = line.find(',');
        if (firstComma == std::string::npos)
            return false;
        if (line.find(',', firstComma + 1) != std::string::npos)
            return false;

        std::string date = line.substr(0, firstComma);
        std::string valueStr = line.substr(firstComma + 1);

        if (date.length() != 10 || date[4] != '-' || date[7] != '-')
            return false;

        std::stringstream ss(valueStr);
        float value;
        if (!(ss >> value))
            return false;

        _bitCoinDatabase[date] = value; // Add DATE & VALUE
    }

    return !_bitCoinDatabase.empty(); // is empty??
}

bool BitcoinExchange::parseInput(const std::string &strFile)
{
    std::ifstream inputFile(strFile.c_str());
    if (!inputFile.is_open())
        return false;

    std::string line;

    if (std::getline(inputFile, line))
    {
        if (line != "date | value")

            return false;
    }
    else
        return false; /*void file*/

    return true; // Input file OK
}

void BitcoinExchange::tester()
{
    std::map<std::string, float>::const_iterator it;
    for (it = _bitCoinDatabase.begin(); it != _bitCoinDatabase.end(); ++it)
    {
        std::cout << it->first << " -> " << it->second << std::endl;
    }
}