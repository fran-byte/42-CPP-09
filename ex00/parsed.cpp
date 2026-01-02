/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsed.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 20:30:29 by frromero          #+#    #+#             */
/*   Updated: 2026/01/02 20:48:27 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <exception>

bool parseCsv()
{
    std::ifstream csvFile(CSV_FILE);
    if (!csvFile.is_open())
        throw std::runtime_error("Error: could not open CSV file.");

    return true;
}

bool parseInput(std::string strFile)
{
    std::ifstream file(strFile.c_str());
    if (!file.is_open())
        throw std::runtime_error("Error: could not open file.");

    return true;
}
