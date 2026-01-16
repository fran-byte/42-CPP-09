#include "PmergeMe.hpp"
#include <stdexcept>
#include <cstdlib>
#include <iostream>
#include <climits>
#include <cctype>
#include <cerrno>

/* **********************************
 * Constructors and Destructor
 * **********************************/
PmergeMe::PmergeMe(void) {}

PmergeMe::PmergeMe(std::vector<std::string> const &argvString)
{
    if (!_isValidInt(argvString))
        throw std::runtime_error("Error");
    for (size_t i = 0; i < argvString.size(); i++)
    {
        _vec.push_back(std::atoi(argvString[i].c_str()));
        _deq.push_back(std::atoi(argvString[i].c_str()));
    }
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

/* ***********************************************************************
 * Validate positive integer (PARSER)
 * ***********************************************************************/
bool PmergeMe::_isValidInt(const std::vector<std::string> &argvString)
{
    if (argvString.size() > 5000)
    { /*SUBJECT: Your program must be able to handle at least 3000 different integers*/
        std::cerr << "Error: Too many numbers (maximum 5000 allowed)" << std::endl;
        return false;
    }
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