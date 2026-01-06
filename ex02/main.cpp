/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:43:03 by frromero          #+#    #+#             */
/*   Updated: 2026/01/06 11:29:19 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>

#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Error: Invalid input" << std::endl;
        return 1;
    }

    std::vector<std::string> args;
    for (int i = 1; i < argc; i++) /*Create a vector from argv */
        args.push_back(argv[i]);

    try
    {
        PmergeMe sortNumber(args);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}