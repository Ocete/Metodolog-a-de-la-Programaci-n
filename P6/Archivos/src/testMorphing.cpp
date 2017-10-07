/**
   @file testplano.cpp
   @brief Lee la imagen imagenes/giotexto.pgm y extrae el plano 6 en plano6.pgm y el
   plano 0 en plano0.pgm
   @author MP-DGIM - Grupo A

**/
#include <iostream>
#include <imagen.h>
#include <lista.h>
#include <string>
#include <cstdlib>
#include <cstdio>

using namespace std;

int main(int argc,char** argv){
  // Comprobamos el número de argumentos
  if (argc<5){
    cerr << "Error en nº de parámetros. Ejecución:\n";
		cerr << argv[0] << " <imagen1> <imagen2> <npasos> <salida>" << endl;
    exit(-1);
  }

  // Comprobamos que el parámetro npasos tiene un valor correcto
  int npasos = atoi(argv[3]);
  if (npasos <= 0 || npasos > 20){
    cerr << "Error en nº de pasos. Tiene que tomar un valor entre 1 y 20.\n";
    exit(-1);
  }

  Imagen img1, img2;
  string nombreImg1, nombreImg2, salida;

  // Leemos el nombre de salida
  salida = argv[4];
  char * salidaMod = new char[salida.size() + 7];

  // Leemos la imagen 1
	nombreImg1 = argv[1];
  if (!img1.leerImagen(nombreImg1.c_str())){
   cerr << "error leyendo "<< nombreImg1 << endl;
   delete [] salidaMod;
   exit(-1);
  }
	cout << "Imagen " << nombreImg1 << " leida correctamente" << endl;

  // Leemos la imagen 2
	nombreImg2 = argv[2];
  if (!img2.leerImagen(nombreImg2.c_str())){
   cerr << "error leyendo "<< nombreImg2 << endl;
   delete [] salidaMod;
   exit(-1);
  }
	cout << "Imagen " << nombreImg2 << " leida correctamente" << endl;

  // Creamos la lista con los fundidos
  Lista lista;
  Imagen img3;
  for (int i=0; i<=npasos; i++) {
    img3 = img1.combinarCon(img2, i, npasos);
    lista.insertarFinal(img3);
    cout << salida << i << ".pgm creada." << endl;
  }

  // Escribimos las imágenes
  for (int i=0; i<=npasos; i++) {
    sprintf(salidaMod,"%s%d.pgm", salida.c_str(), i);
    if (lista.get(i)->escribirImagen(salidaMod, true)) {
      cout << salidaMod << " guardado correctamente \n";
    } else {
      cerr << "Error guardando la imagen " << salidaMod;
      delete [] salidaMod;
      exit(-1);
    }
  }

  delete [] salidaMod;
	return 0;
}
