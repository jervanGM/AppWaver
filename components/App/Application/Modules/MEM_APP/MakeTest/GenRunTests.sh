components/App/Application/Modules/ANA_APP/MakeTest/GenRunTests.sh#!/bin/bash

# Limpiar el archivo test_report.txt al inicio del script
> test_report.txt

# Ejecutar cmake para configurar el proyecto con FFF_ENABLE encendido (on)
cmake -B build -DFFF_ENABLE=1
cmake -B build -DDISABLE_TRACES=0

# Verificar si la configuración de cmake fue exitosa
if [ $? -eq 0 ]; then
    
    # Ejecutar cmake --build para compilar el proyecto
    cmake --build build
    
    # Verificar si la compilación fue exitosa
    if [ $? -eq 0 ]; then
        # Ruta al archivo test_runner.exe
        test_runner="./build/bin/test_suite.exe"
        
        # Verificar si el archivo test_runner.exe existe
        if [ -f "$test_runner" ]; then
            # Ejecutar test_runner.exe y agregar la salida al archivo de texto
            echo "Ejecutando $test_runner"
            "$test_runner" >> test_report.txt
        else
            echo "Error: No se encontró el archivo $test_runner."
        fi
    else
        echo "Error: La compilación del proyecto falló."
    fi
else
    echo "Error: La configuración de cmake falló."
fi

# Ejecutar cmake para configurar el proyecto con FFF_ENABLE apagado (off)
cmake -B build -DFFF_ENABLE=0
cmake -B build -DDISABLE_TRACES=1

rm -r ./sdcard
mkdir -p ./sdcard

# Verificar si la configuración de cmake fue exitosa
if [ $? -eq 0 ]; then
    
    # Ejecutar cmake --build para compilar el proyecto
    cmake --build build
    
    # Verificar si la compilación fue exitosa
    if [ $? -eq 0 ]; then
        # Ruta al archivo test_runner.exe
        test_runner="./build/bin/test_suite.exe"
        
        # Verificar si el archivo test_runner.exe existe
        if [ -f "$test_runner" ]; then
            # Ejecutar test_runner.exe y agregar la salida al archivo de texto
            echo "Ejecutando $test_runner"
            "$test_runner" >> test_report.txt
        else
            echo "Error: No se encontró el archivo $test_runner."
        fi
    else
        echo "Error: La compilación del proyecto falló."
    fi
else
    echo "Error: La configuración de cmake falló."
fi







