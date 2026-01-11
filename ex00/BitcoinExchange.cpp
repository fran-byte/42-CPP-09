/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:58:43 by frromero          #+#    #+#             */
/*   Updated: 2026/01/11 17:36:53 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <exception>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void) {}

BitcoinExchange::BitcoinExchange(const std::string &csvFile)
{
    if (!_parseCsv(csvFile))
        throw std::runtime_error("Error: could not open source database.");
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &copy)
    : _bitCoinDatabase(copy._bitCoinDatabase) {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &other)
{
    if (this != &other)
        _bitCoinDatabase = other._bitCoinDatabase;
    return *this;
}

/* ********** PRIVATE Methods ************************************************** */

/* CSV */
bool BitcoinExchange::_parseCsv(const std::string &csvFile)
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
            return false;
        char *endPtr;
        float value = std::strtof(valueStr.c_str(), &endPtr);
        if (*endPtr != '\0') /*conversion failed*/
            return false;

        _bitCoinDatabase[date] = value; /*Save date and value*/
    }
    return !_bitCoinDatabase.empty();
}

/* DATE OK ? */
bool BitcoinExchange::_isValidDate(const std::string &date)
{
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    std::string yearStr = date.substr(0, 4);
    std::string monthStr = date.substr(5, 2);
    std::string dayStr = date.substr(8, 2);

    /*Verifying only digits*/
    for (size_t i = 0; i < yearStr.length(); ++i)
        if (!std::isdigit(yearStr[i]))
            return false;
    for (size_t i = 0; i < monthStr.length(); ++i)
        if (!std::isdigit(monthStr[i]))
            return false;
    for (size_t i = 0; i < dayStr.length(); ++i)
        if (!std::isdigit(dayStr[i]))
            return false;

    /*to int*/
    int year = std::atoi(yearStr.c_str());
    int month = std::atoi(monthStr.c_str());
    int day = std::atoi(dayStr.c_str());

    if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;

    if (month == 2)
    {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > 29 || (!isLeap && day > 28))
            return false;
    }
    return true;
}

/* Header OK ?*/
bool BitcoinExchange::_isValidHeader(const std::string &line)
{
    return line == "date | value";
}

/* PARSE input.txt */
std::pair<std::string, float> BitcoinExchange::_parseInputLine(const std::string &line)
{
    size_t pipePos = line.find('|');
    if (pipePos == std::string::npos) /*No PIPE*/
        throw std::runtime_error("Error: bad input => " + line);

    /*Split date and value*/
    std::string date = line.substr(0, pipePos);
    std::string valueStr = line.substr(pipePos + 1);

    /*trim spaces (Date)*/
    size_t start = date.find_first_not_of(" \t");
    size_t end = date.find_last_not_of(" \t");
    if (start == std::string::npos)
        throw std::runtime_error("Error: bad input => " + line);
    date = date.substr(start, end - start + 1);

    /*trim spaces (Value)*/
    start = valueStr.find_first_not_of(" \t");
    end = valueStr.find_last_not_of(" \t");
    if (start == std::string::npos)
        throw std::runtime_error("Error: bad input => " + line);
    valueStr = valueStr.substr(start, end - start + 1);

    /*Valid Date (input.txt)*/
    if (!_isValidDate(date))
        throw std::runtime_error("Error: bad input => " + line);

    /*stringValue to Float*/
    char *endPtr;
    float value = std::strtof(valueStr.c_str(), &endPtr);
    if (*endPtr != '\0')
        throw std::runtime_error("Error: bad input => " + line);
    if (value < 0)
        throw std::runtime_error("Error: not a positive number.");
    if (value > 1000)
        throw std::runtime_error("Error: too large a number.");

    return std::make_pair(date, value); /*Return both*/
}

/* ********** PUBLIC Methods ************************************************** */

/* GET RATE */
float BitcoinExchange::getRate(const std::string &date) const
{
    if (_bitCoinDatabase.empty())
        throw std::runtime_error("Error: Database not loaded");

    /*Try exact date match first*/
    std::map<std::string, float>::const_iterator it = _bitCoinDatabase.find(date);
    if (it != _bitCoinDatabase.end())
        return it->second;
    /*No exact match, find closest date*/
    it = _bitCoinDatabase.lower_bound(date);

    if (it == _bitCoinDatabase.begin()) /*No previous date available*/
        throw std::runtime_error("Error: No data available for date: " + date);

    /*Use previous date (lower bound - 1)*/
    --it;
    return it->second;
}

/* PROCESS INPUT FILE input.txt */
void BitcoinExchange::processInputFile(const std::string &inputFileName)
{
    std::ifstream inputFile(inputFileName.c_str());
    if (!inputFile.is_open())
        throw std::runtime_error("Error: could not open file.");

    std::string line;

    while (std::getline(inputFile, line) && line.empty())
    { /* Void lines  */
    }

    if (!_isValidHeader(line))
        throw std::runtime_error("Error: invalid file format.");

    while (std::getline(inputFile, line))
    {
        if (line.empty())
            continue;
        try
        {
            std::pair<std::string, float> dateAndValueParsed = _parseInputLine(line);
            float rate = getRate(dateAndValueParsed.first);
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