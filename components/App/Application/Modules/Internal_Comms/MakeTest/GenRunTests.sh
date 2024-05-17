#!/bin/bash

# Ejecutar cmake para configurar el proyecto
cmake -B build

# Verificar si la configuración de cmake fue exitosa
if [ $? -eq 0 ]; then
    
    # Ejecutar cmake --build para compilar el proyecto
    cmake --build build
    
    # Verificar si la compilación fue exitosa
    if [ $? -eq 0 ]; then
        # Ruta al archivo test_runner
        test_runner="./build/bin/test_suite"

        # Verificar si estamos en Windows
        if [ -f "$test_runner.exe" ]; then
            test_runner="$test_runner.exe"
        fi
        
        # Verificar si el archivo test_runner existe
        if [ -f "$test_runner" ]; then
            # Ejecutar test_runner y redirigir la salida a un archivo de texto
            echo "Ejecutando $test_runner"
            "$test_runner" > test_report.txt
        else
            echo "Error: No se encontró el archivo $test_runner."
        fi
    else
        echo "Error: La compilación del proyecto falló."
    fi
else
    echo "Error: La configuración de cmake falló."
fi







