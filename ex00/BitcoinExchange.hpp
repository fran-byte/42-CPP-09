/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 21:27:56 by frromero          #+#    #+#             */
/*   Updated: 2026/01/14 18:08:44 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <utility>
#include <stdexcept>

#define CSV_FILE "data.csv"

class BitcoinExchange
{
private:
    /*  Exercise 00: Using std::map as containerm */
    std::map<std::string, float> _bitCoinDatabase;

    /* parsing functions */
    bool _parseCsv(const std::string &csvFile);
    static bool _isValidDate(const std::string &date);
    static bool _isValidHeader(const std::string &line);

    /* this is not a container */
    static std::pair<std::string, float> _parseInputLine(const std::string &line);
    /* https://en.cppreference.com/w/cpp/container.html */

    float _getRate(const std::string &date) const;

public:
    BitcoinExchange(void);
    BitcoinExchange(const std::string &csvFile);
    BitcoinExchange(BitcoinExchange const &copy);
    ~BitcoinExchange();
    BitcoinExchange &operator=(BitcoinExchange const &other);

    void processInputFile(const std::string &inputFileName);
};

#endif