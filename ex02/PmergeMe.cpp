/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:19:57 by frromero          #+#    #+#             */
/*   Updated: 2026/01/08 21:49:46 by frromero         ###   ########.fr       */
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
#include <algorithm>

// generate algorithm
static std::vector<size_t> generateAlgorithm(size_t n)
{
    std::vector<size_t> sequence;
    if (n == 0)
        return sequence;

    // 1st Jacobsthal numbers
    sequence.push_back(1); // J1

    size_t j_prev = 0; // J0
    size_t j_curr = 1; // J1

    while (sequence.size() < n)
    {
        size_t j_next = j_curr + 2 * j_prev;
        sequence.push_back(j_next);
        j_prev = j_curr;
        j_curr = j_next;
    }
    return sequence;
}

// get insertion order
static std::vector<size_t> getInsertionOrder(size_t pendSize)
{
    std::vector<size_t> order;

    if (pendSize == 0)
        return order;

    // start by inserting the 1st element
    order.push_back(0);

    if (pendSize == 1)
        return order;

    // Generate Algorithm
    std::vector<size_t> jacobsthal = generateAlgorithm(pendSize);

    // Use Algorithm sequence to determine insertion order
    size_t lastInserted = 0;
    for (size_t i = 1; i < jacobsthal.size(); i++)
    {
        size_t current = jacobsthal[i];
        if (current > pendSize)
            current = pendSize;

        // Insert in descending order within the group
        for (size_t j = current; j > lastInserted; j--)
        {
            if (j - 1 < pendSize) // Adjust for 0-based indexing
                order.push_back(j - 1);
        }
        lastInserted = current;
    }

    return order;
}

