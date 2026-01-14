/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:19:35 by frromero          #+#    #+#             */
/*   Updated: 2026/01/14 18:07:55 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <vector>
#include <deque>
#include <string>

class PmergeMe
{
private:
    /*  Exercise 00: Using std::map as container
        Exercise 01: Using std::stack as container
        Exercise 02: Using std::vector and std::deque as containers */
    std::vector<int> _vec;
    std::deque<int> _deq;
    bool _isValidInt(const std::vector<std::string> &argvString);
    size_t _binarySearchVector(const std::vector<int> &arr, int value);
    size_t _binarySearchDeque(const std::deque<int> &arr, int value);
    void _fordJohnsonSortVector(std::vector<int> &arr);
    void _fordJohnsonSortDeque(std::deque<int> &arr);

public:
    PmergeMe(void);
    PmergeMe(std::vector<std::string> const &argvString);
    PmergeMe(PmergeMe const &copy);
    ~PmergeMe(void);
    PmergeMe &operator=(PmergeMe const &other);

    void fJVector(void); /*ford Johnson Vector*/
    void fJDeque(void);  /*ford Johnson Deque*/
};

#endif
