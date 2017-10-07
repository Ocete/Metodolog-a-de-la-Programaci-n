/**
   @file imagen.h
   @brief Manejo de imágenes digitales en formato PGM blanco y negro
   @author MP-DGIM - Grupo A

**/

#include "byte.h"
#include "pgm.h"
#include "imagen.h"
#include <iostream>
using namespace std;

/**
@brief Una imagen en blanco y negro. Cada píxel es un Byte
*/

bool CompruebaAcceso(int fil, int col, int nfil, int ncol) {
  return fil >= 0 &&  col >= 0 && fil < nfil && col < ncol;
}

Imagen::Imagen() {
  datos = NULL;
  nfilas = 0;
  ncolumnas = 0;
}

/**
@brief Construye una imagen negra de tamaño @a filas x @a columnas
@param filas 	número de filas de la imagen
@param columnas	número de columnas de la imagen

Construye una imagen de tamaño @a filas x @a columnas y pone todos
sus elementos a 0.
*/
Imagen::Imagen(int filas, int columnas) {
  datos = NULL;
  crear(filas, columnas);
}

Imagen::Imagen(const Imagen &imag) {
  datos = NULL;
  *this = imag;
}

/**
@brief Crea una imagen negra de tamaño @a filas x @a columnas
@param filas 	número de filas de la imagen
@param columnas	número de columnas de la imagen

Dimensiona la imagen a tamaño @a filas x @a columnas y pone todos
sus elementos a 0.
*/
void Imagen::crear(int filas, int columnas) {
  destruir();
  datos = new Byte*[filas];
  datos[0] = new Byte[filas*columnas];
  for (int i=1; i < filas; i++)
    datos[i] = datos[i-1] + columnas;
  this->nfilas = filas;
  this->ncolumnas = columnas;
  for (int i = 0; i < filas; i++)
    for (int j=0; j<columnas; j++)
      datos[i][j] = 0;
}


/**
@brief Devuelve el número de filas de las imagen
@return el número de filas de la imagen
*/
int Imagen::filas() const {
  return this->nfilas;
}


/**
@brief Devuelve el número de columnas de las imagen
@return el número de columnas de la imagen
*/
int Imagen::columnas() const {
 return this->ncolumnas;
}


/**
@brief Asigna el valor @a v a la posición (@a x,@a y) de la imagen
@param y 	fila de la imagen
@param x 	columna de la imagen
@param v 	valor a asignar

Asigna el valor @a v a la posición (@a x,@a y) de la imagen. Dado que la imagen se guarda
como un vector, la posición (@a x,@a y) corresponde a la posición @a y * @c ncolumnas + @a x
del vector.
*/
void Imagen::set(int y, int x, Byte v) {
 if (CompruebaAcceso(y, x, nfilas, ncolumnas))
  datos[y][x] = v;
}


/**
@brief Devuelve el valor de la posición (@a x,@a y) de la imagen
@param y	 fila de la imagen
@param x	 columna de la imagen
@return el valor de la posición (@a x,@a y) de la imagen

Devuelve el valor de la posición (@a x,@a y) de la imagen. Dado que la imagen se guarda
como un vector, la posición (@a x,@a y) corresponde a la posición @a y * @c ncolumnas + @a x
del vector.
*/
Byte Imagen::get(int y, int x) const {
  Byte b = 0;
  if (CompruebaAcceso(y, x, nfilas, ncolumnas))
    b = datos[y][x];
  return b;
}


/**
@brief Asigna el valor @a v a la posición @a i de la imagen considerada como vector
@param i 	posición de la imagen considerada como vector
@param v 	valor a asignar

Asigna el valor @a v a la posición @a i de la imagen considerada como vector. La posición @a i
corresponde con la posición @c y * @c ncolumnas + @c x de la imagen donde @c y representa la
fila y @c x representa la columna.
*/
void Imagen::setPos(int i, Byte v) {
 if (i >= 0 && i < nfilas*ncolumnas)
   datos[0][i] = v;
}


/**
@brief Devuelve el valor de la posición @a i de la imagen considerada como vector
@param i 	posición de la imagen considerada como vector

Devuelve el valor de la posición @a i de la imagen considerada como vector. La posición @a i
corresponde con la posición @c y * @c ncolumnas + @c x de la imagen donde @c y representa la
fila y @c x representa la columna.
*/
Byte Imagen::getPos(int i) const {
  Byte b = 0;
  if (i >= 0 && i < nfilas*ncolumnas)
    b = datos[0][i];
  return b;
}