// validation
bool PmergeMe::isValidInt(const std::vector<std::string> &argvString)
{
    for (size_t i = 0; i < argvString.size(); i++)
    {
        const std::string &str = argvString[i];

        if (str.empty())
            return false;

        if (str[0] == '0')
            return false;

        for (size_t j = 0; j < str.size(); j++) // all characters are digits
        {
            if (!std::isdigit(static_cast<unsigned char>(str[j])))
                return false;
        }

        // Convert and check range
        errno = 0;
        char *endPtr;
        long num = std::strtol(str.c_str(), &endPtr, 10);

        if (*endPtr != '\0') // Non digit characters found
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

// Binary search for vector
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

// Ford-Johnson algorithm for vector
void PmergeMe::_fjRecursVector(std::vector<int> &arr)
{
    if (arr.size() <= 1)
        return;

    bool hasLastElement = (arr.size() % 2 == 1); // odd sized array (single)
    int lastValue = -1;
    size_t sizeForPairs = arr.size();

    if (hasLastElement)
    {
        lastValue = arr.back();
        sizeForPairs = arr.size() - 1;
    }
    else
        sizeForPairs = arr.size();

    // Form pairs and store them in arrays
    std::vector<int> largerElements;  // a elements (larger)
    std::vector<int> smallerElements; // b elements (smaller)

    for (size_t i = 0; i < sizeForPairs; i += 2)
    {
        if (arr[i] > arr[i + 1])
        {
            largerElements.push_back(arr[i]);      // a
            smallerElements.push_back(arr[i + 1]); // b
        }
        else
        {
            largerElements.push_back(arr[i + 1]); // a
            smallerElements.push_back(arr[i]);    // b
        }
    }

    // RECURSIVE - sort larger elements
    if (largerElements.size() > 1)
        _fjRecursVector(largerElements);

    // Build main chain starting with b1
    std::vector<int> mainChain;
    if (!smallerElements.empty())
        mainChain.push_back(smallerElements[0]); // b1 (1st smaller element)

    // Insert sorted larger elements
    for (size_t i = 0; i < largerElements.size(); i++)
        mainChain.push_back(largerElements[i]);

    // Insert remaining smaller elements
    if (smallerElements.size() > 1)
    {
        std::vector<int> remainingSmallers(smallerElements.begin() + 1, smallerElements.end());

        // Get insertion order
        std::vector<size_t> insertionOrder = getInsertionOrder(remainingSmallers.size());

        for (size_t i = 0; i < insertionOrder.size(); i++)
        {
            size_t idx = insertionOrder[i];
            if (idx < remainingSmallers.size())
            {
                int value = remainingSmallers[idx];
                size_t pos = _binarySearchVector(mainChain, value);
                mainChain.insert(mainChain.begin() + pos, value);
            }
        }
    }
    if (hasLastElement) // Insert hasLastElement if exists
    {
        size_t pos = _binarySearchVector(mainChain, lastValue);
        mainChain.insert(mainChain.begin() + pos, lastValue);
    }

    arr = mainChain; // Update arr
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

void PmergeMe::_fjRecursDeque(std::deque<int> &arr)
{
    if (arr.size() <= 1)
        return;
    bool hasLastElement = (arr.size() % 2 == 1);
    int lastValue = -1;
    size_t sizeForPairs = arr.size();
    if (hasLastElement)
    {
        lastValue = arr.back();
        sizeForPairs = arr.size() - 1;
    }
    else
        sizeForPairs = arr.size();
    std::deque<int> largerElements;
    std::deque<int> smallerElements;
    for (size_t i = 0; i < sizeForPairs; i += 2)
    {
        if (arr[i] > arr[i + 1])
        {
            largerElements.push_back(arr[i]);
            smallerElements.push_back(arr[i + 1]);
        }
        else
        {
            largerElements.push_back(arr[i + 1]);
            smallerElements.push_back(arr[i]);
        }
    }
    if (largerElements.size() > 1)
        _fjRecursDeque(largerElements);
    std::deque<int> mainChain;
    if (!smallerElements.empty())
        mainChain.push_back(smallerElements[0]); // b₁
    for (size_t i = 0; i < largerElements.size(); i++)
        mainChain.push_back(largerElements[i]);
    if (smallerElements.size() > 1)
    {
        std::deque<int> remainingSmallers(smallerElements.begin() + 1, smallerElements.end());
        std::vector<size_t> insertionOrder = getInsertionOrder(remainingSmallers.size());
        for (size_t i = 0; i < insertionOrder.size(); i++)
        {
            size_t idx = insertionOrder[i];
            if (idx < remainingSmallers.size())
            {
                int value = remainingSmallers[idx];
                size_t pos = _binarySearchDeque(mainChain, value);
                mainChain.insert(mainChain.begin() + pos, value);
            }
        }
    }
    if (hasLastElement)
    {
        size_t pos = _binarySearchDeque(mainChain, lastValue);
        mainChain.insert(mainChain.begin() + pos, lastValue);
    }
    arr = mainChain;
}

void PmergeMe::fJVector(void)
{
    std::cout << "Before : ";
    for (size_t i = 0; i < _vec.size(); i++)
        std::cout << _vec[i] << " ";
    std::cout << std::endl;

    clock_t start = clock();
    std::vector<int> sorted = _vec;
    _fjRecursVector(sorted);
    _vec = sorted;
    clock_t end = clock();
    double microseconds = (end - start) * 1000000.0 / CLOCKS_PER_SEC;

    std::cout << "After  : ";
    for (size_t i = 0; i < _vec.size(); i++)
        std::cout << _vec[i] << " ";
    std::cout << std::endl;

    std::cout << "Time to process a range of " << _vec.size()
              << " elements with std::vector : " << microseconds << " us" << std::endl;
}

void PmergeMe::fJDeque(void)
{
    clock_t start = clock();
    std::deque<int> sorted = _deq;
    _fjRecursDeque(sorted);
    _deq = sorted;
    clock_t end = clock();
    double microseconds = (end - start) * 1000000.0 / CLOCKS_PER_SEC;

    std::cout << "Time to process a range of " << _deq.size()
              << " elements with std::deque  : " << microseconds << " us" << std::endl;
}

/*

Ford Johnson (Merge-Insertion Sort): _vec

    Form pairs of elements

    Compare each pair and separate into larger (a) and smaller (b) elements

    Sort only the larger elements (a) recursively

    Build chain: b1 + sorted a

    Insert remaining b using special order (Jacobsthal) + binary search

*/