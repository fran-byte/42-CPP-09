#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>

class PmergeMe
{
private:
    std::vector<int> _vec;
    std::deque<int> _deq;

    bool _isValidInt(const std::vector<std::string> &argvString);

    // Declaraciones para vector
    size_t _binarySearchVector(const std::vector<int> &arr, int value);
    void _fordJohnsonSortVector(std::vector<int> &arr);

    // Declaraciones para deque
    size_t _binarySearchDeque(const std::deque<int> &arr, int value);
    void _fordJohnsonSortDeque(std::deque<int> &arr);

public:
    PmergeMe(void);
    PmergeMe(std::vector<std::string> const &argvString);
    PmergeMe(PmergeMe const &copy);
    ~PmergeMe(void);
    PmergeMe &operator=(PmergeMe const &other);

    void fJVector(void);
    void fJDeque(void);
};

#endif