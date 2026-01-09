/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:19:57 by frromero          #+#    #+#             */
/*   Updated: 2026/01/09 19:18:55 by frromero         ###   ########.fr       */
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

/*

Ford Johnson (Merge-Insertion Sort):

    Form pairs of elements
    Compare each pair and separate into larger (a) and smaller (b) elements
    Sort only the larger elements (a) recursively
    Build chain: b1 + sorted a
    Insert remaining b using special order (Jacobsthal) + binary search

*/

PmergeMe::PmergeMe(void) {}

PmergeMe::PmergeMe(std::vector<std::string> const &argvString)
{
    if (!isValidInt(argvString))
        throw std::runtime_error("Error");
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
/*  END CONSTRUCTORS ******************************************************* */

/* [0]
 * @brief Checks that all input strings represent valid positive integers
 * @param argvString Vector containing the program arguments as strings
 * @return true if all arguments are valid, false otherwise
 */
bool PmergeMe::isValidInt(const std::vector<std::string> &argvString)
{
    for (size_t i = 0; i < argvString.size(); i++)
    {
        const std::string &str = argvString[i];

        if (str.empty())
            return false;

        if (str[0] == '0')
            return false;

        for (size_t j = 0; j < str.size(); j++) /* all characters are digits */
        {
            if (!std::isdigit(static_cast<unsigned char>(str[j])))
                return false;
        }

        /* convert and check range */
        errno = 0;
        char *endPtr;
        long num = std::strtol(str.c_str(), &endPtr, 10);

        if (*endPtr != '\0') /* Non digit characters found */
            return false;

        if (errno == ERANGE || num > INT_MAX || num <= 0)
            return false;
    }
    return true;
}

/* [5]
 * @brief Performs a binary search to find the insertion position for a value in a sorted vector.
 *
 * The function returns the index at which "value" should be inserted to maintain
 * the sorted order. This is used in the Ford–Johnson algorithm when inserting
 * pending elements efficiently
 *
 * @param arr Sorted vector of integers
 * @param value Value to search for
 * @return Index where "value" can be inserted
 */
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

/* [4]
 * @brief Generates the JACOBSTHAL SECUENCE used for insertion ordering
 *
 * Jacobsthal sequence:
 *   J(0) = 0, J(1) = 1
 *   J(n) = J(n - 1) + 2 * J(n - 2)
 *
 *  n	    J(n)
 * ---      --------
 *  0	    0  -> omit
 *  1	    1
 *  2	    1  + 2*0  = 1
 *  3	    1  + 2*1  = 3
 *  4	    3  + 2*1  = 5
 *  5	    5  + 2*3  = 11
 *  6	    11 + 2*5  = 21
 *  7	    21 + 2*11 = 43
 * ...      ...
 * @param n Number of elements to generate
 * @return Vector containing the first n Jacobsthal numbers
 */
static std::vector<size_t> generateJacobSequence(size_t n)
{
    std::vector<size_t> insertionSequence;
    if (n == 0)
        return insertionSequence;

    insertionSequence.push_back(1); // J(1)

    size_t j_prev = 0; // J(0) aux Variable
    size_t j_curr = 1; // J(1) aux Variable

    while (insertionSequence.size() < n)
    {
        size_t j_next = j_curr + 2 * j_prev; /*  J(n-1) + 2*J(n-2  */
        insertionSequence.push_back(j_next);
        j_prev = j_curr;
        j_curr = j_next;
    }
    return insertionSequence;
}

/* [3]
 * @brief Builds the insertion order for the Ford–Johnson algorithm
 *
 * Uses the JACOBSTHAL sequence to determine the optimal order for
 * inserting pending elements into the main chain
 * Indices beyond the number of pending elements are discarded
 *
 * @param pendSize Number of pending elements to insert
 * @return Vector containing the insertion indices in order
 */
static std::vector<size_t> getInsertionOrder(size_t pendSize)
{
    std::vector<size_t> insertionOrder;

    if (pendSize == 0)
        return insertionOrder;

    insertionOrder.push_back(0); /* start by inserting the 1st element */

    if (pendSize == 1)
        return insertionOrder;

    std::vector<size_t> jacobsthal = generateJacobSequence(pendSize); /* Jacobs sequence */

    size_t lastInserted = 0;
    for (size_t i = 1; i < jacobsthal.size(); i++)
    {
        size_t current = jacobsthal[i];
        if (current > pendSize)
            current = pendSize; /*discard out-of-range indices*/

        /* Insert in descending order within the group */
        for (size_t j = current; j > lastInserted; j--)
        {
            if (j - 1 < pendSize) /* Adjust for 0-based indexing */
                insertionOrder.push_back(j - 1);
        }
        lastInserted = current;
    }
    return insertionOrder;
}

/* [2]
 * @brief Sorts a vector using the Ford–Johnson (merge-insertion) algorithm
 *
 * The algorithm works by:
 * 2.1. Pairing elements and separating them into larger (a) and smaller (b) elements
 * 2.2. Recursively sorting the larger elements
 * 2.3. Building the main chain starting with the first smaller element
 * 2.4. Inserting remaining smaller elements in an order determined by the JACOBSTHAL sequence,
 *    using binary search for efficient placement
 * 2.5. If the array has an odd number of elements, the last element is inserted at the end
 *
 * @param arr Vector of integers to sort. The vector is modified in-place
 */
void PmergeMe::_fordJohnsonSortVector(std::vector<int> &arr)
{
    if (arr.size() <= 1)
        return; /*sorted*/

    bool hasLastElement = (arr.size() % 2 == 1); /* odd sized array (single) */
    int lastValue = -1;
    size_t sizeForPairs = arr.size();

    if (hasLastElement) /*Check if there is a last unpaired element*/
    {
        lastValue = arr.back();
        sizeForPairs = arr.size() - 1;
    }
    else
        sizeForPairs = arr.size();

    /* [2.1]Form PAIRS and STORE them in arrays */
    std::vector<int> largerElements;  /* a elements (larger) */
    std::vector<int> smallerElements; /* b elements (smaller) */

    for (size_t i = 0; i < sizeForPairs; i += 2)
    {
        if (arr[i] > arr[i + 1]) /* index 0 > index 1 ....*/
        {
            largerElements.push_back(arr[i]);      // STORE a
            smallerElements.push_back(arr[i + 1]); // STORE b
        }
        else
        {
            largerElements.push_back(arr[i + 1]); // STORE a
            smallerElements.push_back(arr[i]);    // STORE b
        }
    }

    if (largerElements.size() > 1)              /* BASE CASE*/
        _fordJohnsonSortVector(largerElements); /* [2.2]RECURSIVE (sort larger elements)*/

    /* [2.3]Build MAIN CHAIN starting with b1 (first smaller) */
    std::vector<int> mainChain;
    if (!smallerElements.empty())
        mainChain.push_back(smallerElements[0]);

    for (size_t i = 0; i < largerElements.size(); i++)
        mainChain.push_back(largerElements[i]); /* Insert sorted larger elements */

    if (smallerElements.size() > 1)
    {
        std::vector<int> remainingSmallers(smallerElements.begin() + 1, smallerElements.end()); /* [2.4]Insert remaining smaller elements */
        std::vector<size_t> insertionOrder = getInsertionOrder(remainingSmallers.size());       /* Get insertion order */

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
    if (hasLastElement) /* [2.5]Insert hasLastElement if exists */
    {
        size_t pos = _binarySearchVector(mainChain, lastValue);
        mainChain.insert(mainChain.begin() + pos, lastValue);
    }
    arr = mainChain; /* Update arr */
}

/* [1]
 * @brief Sorts the stored vector using the Ford–Johnson algorithm
 *
 * Copies _vec, sorts it, and updates _vec with the result
 */
void PmergeMe::fJVector(void)
{
    std::cout << "Before : ";
    for (size_t i = 0; i < _vec.size(); i++)
        std::cout << _vec[i] << " ";
    std::cout << std::endl;

    clock_t start = clock();
    std::vector<int> sorted = _vec;
    _fordJohnsonSortVector(sorted);
    clock_t end = clock();
    double microseconds = (end - start) * 1000000.0 / CLOCKS_PER_SEC;
    _vec = sorted;
    std::cout << "After  : ";
    for (size_t i = 0; i < _vec.size(); i++)
        std::cout << _vec[i] << " ";
    std::cout << std::endl;

    std::cout << "Time to process a range of " << _vec.size()
              << " elements with std::vector : " << microseconds << " us" << std::endl;
}

/* **************  SIMILAR CODE FOR "DEQUE" **********************************/

/* Binary search (deque) */
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

void PmergeMe::_fordJohnsonSortDeque(std::deque<int> &arr)
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
        _fordJohnsonSortDeque(largerElements);
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

void PmergeMe::fJDeque(void)
{
    clock_t start = clock();
    std::deque<int> sorted = _deq;
    _fordJohnsonSortDeque(sorted);
    clock_t end = clock();
    double microseconds = (end - start) * 1000000.0 / CLOCKS_PER_SEC;
    _deq = sorted;
    std::cout << "Time to process a range of " << _deq.size()
              << " elements with std::deque  : " << microseconds << " us" << std::endl;
}
