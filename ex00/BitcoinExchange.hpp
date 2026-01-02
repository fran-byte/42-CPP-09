/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 21:27:56 by frromero          #+#    #+#             */
/*   Updated: 2026/01/02 21:54:05 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

#define CSV_FILE "data.csv"

class BitcoinExchange
{
private:
    std::map<std::string, float> _bitCoinDatabase;
    bool parseCsv();
    bool parseInput(const std::string &strFile);

public:
    BitcoinExchange(void);
    BitcoinExchange(const std::string &csvFile);
    BitcoinExchange(BitcoinExchange const &copy);
    ~BitcoinExchange();
    BitcoinExchange &operator=(BitcoinExchange const &other);
    void tester();
};

#endif