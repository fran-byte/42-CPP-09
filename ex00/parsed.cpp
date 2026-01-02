/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsed.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 00:17:45 by frromero          #+#    #+#             */
/*   Updated: 2026/01/03 00:17:46 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <cstdlib>
#include <cctype>
#include <stdexcept>

bool isValidDate(const std::string &date)
{
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    std::string yearStr = date.substr(0, 4);
    std::string monthStr = date.substr(5, 2);
    std::string dayStr = date.substr(8, 2);

    for (size_t i = 0; i < yearStr.length(); ++i)
        if (!std::isdigit(yearStr[i]))
            return false;
    for (size_t i = 0; i < monthStr.length(); ++i)
        if (!std::isdigit(monthStr[i]))
            return false;
    for (size_t i = 0; i < dayStr.length(); ++i)
        if (!std::isdigit(dayStr[i]))
            return false;

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

std::pair<std::string, float> parseInputLine(const std::string &line)
{
    size_t pipePos = line.find('|');
    if (pipePos == std::string::npos)
        throw std::runtime_error("Error: bad input => " + line);

    std::string date = line.substr(0, pipePos);
    std::string valueStr = line.substr(pipePos + 1);

    size_t start = date.find_first_not_of(" \t");
    size_t end = date.find_last_not_of(" \t");
    if (start == std::string::npos)
        throw std::runtime_error("Error: bad input => " + line);
    date = date.substr(start, end - start + 1);

    start = valueStr.find_first_not_of(" \t");
    end = valueStr.find_last_not_of(" \t");
    if (start == std::string::npos)
        throw std::runtime_error("Error: bad input => " + line);
    valueStr = valueStr.substr(start, end - start + 1);

    if (!isValidDate(date))
        throw std::runtime_error("Error: bad input => " + line);

    char *endPtr;
    float value = std::strtof(valueStr.c_str(), &endPtr);
    if (*endPtr != '\0')
        throw std::runtime_error("Error: bad input => " + line);

    if (value < 0)
        throw std::runtime_error("Error: not a positive number.");
    if (value > 1000)
        throw std::runtime_error("Error: too large a number.");

    return std::make_pair(date, value);
}