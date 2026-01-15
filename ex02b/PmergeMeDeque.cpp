#include "PmergeMe.hpp"
#include <deque>
#include <utility>
#include <iostream>
#include <ctime>
#include <algorithm>

/* ***********************************************************************
 * BinarySearch determines THE POSITION for deque
 * ***********************************************************************/
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

/* ***********************************************************************
 * Insertion order (Jacobsthal sequence) for Deque
 * ***********************************************************************/
static std::deque<size_t> getInsertionOrderDeque(size_t pendSize)
{
    std::deque<size_t> insertionOrder;

    if (pendSize == 0)
        return insertionOrder;

    insertionOrder.push_back(0);

    if (pendSize == 1)
        return insertionOrder;

    std::deque<size_t> jacob;
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
 * Ford–Johnson sort for std::deque
 * ***********************************************************************/
void PmergeMe::_fordJohnsonSortDeque(std::deque<int> &arr)
{
    if (arr.size() <= 1)
        return;

    bool hasOdd = (arr.size() % 2 == 1);
    int oddElement = -1;

    if (hasOdd)
    {
        oddElement = arr.back();
        arr.pop_back();
    }

    // Create pairs using std::pair (utility, not container)
    std::deque<std::pair<int, int> > pairs;
    for (size_t i = 0; i < arr.size(); i += 2)
    {
        if (arr[i] > arr[i + 1])
            pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
        else
            pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
    }

    // Extract larger elements
    std::deque<int> larger;
    for (size_t i = 0; i < pairs.size(); i++)
        larger.push_back(pairs[i].first);

    // Recursively sort larger elements
    if (larger.size() > 1)
        _fordJohnsonSortDeque(larger);

    // Reconstruct smaller elements
    std::deque<int> smaller(larger.size(), -1);
    std::deque<bool> used(pairs.size(), false);

    for (size_t i = 0; i < larger.size(); i++)
    {
        for (size_t j = 0; j < pairs.size(); j++)
        {
            if (!used[j] && pairs[j].first == larger[i])
            {
                smaller[i] = pairs[j].second;
                used[j] = true;
                break;
            }
        }
    }

    // Build main chain
    std::deque<int> mainChain;
    if (!smaller.empty() && smaller[0] != -1)
        mainChain.push_back(smaller[0]);

    for (size_t i = 0; i < larger.size(); i++)
        mainChain.push_back(larger[i]);

    // Insert remaining smaller elements using Jacobsthal order
    if (smaller.size() > 1)
    {
        std::deque<int> remaining;
        for (size_t i = 1; i < smaller.size(); i++)
            if (smaller[i] != -1)
                remaining.push_back(smaller[i]);

        if (!remaining.empty())
        {
            std::deque<size_t> insertionOrder = getInsertionOrderDeque(remaining.size());

            for (size_t i = 0; i < insertionOrder.size(); i++)
            {
                size_t idx = insertionOrder[i];
                if (idx < remaining.size())
                {
                    int value = remaining[idx];
                    size_t pos = _binarySearchDeque(mainChain, value);
                    mainChain.insert(mainChain.begin() + pos, value);
                }
            }
        }
    }

    // Insert odd element if present
    if (hasOdd)
    {
        size_t pos = _binarySearchDeque(mainChain, oddElement);
        mainChain.insert(mainChain.begin() + pos, oddElement);
    }

    arr = mainChain;
}

/* ***********************************************************************
 * Public method to sort deque
 * ***********************************************************************/
void PmergeMe::fJDeque(void)
{
    clock_t start = clock();
    std::deque<int> sorted = _deq;
    _fordJohnsonSortDeque(sorted);
    _deq = sorted;
    clock_t end = clock();

    double microseconds = (end - start) * 1000000.0 / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << _deq.size()
              << " elements with std::deque  : " << microseconds << " us" << std::endl;
}
