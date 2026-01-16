#include "PmergeMe.hpp"
#include <vector>
#include <utility>
#include <iostream>
#include <ctime>
#include <algorithm>

/* THIS IS THE FUCKING CRAZY FORD-JOHNSON ALGORITHM for Vector Container  :-) */

/* ***********************************************************************
 * BinarySearch determines THE POSITION for vector
 * Finds the insertion index for `value` inside a sorted vector
 * returns the first position where value fits
 * ***********************************************************************/

size_t PmergeMe::_binarySearchVector(const std::vector<int> &arr, int value)
{
    return std::lower_bound(arr.begin(), arr.end(), value) - arr.begin();
}

/* ***********************************************************************
 * Insertion order (Jacobsthal sequence )for Vector
 * Generates the insertion order using the Jacobsthal sequence
 * This order minimizes the number of comparisons when inserting
 * pending elements during the Ford–Johnson algorithm
 * ***********************************************************************/
static std::vector<size_t> getInsertionOrderVector(size_t pendSize)
{
    std::vector<size_t> insertionOrder;

    if (pendSize == 0)
        return insertionOrder;

    insertionOrder.push_back(0);

    if (pendSize == 1)
        return insertionOrder;

    std::vector<size_t> jacob;
    jacob.push_back(0);
    jacob.push_back(1);

    size_t i = 2;
    while (true)
    {
        size_t next = jacob[i - 1] + 2 * jacob[i - 2];
        jacob.push_back(next);

        if (jacob.back() >= pendSize)
            break;
        i++;
    }

    size_t lastInserted = 0;

    for (size_t j = 2; j < jacob.size(); j++)
    {
        size_t current = jacob[j];
        if (current > pendSize)
            current = pendSize;

        for (size_t k = current; k > lastInserted; k--)
        {
            size_t idx = k - 1;
            if (idx < pendSize && idx > 0)
                insertionOrder.push_back(idx);
        }
        lastInserted = current;

        if (current >= pendSize)
            break;
    }
    return insertionOrder;
}

/* ***********************************************************************
 * Ford–Johnson sort for std::vector
 *  1) Form pairs and sort each pair internally
 *  2) Extract larger elements and sort them recursively
 *  3) Insert the smaller elements back into the main using Jacobsthal order
 * ***********************************************************************/
void PmergeMe::_fordJohnsonSortVector(std::vector<int> &arr)
{
    if (arr.size() <= 1)
        return;

    /*Handle odd element */
    bool hasOdd = (arr.size() % 2 == 1);
    int oddElement = -1;

    if (hasOdd)
    {
        oddElement = arr.back();
        arr.pop_back();
    }

    /*Create pairs using std::pair (utility, not container)*/
    std::vector<std::pair<int, int>> pairs;
    for (size_t i = 0; i < arr.size(); i += 2)
    {
        if (arr[i] > arr[i + 1])
            pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
        else
            pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
    }

    /*Extract larger elements */
    std::vector<int> larger;
    for (size_t i = 0; i < pairs.size(); i++)
        larger.push_back(pairs[i].first);

    /* Recursively sort larger elements */
    if (larger.size() > 1)
        _fordJohnsonSortVector(larger);

    /* Reconstruct smaller elements */
    std::vector<int> smaller(larger.size(), -1);
    std::vector<bool> used(pairs.size(), false);

    for (size_t i = 0; i < larger.size(); i++)
    {
        for (size_t j = 0; j < pairs.size(); j++)
        { /*if pair hasn't been used AND its 1st element matches larger[i]*/
            if (!used[j] && pairs[j].first == larger[i])
            {
                smaller[i] = pairs[j].second;
                used[j] = true;
                break;
            }
        }
    }

    /* Build main chain */
    std::vector<int> mainChain;
    if (!smaller.empty() && smaller[0] != -1)
        mainChain.push_back(smaller[0]);

    for (size_t i = 0; i < larger.size(); i++)
        mainChain.push_back(larger[i]);

    /* Insert remaining smaller elements using Jacobsthal order */
    {
        std::vector<int> remaining;
        for (size_t i = 1; i < smaller.size(); i++)
            if (smaller[i] != -1)
                remaining.push_back(smaller[i]);

        if (!remaining.empty())
        {
            std::vector<size_t> insertionOrder = getInsertionOrderVector(remaining.size());

            for (size_t i = 0; i < insertionOrder.size(); i++)
            {
                size_t idx = insertionOrder[i];
                if (idx < remaining.size())
                {
                    int value = remaining[idx];
                    size_t pos = _binarySearchVector(mainChain, value);
                    mainChain.insert(mainChain.begin() + pos, value);
                }
            }
        }
    }

    /* Insert odd element if present */
    if (hasOdd)
    {
        size_t pos = _binarySearchVector(mainChain, oddElement);
        mainChain.insert(mainChain.begin() + pos, oddElement);
    }

    arr = mainChain;
}

/* ***********************************************************************
 * Public method to sort vector
 * ***********************************************************************/
void PmergeMe::fJVector(void)
{
    std::cout << "Before: ";
    for (size_t i = 0; i < _vec.size(); i++)
        std::cout << _vec[i] << " ";
    std::cout << std::endl;

    clock_t start = clock();
    std::vector<int> sorted = _vec;
    _fordJohnsonSortVector(sorted);
    _vec = sorted;
    clock_t end = clock();

    double microseconds = (end - start) * 1000000.0 / CLOCKS_PER_SEC;

    std::cout << "After: ";
    for (size_t i = 0; i < _vec.size(); i++)
        std::cout << _vec[i] << " ";
    std::cout << std::endl;

    std::cout << "Time to process a range of " << _vec.size()
              << " elements with std::vector : " << microseconds << " us" << std::endl;
}
