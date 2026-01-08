/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:19:57 by frromero          #+#    #+#             */
/*   Updated: 2026/01/07 18:32:53 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <stdexcept>
#include <climits>
#include <cstdlib>
#include <cctype>
#include <cerrno>
#include <iostream>
#include <ctime>

bool PmergeMe::isValidInt(const std::vector<std::string> &argvString)
{
    for (size_t i = 0; i < argvString.size(); i++)
    {
        const std::string &str = argvString[i];

        if (str.empty())
            return false;

        if (str[0] == '0')
            return false;

        for (size_t j = 0; j < str.size(); j++)
        {
            if (!std::isdigit(static_cast<unsigned char>(str[j])))
                return false;
        }

        errno = 0;
        char *endPtr;
        long num = std::strtol(str.c_str(), &endPtr, 10);

        if (*endPtr != '\0')
            return false;

        if (errno == ERANGE || num > INT_MAX || num <= 0)
            return false;
    }
    return true;
}

PmergeMe::PmergeMe(void) {}

PmergeMe::PmergeMe(std::vector<std::string> const &argvString)
{
    if (!isValidInt(argvString))
    {
        throw std::runtime_error("Error");
    }
    for (size_t i = 0; i < argvString.size(); i++)
        _vec.push_back(std::atoi(argvString[i].c_str()));

    for (size_t i = 0; i < argvString.size(); i++)
        _deq.push_back(std::atoi(argvString[i].c_str()));
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

// Binary search helper
size_t PmergeMe::_binarySearchVector(const std::vector<int> &arr, int value)
{
    size_t left = 0;
    size_t right = arr.size();

    while (left < right)
    {
        size_t mid = left + (right - left) / 2;
        if (arr[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

// Ford-Johnson recursive (vector)
void PmergeMe::_fordJohnsonRecursiveVector(std::vector<int> &arr)
{
    if (arr.size() <= 1)
        return;

    bool sizeIsOdd = (arr.size() % 2 == 1);
    int lastElemWithoutPair = sizeIsOdd ? arr.back() : -1;

    // Pairwise comparison and swap
    for (size_t i = 0; i < arr.size() - sizeIsOdd; i += 2)
    {
        if (arr[i] > arr[i + 1])
            std::swap(arr[i], arr[i + 1]);
    }

    // Create main chain & pending elem
    std::vector<int> mainChain;
    std::vector<int> pend;

    mainChain.push_back(arr[0]); // 1º element (b1)
    for (size_t i = 1; i < arr.size() - sizeIsOdd; i += 2)
        mainChain.push_back(arr[i]); // a elements

    for (size_t i = 2; i < arr.size() - sizeIsOdd; i += 2)
        pend.push_back(arr[i]); // Remaining b elements

    // Recursively sort (a elements (main)
    if (mainChain.size() > 2)
    {
        std::vector<int> aElements;
        for (size_t i = 1; i < mainChain.size(); i++)
            aElements.push_back(mainChain[i]);

        _fordJohnsonRecursiveVector(aElements);

        for (size_t i = 0; i < aElements.size(); i++)
            mainChain[i + 1] = aElements[i];
    }

    // Insert pending elemen (binary search)
    for (size_t i = 0; i < pend.size(); i++)
    {
        size_t pos = _binarySearchVector(mainChain, pend[i]);
        mainChain.insert(mainChain.begin() + pos, pend[i]);
    }

    // (if exists) Insert unpaired element (binary search)
    if (sizeIsOdd)
    {
        size_t pos = _binarySearchVector(mainChain, lastElemWithoutPair);
        mainChain.insert(mainChain.begin() + pos, lastElemWithoutPair);
    }

    // Update original arr
    arr = mainChain;
}

// Binary search (deque)
size_t PmergeMe::_binarySearchDeque(const std::deque<int> &arr, int value)
{
    size_t left = 0;
    size_t right = arr.size();

    while (left < right)
    {
        size_t mid = left + (right - left) / 2;
        if (arr[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

// Ford-Johnson recursive (deque)
void PmergeMe::_fordJohnsonRecursiveDeque(std::deque<int> &arr)
{
    if (arr.size() <= 1)
        return;

    bool sizeIsOdd = (arr.size() % 2 == 1);
    int lastElemWithoutPair = sizeIsOdd ? arr.back() : -1;

    for (size_t i = 0; i < arr.size() - sizeIsOdd; i += 2)
    {
        if (arr[i] > arr[i + 1])
            std::swap(arr[i], arr[i + 1]);
    }

    std::deque<int> mainChain;
    std::deque<int> pend;

    mainChain.push_back(arr[0]);
    for (size_t i = 1; i < arr.size() - sizeIsOdd; i += 2)
        mainChain.push_back(arr[i]);

    for (size_t i = 2; i < arr.size() - sizeIsOdd; i += 2)
        pend.push_back(arr[i]);

    if (mainChain.size() > 2)
    {
        std::deque<int> aElements;
        for (size_t i = 1; i < mainChain.size(); i++)
            aElements.push_back(mainChain[i]);

        _fordJohnsonRecursiveDeque(aElements);

        for (size_t i = 0; i < aElements.size(); i++)
            mainChain[i + 1] = aElements[i];
    }

    for (size_t i = 0; i < pend.size(); i++)
    {
        size_t pos = _binarySearchDeque(mainChain, pend[i]);
        mainChain.insert(mainChain.begin() + pos, pend[i]);
    }

    if (sizeIsOdd)
    {
        size_t pos = _binarySearchDeque(mainChain, lastElemWithoutPair);
        mainChain.insert(mainChain.begin() + pos, lastElemWithoutPair);
    }

    arr = mainChain;
}

void PmergeMe::fJVector(void)
{
    std::vector<int> sorted = _vec;
    _fordJohnsonRecursiveVector(sorted);
    _vec = sorted;

    // Debug output
    std::cout << "Sorted vector: ";
    for (size_t i = 0; i < _vec.size(); i++)
        std::cout << _vec[i] << " ";
    std::cout << std::endl;
}

void PmergeMe::fJDeque(void)
{
    std::timne_t timeDeque =
    std::deque<int> sorted = _deq;
    _fordJohnsonRecursiveDeque(sorted);
    _deq = sorted;

    // Debug output
    std::cout << "Sorted deque: ";
    for (size_t i = 0; i < _deq.size(); i++)
        std::cout << _deq[i] << " ";
    std::cout << std::endl;
}

std::time_t PmergeMe::myTime(void)
{
    currencyTime = std::
    return 
}