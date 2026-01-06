/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:19:57 by frromero          #+#    #+#             */
/*   Updated: 2026/01/06 12:00:03 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <stdexcept>
#include <climits>
#include <cstdlib>
#include <cctype>
#include <cerrno>
#include <iostream>

bool PmergeMe::isValidInt(const std::vector<std::string> &argvString)
{
    for (size_t i = 0; i < argvString.size(); i++)
    {
        const std::string &str = argvString[i];

        if (str.empty()) /*EMPTY*/
            return false;

        if (str[0] == '0') /*Zero is not a positive integer*/
            return false;

        for (size_t j = 0; j < str.size(); j++)
        {
            if (!std::isdigit(static_cast<unsigned char>(str[j]))) /* Digit*/
                return false;
        }

        errno = 0;
        char *endPtr;
        long num = std::strtol(str.c_str(), &endPtr, 10);

        if (*endPtr != '\0')
            return false;

        if (errno == ERANGE || num > INT_MAX || num <= 0) /*INT_MAX*/
            return false;
    }
    return true;
}

PmergeMe::PmergeMe(void) {}
PmergeMe::PmergeMe(std::vector<std::string> const &argvString)
{
    if (!isValidInt(argvString))
    {
        throw std::runtime_error("Error: Invalid integer argument.");
    }
    for (size_t i = 0; i < argvString.size(); i++)
        _vec.push_back(std::atoi(argvString[i].c_str())); /*fill container*/

    for (size_t i = 0; i < argvString.size(); i++)
        _deq.push_back(std::atoi(argvString[i].c_str())); /*fill container*/

    /**************************************************DEBUG*/
    std::cout << "vector<int> ";
    for (size_t i = 0; i < _vec.size(); i++)
        std::cout << _vec[i];
    std::cout << std::endl;
    std::cout << "deque<int>  ";
    for (size_t i = 0; i < _deq.size(); i++)
        std::cout << _deq[i];
    std::cout << std::endl;
    /* **************************************************   */
}

PmergeMe::~PmergeMe(void) {}

PmergeMe::PmergeMe(PmergeMe const &copy) : _vec(copy._vec), _deq(copy._deq) {}

PmergeMe &PmergeMe::operator=(PmergeMe const &other)
{
    if (this != &other)
    {
        _vec = other._vec;
        _deq = other._deq;
    }
    return *this;
}

void PmergeMe::fJVector(void)
{
}
void PmergeMe::fJDeque(void)
{
}
