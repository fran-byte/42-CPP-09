/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:19:35 by frromero          #+#    #+#             */
/*   Updated: 2026/01/05 20:55:04 by frromero         ###   ########.fr       */
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
    /*Añadir metodos privados*/

public:
    PmergeMe(void);
    PmergeMe(std::string const &strNumbers);
    PmergeMe(PmergeMe const &copy);
    ~PmergeMe(void);
    PmergeMe &operator=(PmergeMe const &other);

    void fJVector(void); /*ford Johnson Vector*/
    void fJDeque(void);  /*ford Johnson Deque*/
};

#endif
