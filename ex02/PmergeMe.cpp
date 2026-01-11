/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:19:57 by frromero          #+#    #+#             */
/*   Updated: 2026/01/11 19:07:14 by frromero         ###   ########.fr       */
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

static std::vector<size_t> getInsertionOrder(size_t pendSize)
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
            {
                insertionOrder.push_back(idx);
            }
        }

        lastInserted = current;

        if (current >= pendSize)
            break;
    }

    return insertionOrder;
}

// Estructura simple para mantener pares sin usar std::pair
struct SimplePair
{
    int first;
    int second;

    SimplePair() : first(0), second(0) {}
    SimplePair(int f, int s) : first(f), second(s) {}
};

void PmergeMe::_fordJohnsonSortVector(std::vector<int> &arr)
{
    if (arr.size() <= 1)
        return;

    // Caso base para arrays pequeños
    if (arr.size() <= 16)
    {
        for (size_t i = 1; i < arr.size(); i++)
        {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
        return;
    }

    // Manejar elemento impar
    bool hasOdd = (arr.size() % 2 == 1);
    int oddElement = -1;

    if (hasOdd)
    {
        oddElement = arr.back();
        arr.pop_back();
    }

    // Crear pares usando nuestro propio struct
    std::vector<SimplePair> pairs;
    for (size_t i = 0; i < arr.size(); i += 2)
    {
        if (arr[i] > arr[i + 1])
            pairs.push_back(SimplePair(arr[i], arr[i + 1]));
        else
            pairs.push_back(SimplePair(arr[i + 1], arr[i]));
    }

    // Extraer los mayores
    std::vector<int> larger;
    for (size_t i = 0; i < pairs.size(); i++)
        larger.push_back(pairs[i].first);

    // Ordenar recursivamente los mayores
    if (larger.size() > 1)
        _fordJohnsonSortVector(larger);

    // Reconstruir menores manteniendo correspondencia
    std::vector<int> smaller(pairs.size(), -1);
    std::vector<bool> used(pairs.size(), false);

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

    // Construir la cadena principal
    std::vector<int> mainChain;
    if (!smaller.empty() && smaller[0] != -1)
        mainChain.push_back(smaller[0]);

    for (size_t i = 0; i < larger.size(); i++)
        mainChain.push_back(larger[i]);

    // Insertar menores restantes usando orden Jacobsthal
    if (smaller.size() > 1)
    {
        // Crear vector de menores restantes (sin el primero)
        std::vector<int> remaining;
        for (size_t i = 1; i < smaller.size(); i++)
            if (smaller[i] != -1)
                remaining.push_back(smaller[i]);

        if (!remaining.empty())
        {
            std::vector<size_t> insertionOrder = getInsertionOrder(remaining.size());

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

    // Insertar elemento impar si existe
    if (hasOdd)
    {
        size_t pos = _binarySearchVector(mainChain, oddElement);
        mainChain.insert(mainChain.begin() + pos, oddElement);
    }

    arr = mainChain;
}

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

// Struct para deque también
struct SimplePairDeque
{
    int first;
    int second;

    SimplePairDeque() : first(0), second(0) {}
    SimplePairDeque(int f, int s) : first(f), second(s) {}
};

void PmergeMe::_fordJohnsonSortDeque(std::deque<int> &arr)
{
    if (arr.size() <= 1)
        return;

    // Caso base para arrays pequeños
    if (arr.size() <= 16)
    {
        for (size_t i = 1; i < arr.size(); i++)
        {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
        return;
    }

    bool hasOdd = (arr.size() % 2 == 1);
    int oddElement = -1;

    if (hasOdd)
    {
        oddElement = arr.back();
        arr.pop_back();
    }

    // Crear pares
    std::vector<SimplePairDeque> pairs;
    for (size_t i = 0; i < arr.size(); i += 2)
    {
        if (arr[i] > arr[i + 1])
            pairs.push_back(SimplePairDeque(arr[i], arr[i + 1]));
        else
            pairs.push_back(SimplePairDeque(arr[i + 1], arr[i]));
    }

    // Extraer mayores
    std::deque<int> larger;
    for (size_t i = 0; i < pairs.size(); i++)
        larger.push_back(pairs[i].first);

    // Ordenar recursivamente
    if (larger.size() > 1)
        _fordJohnsonSortDeque(larger);

    // Reconstruir menores
    std::deque<int> smaller(larger.size(), -1);
    std::vector<bool> used(pairs.size(), false);

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

    // Construir cadena principal
    std::deque<int> mainChain;
    if (!smaller.empty() && smaller[0] != -1)
        mainChain.push_back(smaller[0]);

    for (size_t i = 0; i < larger.size(); i++)
        mainChain.push_back(larger[i]);

    // Insertar menores restantes
    if (smaller.size() > 1)
    {
        std::vector<int> remaining;
        for (size_t i = 1; i < smaller.size(); i++)
            if (smaller[i] != -1)
                remaining.push_back(smaller[i]);

        if (!remaining.empty())
        {
            std::vector<size_t> insertionOrder = getInsertionOrder(remaining.size());

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

    // Insertar elemento impar
    if (hasOdd)
    {
        size_t pos = _binarySearchDeque(mainChain, oddElement);
        mainChain.insert(mainChain.begin() + pos, oddElement);
    }

    arr = mainChain;
}

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