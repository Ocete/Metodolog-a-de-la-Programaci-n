#include "imagen.h"
#include "lista.h"
#include <cstdlib>

#include <iostream> // SOLO PARA DEPURACION
using namespace std;

Celda::Celda () {
  this->img = NULL;
  this->sig = NULL;
}

/** @brief Destructor de la clase */
Celda::~Celda () {
	if (img != NULL)
		delete img;
}

/** @brief Inserta UNA COPIA de la imagen que se pasa por parámetro en la celda (usar operador = sobrecargado)
	 @param img La imagen cuya copia se pretende insertar  	 */
void Celda::setImagen (const Imagen &in) {
  if (img == NULL) {
    img = new Imagen;
  }
  *img = in;
}


/** @brief Devuelve un puntero a la imagen contenida en la celda
	 @return La dirección de memoria de la imagen contenida 	 */
Imagen * Celda::getImagen() const {
  return this->img;
}

/** @brief Actualiza el puntero a la siguiente celda con el puntero que recibe como argumento
	 @param next Puntero a la siguiente celda 	 */
void Celda::setSiguiente(Celda *next) {
  sig = next;
}

/** @brief Devuelve el puntero a la siguiente celda
	 @return Puntero a la siguiente celda 	 */
Celda * Celda::getSiguiente() const {
  return sig;
}

Lista::Lista() {
  lista = NULL;
}

/** @brief Destructor de la clase */
Lista::~Lista() {
	destruir();
}

/** @brief Libera toda la lista */
void Lista::destruir() {
	Celda * aux;
	while (lista != NULL) {
		aux = lista;
		lista = lista->getSiguiente();
		delete aux;
	}
}

/** @brief Inserta UNA COPIA de la imagen en la primera posición de la lista, desplazando el resto, si lo hubiese.
	 @param img La imagen cuya copia se pretende insertar  	 */
void Lista::insertarPrincipio(const Imagen &img) {
  Celda * aux = lista;
  lista = new Celda;
  lista->setImagen(img);
  lista->setSiguiente(aux);
}

/** @brief Inserta UNA COPIA de la imagen en la última posición de la lista.
	 @param img La imagen cuya copia se pretende insertar  	 */
void Lista::insertarFinal(const Imagen &img) {
  if (lista == NULL) {
    lista = new Celda;
    lista->setImagen(img);
  } else {
    Celda * i = lista;
    while (i->getSiguiente() != NULL) {
      i = i->getSiguiente();
    }
    i->setSiguiente(new Celda);
    i->getSiguiente()->setImagen(img);
  }
}


/** @brief Devuelve la longitud de la lista
	 @return El número de celdas válidas que contiene la lista 	 */
int Lista::longitud() const {
  int lon = 0;
  Celda * i = lista;
  while (i != NULL) {
    i = i->getSiguiente();
    lon++;
  }
  return lon;
}

/** @brief Consulta una celda de la lista
	 @param pos Posición ordinal de la celda que se quiere consultar
	 @return La dirección de memoria de la Imagen en la celda que ocupa la posición @a pos dentro de la lista. Si @a pos es mayor o igual que la longitud de la lista, entonces devuelve 0 	 */
Imagen * Lista::get(int pos) const {
  Celda * ret = lista;
  while (pos > 0 && ret->getSiguiente() != NULL) {
		ret = ret->getSiguiente();
		pos--;
	}
	return ret->getImagen();
}
