# \_fordJohsonSortVector()


```

[INPUT] e.g., [6, 24, 999, 78, 5, 21, 3]
    │
    ▽
¿Tamaño > 1? → No → RETORNAR
    │ Sí
    ▽
¿Hay impar? → Sí → Guardar oddElement = 3
    │ No
    ▽
[FORMAR PARES] → (Mayor, Menor)
    │
    ▽
[6,24]→(24,6), [999,78]→(999,78), [5,21]→(21,5)
    │
    ▽
[EXTRAER LARGER] → [24, 999, 21]
    │
    ▽
┌───────────────────────┐
│  RECURSIÓN en       ──│ ←──────────────────────────┐
│  LARGER = [24,999,21] │                            │
└───────────────────────┘                            │
    │                                                │
    ▽ (Mismo proceso recursivo)                      │
[24,999,21] → impar=21                               │
    │                                                │
    ▽                                                │
[FORMAR PARES] → [24,999]→(999,24)                   │
    │                                                │
    ▽                                                │
[EXTRAER LARGER] → [999]                             │
    │                                                │
    ▽ (Tamaño=1, fin recursión)                      │
[RECONSTRUIR smaller] → smaller[0] = 24              │
    │                                                │
    ▽                                                │
[CONSTRUIR mainChain] → [24] + [999] = [24, 999]     │
    │                                                │
    ▽                                                │
[INSERTAR impar 21] → binarySearch → [21, 24, 999]   │
    │                                                │
    ▽ (Retorno recursión)                            │
larger ORDENADO = [21, 24, 999]                      │
    │                                                │
    ▽                                                │
┌────────────────────────────────────────────────────┘
│
▽
[RECONSTRUIR larger ordenado con su smaller correspondiente]
Buscar para cada larger[i] su par original:
larger[0]=21 → par(21,5) → smaller[0]=5
larger[1]=24 → par(24,6) → smaller[1]=6  
larger[2]=999 → par(999,78) → smaller[2]=78
    │
    ▽
smaller = [5, 6, 78]
    │
    ▽
[CONSTRUIR mainChain INICIAL]
1. smaller[0] = 5 (directo, sin búsqueda)
2. larger completo = [21, 24, 999]
    │
    ▽
mainChain = [5, 21, 24, 999] ← "Esqueleto ordenado"
    │
    ▽
┌─────────────────────────────────────────────────┐
│  INSERCIÓN BINARIA de smaller[1..]              │
│  (CORAZÓN DEL ALGORITMO)                        │
└─────────────────────────────────────────────────┘
    │
    ▽
[ORDEN JACOBSTHAL] para remaining = [6, 78]
Secuencia: [0, 1] → insertar índice 0, luego 1
    │
    ▽
┌─────────────────────┐
│ PASO 1: Insertar 6  │
└─────────────────────┘
mainChain actual: [5, 21, 24, 999]
    │
    ▽ (¡BÚSQUEDA BINARIA!)
Binary Search(6, [5, 21, 24, 999]):
1. left=0, right=4, mid=2 → 24, 6 < 24 → right=2
2. left=0, right=2, mid=1 → 21, 6 < 21 → right=1  
3. left=0, right=1, mid=0 → 5, 6 > 5 → left=1
4. left=1, right=1 → STOP → pos=1
    │
    ▽
INSERTAR en posición 1: [5, 6, 21, 24, 999]
    │
    ▽
┌──────────────────────┐
│ PASO 2: Insertar 78  │
└──────────────────────┘
mainChain actual: [5, 6, 21, 24, 999]
    │
    ▽ (¡OTRA BÚSQUEDA BINARIA!)
Binary Search(78, [5, 6, 21, 24, 999]):
1. left=0, right=5, mid=2 → 21, 78 > 21 → left=3
2. left=3, right=5, mid=4 → 999, 78 < 999 → right=4
3. left=3, right=4, mid=3 → 24, 78 > 24 → left=4
4. left=4, right=4 → STOP → pos=4
    │
    ▽
INSERTAR en posición 4: [5, 6, 21, 24, 78, 999]
    │
    ▽
[INSERTAR ELEMENTO IMPAR]
oddElement = 3
    │
    ▽ (¡ÚLTIMA BÚSQUEDA BINARIA!)
Binary Search(3, [5, 6, 21, 24, 78, 999]):
1. left=0, right=6, mid=3 → 24, 3 < 24 → right=3
2. left=0, right=3, mid=1 → 6, 3 < 6 → right=1
3. left=0, right=1, mid=0 → 5, 3 < 5 → right=0
4. left=0, right=0 → STOP → pos=0
    │
    ▽
INSERTAR en posición 0: [3, 5, 6, 21, 24, 78, 999]
    │
    ▽
[OUTPUT ORDENADO]
    │
    └────────────────────────────────────────────┐
                                                 │
┌────────────────────────────────────────────────┘
│
▽
RESUMEN DE INSERCIONES BINARIAS REALIZADAS:
1. Inserción de smaller[1]=6 → pos=1
2. Inserción de smaller[2]=78 → pos=4  
3. Inserción de oddElement=3 → pos=0
   TOTAL: 3 búsquedas binarias O(log n)

```
