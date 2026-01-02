/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 21:27:56 by frromero          #+#    #+#             */
/*   Updated: 2026/01/03 00:16:50 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <utility>
#include <stdexcept>

class BitcoinExchange
{
private:
    std::map<std::string, float> _bitCoinDatabase;
    bool parseCsv(const std::string &csvFile);

public:
    BitcoinExchange(void);
    BitcoinExchange(const std::string &csvFile);
    BitcoinExchange(BitcoinExchange const &copy);
    ~BitcoinExchange();
    BitcoinExchange &operator=(BitcoinExchange const &other);
    float getRate(const std::string &date) const;
};

bool isValidDate(const std::string &date);
std::pair<std::string, float> parseInputLine(const std::string &line);

#endif