# \_fordJohsonSortVector()

arr = [6, 24, 999, 78, 5, 21, 3]

hasodd = true

oddElement = 3 POP -> arr = [6, 24, 999, 78, 5, 21]

## PAIRS

24 > 6 [24, 6]

[999 , 78]

21 > 5 [21, 5]

pairs [(24, 6), (999, 78), (21, 5)]

larger = [24, 999, 21]

## RECURSIVIDAD - PRIMERA LLAMADA

arr = [24, 999, 21]

hasOdd = true

oddElement = 21

POP → arr = [24, 999]

## PAIRS (recursivo)

[24, 999] → 999 > 24 → (999, 24)

pairs = [(999, 24)]

## larger (recursivo)

larger = [999]

NO HAY MÁS RECURSIVIDAD! (larger.size() = 1)

RECONSTRUIR smaller (recursivo)

// i=0: larger[0] = 999

// j=0: pairs[0].first = 999, pairs[0].second = 24

larger = [999]

pairs = [(999, 24)]

smaller[0] = pairs[0].second; // smaller[0] = 24

smaller = [24]

## CONSTRUIR mainChain (recursivo)

mainChain.push_back(smaller[0]); // mainChain = [24]

## INSERTAR oddElement (recursivo)

oddElement = 21

binarySearch([24, 999], 21) → posición 0 (21 < 24)

mainChain.insert(0, 21) → mainChain = [21, 24, 999]

# FIN RECURSIVIDAD

Retornamos: larger = [21, 24, 999]

# VOLVEMOS A LLAMADA ORIGINAL

pairs original = [(24,6), (999,78), (21,5)]

larger (ordenado) = [21, 24, 999]

# RECONSTRUIR smaller (original)

smaller = [5, 6, 78]

# CONSTRUIR mainChain (original)

mainChain = [5, 21, 24, 999]

# INSERTAR remaining (Jacobsthal)

/ smaller.size() > 1 → 3 > 1 → TRUE

std::vector<int> remaining;

for (size_t i = 1; i < smaller.size(); i++) // i=1,2

    if (smaller[i] != -1)

        remaining.push_back(smaller[i]);  // remaining = [6, 78]

// getInsertionOrderVector(2)

// insertionOrder = [0, 1]

// Insertar remaining[0] = 6

pos = binarySearch([5, 21, 24, 999], 6) → 1 (entre 5 y 21)

mainChain.insert(1, 6) // [5, 6, 21, 24, 999]

// Insertar remaining[1] = 78

pos = binarySearch([5, 6, 21, 24, 999], 78) → 4 (antes de 999)

mainChain.insert(4, 78) // [5, 6, 21, 24, 78, 999]

# INSERTAR oddElement (original)

oddElement = 3

binarySearch([5, 6, 21, 24, 78, 999], 3) → posición 0 (3 < 5)

mainChain.insert(0, 3) // [3, 5, 6, 21, 24, 78, 999]
