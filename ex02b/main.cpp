/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frromero <frromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:43:03 by frromero          #+#    #+#             */
/*   Updated: 2026/01/16 23:46:19 by frromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>

#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <string>
void info();
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
        sortNumber.fJVector();
        sortNumber.fJDeque();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    info();
    return 0;
}

void info()
{
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════════╗\n";
    std::cout << "║                 FORD–JOHNSON MERGE–INSERT                  ║\n";
    std::cout << "╠════════════════════════════════════════════════════════════╣\n";
    std::cout << "║                                                            ║\n";
    std::cout << "║  INPUT                                                     ║\n";
    std::cout << "║  ─────                                                     ║\n";
    std::cout << "║  [8, 3, 7, 4, 6, 1, 5, 2]                                  ║\n";
    std::cout << "║                                                            ║\n";
    std::cout << "║  1) CREAR PARES                                            ║\n";
    std::cout << "║     (8,3) (7,4) (6,1) (5,2)                                ║\n";
    std::cout << "║     → ordenar cada par internamente (mayor, menor)         ║\n";
    std::cout << "║                                                            ║\n";
    std::cout << "║  2) EXTRAER LARGER                                         ║\n";
    std::cout << "║     larger = [8, 7, 6, 5]                                  ║\n";
    std::cout << "║              │                                             ║\n";
    std::cout << "║              ▼                                             ║\n";
    std::cout << "║        llamada recursiva                                   ║\n";
    std::cout << "║              │                                             ║\n";
    std::cout << "║              ▼                                             ║\n";
    std::cout << "║     larger ordenado = [5, 6, 7, 8]                         ║\n";
    std::cout << "║                                                            ║\n";
    std::cout << "║  3) RECONSTRUIR SMALLER                                    ║\n";
    std::cout << "║     smaller asociado = [2, 1, 4, 3]                        ║\n";
    std::cout << "║     (mantiene correspondencia con larger)                  ║\n";
    std::cout << "║                                                            ║\n";
    std::cout << "║  4) CONSTRUIR MAINCHAIN BASE                               ║\n";
    std::cout << "║     mainChain = [2] + [5,6,7,8]                            ║\n";
    std::cout << "║     mainChain = [2, 5, 6, 7, 8]                            ║\n";
    std::cout << "║                                                            ║\n";
    std::cout << "║     remaining = [1, 4, 3]                                  ║\n";
    std::cout << "║                                                            ║\n";
    std::cout << "║  5) JACOBSTHAL                                             ║\n";
    std::cout << "║     remaining.size() = 3                                   ║\n";
    std::cout << "║     getInsertionOrderVector(3)                             ║\n";
    std::cout << "║              │                                             ║\n";
    std::cout << "║              ▼                                             ║\n";
    std::cout << "║     orden = [1, 0, 2]                                      ║\n";
    std::cout << "║                                                            ║\n";
    std::cout << "║  6) INSERCIÓN GUIADA (Binary Search)                       ║\n";
    std::cout << "║                                                            ║\n";
    std::cout << "║     idx = 1 → remaining[1] = 4                             ║\n";
    std::cout << "║     _binarySearchVector(mainChain, 4) → pos = 1            ║\n";
    std::cout << "║     mainChain = [2, 4, 5, 6, 7, 8]                         ║\n";
    std::cout << "║                                                            ║\n";
    std::cout << "║     idx = 0 → remaining[0] = 1                             ║\n";
    std::cout << "║     _binarySearchVector(mainChain, 1) → pos = 0            ║\n";
    std::cout << "║     mainChain = [1, 2, 4, 5, 6, 7, 8]                      ║\n";
    std::cout << "║                                                            ║\n";
    std::cout << "║     idx = 2 → remaining[2] = 3                             ║\n";
    std::cout << "║     _binarySearchVector(mainChain, 3) → pos = 2            ║\n";
    std::cout << "║     mainChain = [1, 2, 3, 4, 5, 6, 7, 8]                   ║\n";
    std::cout << "║                                                            ║\n";
    std::cout << "║  7) RESULTADO FINAL                                        ║\n";
    std::cout << "║     mainChain ordenada                                     ║\n";
    std::cout << "║     [1, 2, 3, 4, 5, 6, 7, 8]                               ║\n";
    std::cout << "║                                                            ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════╝\n";
}