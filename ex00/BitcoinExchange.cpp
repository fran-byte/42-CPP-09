/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:58:43 by frromero          #+#    #+#             */
/*   Updated: 2026/01/03 00:17:07 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <exception>
#include <sstream>
#include <cstdlib>
#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
}

BitcoinExchange::BitcoinExchange(const std::string &csvFile)
{
    if (!parseCsv(csvFile))
    {
        throw std::runtime_error("Error: could not open database.");
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

bool BitcoinExchange::parseCsv(const std::string &csvFile)
{
    std::ifstream file(csvFile.c_str());
    if (!file.is_open())
        return false;

    std::string line;

    if (!std::getline(file, line) || line != "date,exchange_rate")
        return false;

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        size_t firstComma = line.find(',');
        if (firstComma == std::string::npos)
            return false;

        std::string date = line.substr(0, firstComma);
        std::string valueStr = line.substr(firstComma + 1);

        if (date.length() != 10 || date[4] != '-' || date[7] != '-')
            continue;

        char *endPtr;
        float value = std::strtof(valueStr.c_str(), &endPtr);
        if (*endPtr != '\0' && *endPtr != '\r')
            continue;

        _bitCoinDatabase[date] = value;
    }

    return !_bitCoinDatabase.empty();
}

float BitcoinExchange::getRate(const std::string &date) const
{
    if (_bitCoinDatabase.empty())
        throw std::runtime_error("Error: Database not loaded");

    std::map<std::string, float>::const_iterator it = _bitCoinDatabase.find(date);
    if (it != _bitCoinDatabase.end())
        return it->second;

    it = _bitCoinDatabase.lower_bound(date);
    if (it == _bitCoinDatabase.begin())
        throw std::runtime_error("Error: No data available for date: " + date);

    --it;
    return it->second;
}