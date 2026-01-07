/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:19:57 by frromero          #+#    #+#             */
/*   Updated: 2026/01/06 17:13:03 by frromero         ###   ########.fr       */
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
/*
        a1 b1   a2 b2   a3 b3    c(single)  =>   sorter pairs
main =  b1 a1   a2  a3
pend =  b2 c
*/

void PmergeMe::fJVector(void)
{
    std::vector<int> _cpVect = _vec;
    bool isOdd = _cpVect.size() % 2;

    /* 1st sorting in pairs*/
    for (size_t i = 1; i + 1 < _cpVect.size(); i = i + 2)
    {
        int b = _cpVect[i - 1];
        int a = _cpVect[i];

        if (b > a)
            std::swap(_cpVect[i], _cpVect[i - 1]);
    }

    /*2nd create Main and Pending Elements*/
    std::vector<int> mainElem;
    std::vector<int> pendElem;

    mainElem.push_back(_cpVect[0]); /*b1*/
    for (size_t i = 1; i < _cpVect.size(); i = i + 2)
        mainElem.push_back(_cpVect[i]); /*a1,a2,a3...*/

    for (size_t i = 2; i + 1 < _cpVect.size(); i = i + 2)
        pendElem.push_back(_cpVect[i]); /* b2,b3,b4... */

    if (isOdd)
        pendElem.push_back(_cpVect.back());

    // DEBUG *************************************
    std::cout << "DEBUG - MAIN: ";
    for (size_t i = 0; i < mainElem.size(); i++)
        std::cout << mainElem[i] << " ";
    std::cout << "\nDEBUG - PEND: ";
    for (size_t i = 0; i < pendElem.size(); i++)
        std::cout << pendElem[i] << " ";
    std::cout << std::endl;
    // DEBUG *************************************
}
void PmergeMe::fJDeque(void)
{
    // size_t containerDeq = _deq.size() + 1;
}
