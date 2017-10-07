/*
  * @file tiempo.cpp
  * @brief Utilidades para la gestión de datos temporales usando structs
	* @authorJosé Antonio Álvarez Ocete- Grupo A
*/

#include <iostream>
using namespace std;

const int SEGUNDOS_MINUTO = 60;
const int MINUTOS_HORA = 60;
const int SEGUNDOS_HORA = SEGUNDOS_MINUTO * MINUTOS_HORA;

struct Tiempo {
	int horas, minutos, segundos;
};

int convertirASegundos(Tiempo t)  {
  return t.segundos + SEGUNDOS_MINUTO * t.minutos + SEGUNDOS_HORA * t.horas;
}

Tiempo convertirATiempo(int segundos)  {
  Tiempo t;

  t.horas = segundos / SEGUNDOS_HORA;
  segundos = segundos % SEGUNDOS_HORA;
  t.minutos = segundos / SEGUNDOS_MINUTO;
  t.segundos = segundos % SEGUNDOS_MINUTO;

  return t;
}

void repararTiempo(Tiempo& t)  {
  int aux;

  aux = t.segundos / SEGUNDOS_MINUTO;
  t.segundos -= aux * SEGUNDOS_MINUTO;
  t.minutos += aux;

  aux = t.minutos / MINUTOS_HORA;
  t.minutos -= aux * MINUTOS_HORA;
  t.horas += aux;
}

bool esPosterior(Tiempo t1, Tiempo t2) {
  int t1s, t2s;

  t1s = convertirASegundos(t1);
  t2s = convertirASegundos(t2);

  return t1s > t2s;
}

Tiempo incrementarTiempo(Tiempo t, int s) {
  t.segundos += s;
  repararTiempo(t);
  return t;
}

void imprimeTiempo(Tiempo t)  {
	cout << "[" << t.horas << "h :" << t.minutos << "m :" << t.segundos << "s]" << endl;
}

int main() {
	Tiempo t_inicial={10, 30, 45}, t;
	int aux;

	cout << "Tiempo inicial: ";
	imprimeTiempo(t_inicial);

	cout << "Introduce HH MM SS" << endl;
	cin >> t.horas >> t.minutos >> t.segundos;
	aux = convertirASegundos(t);
	imprimeTiempo(t);
	cout << "Equivalente a " << aux << " segundos" << endl;

	Tiempo taux = convertirATiempo(aux);
	cout << "A la inversa es ";
	imprimeTiempo(taux);

	repararTiempo(t);
	cout << "Reparado es ";
	imprimeTiempo(t);

	if (esPosterior(t_inicial, t))
		cout << "El tiempo inicial es más grande" << endl;
	else
		cout << "El tiempo inicial es más pequeño" << endl;

	taux = incrementarTiempo(t,100);
	cout << "El tiempo inicial más 100 segundos es ";
	imprimeTiempo(taux);

	return 0;
}
