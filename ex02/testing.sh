#!/bin/bash

# verify_42.sh - Verificación completa para PmergeMe

echo "========================================"
echo "    VERIFICADOR PmergeMe 42"
echo "========================================"

# Paso 1: Generar 3000 números aleatorios
echo "1. Generando 3000 números aleatorios (1-100000)..."
RANDOM_NUMS=$(shuf -i 1-100000 -n 3000 | tr "\n" " ")
echo "   ✓ Generados"

# Paso 2: Ejecutar PmergeMe
echo "2. Ejecutando ./PmergeMe \$RANDOM_NUMS"
./PmergeMe $RANDOM_NUMS > output.txt 2>&1

# Paso 3: Extraer línea "After:"
echo "3. Extrayendo secuencia ordenada..."
AFTER_LINE=$(grep "After:" output.txt)
if [ -z "$AFTER_LINE" ]; then
    echo "   ❌ No se encontró línea 'After:' en la salida"
    exit 1
fi

# Extraer solo los números después de "After:"
SORTED_NUMS=$(echo "$AFTER_LINE" | sed 's/After: //')

# Paso 4: Verificar ordenación
echo "4. Verificando ordenación..."
python3 -c "
import sys

nums_str = '''$SORTED_NUMS'''
numbers = [int(x) for x in nums_str.split() if x]

print(f'Total números: {len(numbers)}')

# Verificar orden
errors = []
for i in range(len(numbers) - 1):
    if numbers[i] > numbers[i + 1]:
        errors.append((i, numbers[i], numbers[i + 1]))

if not errors:
    print('✅ ¡PERFECTO! La secuencia está ordenada correctamente.')
    print(f'Rango: {min(numbers)} - {max(numbers)}')
else:
    print(f'❌ ERROR: {len(errors)} posiciones desordenadas')
    for i, a, b in errors[:5]:  # Mostrar solo primeros 5 errores
        print(f'  Posición {i}: {a} > {b}')
    if len(errors) > 5:
        print(f'  ... y {len(errors) - 5} errores más')
    
    # Encontrar el peor error
    worst = max(errors, key=lambda x: x[1] - x[2])
    print(f'  Peor error: posición {worst[0]}: {worst[1]} > {worst[2]} (diferencia: {worst[1] - worst[2]})')

# Verificar duplicados
if len(set(numbers)) != len(numbers):
    print('⚠️  Advertencia: Hay números duplicados')
else:
    print('✓ Sin duplicados')
"

# Paso 5: Limpieza
rm -f output.txt
echo "========================================"
