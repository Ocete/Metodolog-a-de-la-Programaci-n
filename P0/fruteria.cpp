/*
  * @file fruteria.cpp
  * @brief Programa para la gestión de tickets de compra usando structs
  * @authorJosé Antonio Álvarez Ocete- Grupo A
*/

#include <iostream>
#include <string>

using namespace std;

struct Producto {
    string nombre;
    int peso; // en gramos
    float precio_kg;
};

struct Compra {
    static const int MAX = 10;
    Producto lista[MAX];
};

// Imprime un producto en pantalla
void imprimeProducto(Producto a) {
    cout << a.nombre << "\t\t" << a.peso << "\t" << a.precio_kg;
}

// Crea un producto y lo inicializa con los parámetros que recibe
Producto creaProducto(string nombre, int peso, float precio) {
  Producto p = {nombre, peso, precio};
  return p;
}

// Incrementa el precio por kilo de los productos de una lista en k
void incrementarPrecios(Compra & c, int k) {
  for (int i=0; i<c.MAX; i++)
    c.lista[i].precio_kg *= (1 + k/100.0);
}

// Muestra la lista de la compra
void imprimirCompra(const Compra & c) {
  for (int i=0; i<c.MAX; i++) {
    imprimeProducto(c.lista[i]);
    cout << endl;
  }
}

// Extrae el precio y el peso totales de una lista de la compra
void obtenerImporteYPeso(const Compra & c, float & precio, int & peso) {
  precio = 0;
  peso = 0;

  for (int i=0; i<c.MAX; i++) {
    peso += c.lista[i].peso;
    precio += ((c.lista[i].peso / 1000.0) * c.lista[i].precio_kg);
  }

  //NOTA IMPORTANTE: Creo que esta función debería devolver el peso en GRAMOS en
  //vez de kilogramos. Sin embargo, el main la interpreta como si fuesen kgs asi
  //que para no alterar el main, devolveré el peso en kilogramos (sin redondear).
  peso /= 1000;
}

// Muestra la lista de la compra y el importe final desglosado en subtotal, IVA y total
void imprimirTicketCompra(const Compra & c) {
  float subtotal, iva, precio;
  const int IV_IVA = 21;
  int aux;
  obtenerImporteYPeso(c, subtotal, aux);
  iva = subtotal * (IV_IVA/100.0);
  precio = subtotal + iva;

  imprimirCompra(c);
  cout << "Subtotal:\t\t" << subtotal << endl;
  cout << "IVA (" << IV_IVA << "%):\t\t" << iva << endl;
  cout << "Total de la compra:\t" << precio << endl;
}
//Nota: Sería más eficiente tener una función obtenerImporte, ya que calculo del
//peso no es necesario.

int main () {
    const int TAM = 10;
    Producto actual;
    Compra mi_compra;
    float precio;
    int peso;
    string nombre;

    for(int i = 0; i < TAM; i++) {
        cin >> nombre >> peso >> precio;
        mi_compra.lista[i] = creaProducto(nombre, peso, precio);
    }

    // se muestra la lista de productos.
    cout << "\n ******** Prueba de funcion listarCompra ******** \n";
    imprimirCompra(mi_compra);

    // se muestra el importe total de la compra y el peso
    cout << "\n ******** Prueba de funcion obtenerImporteYPeso ******** \n";
    obtenerImporteYPeso(mi_compra, precio, peso);
    cout << "\nEl importe de la compra es: " << precio << ", su compra pesa:"
		 << peso << " Kg. " << endl;

    // se muestra el ticket de la compra.
    cout << "\n ******** Prueba de la funcion mostrarTicketCompra ******** \n";
    imprimirTicketCompra(mi_compra);

    cout << "\n ******** Prueba de la funcion incrementarPrecio ********";
    incrementarPrecios(mi_compra, 10);
    cout << "\n ******** y listarCompra de nuevo   \t\t********\n\n";
    imprimirCompra(mi_compra);

    return(0);
}
