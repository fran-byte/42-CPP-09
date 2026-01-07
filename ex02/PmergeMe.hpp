/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:19:35 by frromero          #+#    #+#             */
/*   Updated: 2026/01/07 18:17:42 by frromero         ###   ########.fr       */
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
    std::vector<int> _vec;
    std::deque<int> _deq;
    bool isValidInt(const std::vector<std::string> &argvString);
    size_t _binarySearchVector(const std::vector<int> &arr, int value);
    size_t _binarySearchDeque(const std::deque<int> &arr, int value);
    void _fordJohnsonRecursiveVector(std::vector<int> &arr);
    void _fordJohnsonRecursiveDeque(std::deque<int> &arr);

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