void Imagen::destruir () {
  if (datos != NULL) {
    delete [] datos[0];
    delete [] datos;
  }
  datos = NULL;
  nfilas = 0;
  ncolumnas = 0;
}


///////////////////////////////////////////////////////////////////////////

/**
@brief Carga una imagen desde un fichero
@param nombreFichero nombre del fichero que contiene la imagen
@retval true 	si ha tenido éxito en la lectura
@retval false 	si se ha producido algún error en la lectura

Lee desde disco los datos de la imagen llamada @a nombreFichero y la guarda en
la memoria. La función debe asegurarse de que la imagen es de un tipo de imagen
conocido y de que su tamaño es menor del tamaño máximo permitido (@c MAXDATOS).
*/
bool Imagen::leerImagen(const char nombreFichero[]) {
  int filas, columnas;
  bool result = false;
  TipoImagen tipo = infoPGM (nombreFichero, filas, columnas);
  if (tipo == IMG_PGM_BINARIO) {
    crear(filas, columnas);
    if (leerPGMBinario(nombreFichero, datos[0], filas, columnas)) {
      this->nfilas = filas;
      this->ncolumnas = columnas;
      result = true;
    }
  } else if (tipo == IMG_PGM_TEXTO) {
    crear(filas, columnas);
    if (leerPGMTexto(nombreFichero, datos[0], filas, columnas)) {
      this->nfilas = filas;
      this->ncolumnas = columnas;
      result = true;
    }
  }
  return result;
}


/**
@brief Guarda una imagen desde un fichero
@param nombreFichero nombre del fichero que contiene la imagen
@param esBinario toma el valor @c true si el fichero se escribe en formato binario o @c false en caso contrario.
@retval true 	si ha tenido éxito en la escritura
@retval false 	si se ha producido algún error en la escritura
*/
bool Imagen::escribirImagen(const char nombreFichero[], bool esBinario) const {
  bool result = false;
  if (esBinario) {
   result = escribirPGMBinario(nombreFichero, datos[0], nfilas, ncolumnas);
  } else {
   result = escribirPGMTexto(nombreFichero, datos[0], nfilas, ncolumnas);
  }
  return result;
}

///////////////////////////////////////////////////////////////////////////////////
Imagen Imagen::plano (int k) const {
  Imagen nueva(this->nfilas, this->ncolumnas);
  Byte aux;
  offByte(aux);
  onBit(aux, k);
  for (int i=0; i<this->nfilas; i++) {
    for (int j=0; j<this->ncolumnas; j++) {
      offByte(nueva.datos[i][j]);
      if (this->datos[i][j] & aux)
        onBit(nueva.datos[i][j], 7);
    }
  }
  return nueva;
}

bool Imagen::aArteASCII(const char grises[], char arteASCII[], int maxlong, int nGrises) const {
  bool result = false;
  int iTope = this->nfilas * this->ncolumnas;
  int jTope = iTope + this->ncolumnas + 1;
  if (maxlong >= jTope && nGrises <= 255) {
    int j=0, k=0;
    for (int i=0; i<iTope; i++) {
      arteASCII[j] = grises[this->datos[0][i]*nGrises/256];
      j++;
      k++;
      if (k == this->ncolumnas) {
        arteASCII[j] = '\n';
        j++;
        k = 0;
      }
    }
    arteASCII[jTope - 1] = '\0';
    result = true;
  }
  return result;
}

Imagen Imagen::combinarCon(const Imagen &img, int k, int npasos) const {
  Imagen nueva;
  if (this->ncolumnas != img.ncolumnas && this->nfilas != img.nfilas) {
    cerr << "Error en Imagen::combinarCon - las imágenes no tienen las mismas dimensiones." << endl;
  } else if (npasos <= 0 || k > npasos || k <0) {
    cerr << "Error en Imagen::combinarCon - 'k' y/o 'npasos' incorrectos." << endl;
  } else {
    nueva.crear(nfilas, ncolumnas);
    for (int i=0; i<nueva.nfilas; i++) {
      for (int j=0; j<nueva.ncolumnas; j++) {
        nueva.datos[i][j] = this->datos[i][j] +
          k * (img.datos[i][j] - this->datos[i][j]) / npasos;
      }
    }
  }
  return nueva;
}

///////////////////////////////////////////////////////////////////////////////////

void Imagen::operator = (const Imagen &imag) {
  if (this != &imag) {
    crear(imag.filas(), imag.columnas());
    for (int i = 0; i<nfilas; i++)
      for (int j = 0; j<ncolumnas; j++)
        datos[i][j] = imag.get(i, j);
  }
}


Imagen::~Imagen() {
  destruir();
}
