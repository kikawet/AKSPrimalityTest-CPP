// AKSPrimalityTest.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
//https://en.wikipedia.org/wiki/AKS_primality_test

#include <iostream>
#include <vector>
#include <thread>
#include <future>

#include "../AKSPrimalityTest/AKS.h"

int main() {
	const uint64_t limit = 100;
	const int numThreads = 1;
	std::vector<std::future<void>> threads;

	std::cout << std::boolalpha;

	for (int i = 0; i < numThreads; ++i) {
		threads.push_back(std::move(std::async(std::launch::async, [i]() {
			int start = i * limit / numThreads;
			int end = (i + 1) * (limit / numThreads);
			for (uint64_t j = start; j < end; ++j) {
				if (isPrime(j))
					std::cout << j << '\n';
			}
			})));
	}

	for (int i = 0; i < threads.size(); ++i) {
		threads[i].wait();
	}

	std::cout << std::endl;

	return EXIT_SUCCESS;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
