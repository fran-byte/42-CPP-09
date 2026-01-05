/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:19:35 by frromero          #+#    #+#             */
/*   Updated: 2026/01/05 20:41:11 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <vector>
#include <deque>

class PmergeMe
{
private:
    std::vector<int> _vec;
    std::deque<int> _deq;
    /*Añadir metodos privados*/

public:
    PmergeMe(void);
    PmergeMe(const int numbers);
    PmergeMe(PmergeMe const &copy);
    ~PmergeMe(void);
    PmergeMe &operator=(PmergeMe const &other);

    void fJVector(std::vector<int> &vect); /*ford Johnson Vector*/
    void fJDeque(std::deque<int> &deq);    /*ford Johnson Deque*/
};

#endif
