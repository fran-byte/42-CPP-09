/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:58:35 by frromero          #+#    #+#             */
/*   Updated: 2026/01/02 20:34:18 by frromero         ###   ########.fr       */
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

public:
    BitcoinExchange(void);
    BitcoinExchange(const std::string &csvFile);
    BitcoinExchange(BitcoinExchange const &copy);
    ~BitcoinExchange();
    BitcoinExchange &operator=(BitcoinExchange const &other);
    void tester();
};

bool parseCsv();
bool parseInput();

#endif