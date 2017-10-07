/**
   @file main.cpp
   @brief Operaciones a nivel de bit
   @author MP-DGIM - Grupo A
   @warning Módulo no definitivo (creado para ser modificado)

**/

#include <iostream>
#include "byte.h"

using namespace std;

int main()
{
    Byte b;
    int posiciones[8];
    int size;
    bool inicial[] = {1,0,1,0,0,0,0,0};

    offByte(b);
    cout << "\nbyte apagado bits: ";
	 imprimirByte(b); cout << endl;

	 // enciendo dos bits
    cout << "\nInicializo el byte a partir de un vector de bool ";
    asignarByte(b,inicial);
	 imprimirByte(b); cout << endl;
    cout << "\nAhora enciendo los bits 0, 1 y 2 con la funcion on \n";
    onBit(b,0);
	 imprimirByte(b); cout << endl;
    onBit(b,1);
	 imprimirByte(b); cout << endl;
    onBit(b,2);
	 imprimirByte(b); cout << endl;

    cout << "\nLos bits encendidos estan en las posiciones: ";
    encendidosByte(b,posiciones, size);
    for(int i=0; i< size; i++)
        cout << posiciones[i] << ",";

    cout << endl;

    cout << "\nTodos encendidos: ";
    onByte(b);
	 imprimirByte(b); cout << endl;

    cout << "Todos apagados: ";
    offByte(b);
	 imprimirByte(b); cout << endl;

    cout << "\n\nEjemplo 1 \n";
 	 imprimirByte(0xFF);
   cout << endl;
   for (Byte mask = 0x80; mask > 0; mask = mask >> 1) {
    imprimirByte(~mask);
    cout << endl;
   }  

    cout << "\nAhora la animacion\nEjemplo 2 \n";
    Byte byte = 0xFF;
    imprimirByte(byte);
    cout << endl;
    for (int i = 0; i < 4; i++) {
      offBit(byte, i);
      offBit(byte, 7-i);
      imprimirByte(byte);
      cout << endl;
    }
    for (int i = 3; i >= 0; i--) {
      onBit(byte, i);
      onBit(byte, 7-i);
      imprimirByte(byte);
      cout << endl;
    }

	 return 0;
}
