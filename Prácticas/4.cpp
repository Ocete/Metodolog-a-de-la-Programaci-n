#include <cstring>
#include <string>
#include <iostream>

using namespace std;

class Celda{
	private:
		double info;
		Celda *sig;
		
	public:
		Celda();
		~Celda();
		Celda (double info);
		Celda* getSig();
		void SetInfor(double info);
		void SetSig(Celda* sig);
		double GetInfo ();
		void printList ();
		
};

double Celda::GetInfo(){
	return info;
}

Celda::Celda(double info){
	this->info = info;
	sig = NULL;
}

Celda::Celda(){
	info = 0;
	sig = NULL;
}

void Celda::SetInfor(double info){
	this->info = info;	
}

void Celda::SetSig(Celda* sig){
	this -> sig = sig;
}

Celda* Celda::getSig(){
	return sig;
}

class Lista{
	private:
		Celda * contenido;
		void copia (const Lista& otro);
		Lista CopiaProfunda (const Lista lista);
	public:
		Lista();
		~Lista();
		Lista (const Lista& otro);
		Lista& operator+(const Lista& otro);
		Lista& operator=(const Lista& otro);
		void operator[] (int pos); //Este método borra la posicion indicada 
};

Lista::Lista(){
	contenido = NULL;	
}

Lista::~Lista(){
	Celda *ptr;
	while (contenido != NULL){
		ptr = contenido;
		contenido = contenido -> getSig();
		delete ptr;	
	}
}

Lista::Lista(const Lista& otro){
	
	Celda *aux1;
	Celda *aux2;
	Celda *aux3;
	if (otro.contenido == NULL)
		contenido = NULL;
	else {
		aux1 = otro.contenido->getSig();
		contenido = new Celda (otro.contenido->GetInfo());
		aux2 = contenido;
		while (aux1 != NULL){
			aux3 = new Celda (aux1->GetInfo()); //AUX3 apunta a una nueva celda que apunta al contenido de AUX1
			aux2->SetSig(aux3);					//AUX2 apunta a AUX3
			aux1=aux1->getSig();				//AUX1 apunta a su siguiente Celda
			aux2=aux2->getSig();				//AUX2 apunta a su siguiente Celda
		}
	}
}

Lista& Lista::operator=(const Lista& otro) {
	if (this != &otro) {
		delete this;
		this->contenido = otro.contenido;
	}
	return *this;
}

Lista& Lista::operator+(const Lista& otro) {
	Lista *copia1 = new Lista (*this);
	Lista *copia2 = new Lista (otro);
	Celda *aux;
	aux = copia1->contenido;
	while (aux->getSig() != NULL){
		aux = aux->getSig(); 
	}
	aux->SetSig(copia2->contenido);
	return *copia1;
}

void Lista::operator[](int pos){
	Celda* aux;
	if (pos >= 0 && contenido!=NULL){
		aux = contenido;
		if (pos=0){
			aux = aux->getSig();
			delete contenido;
			contenido = aux; 
		}else {
			int i=0;
			while (aux->getSig() != NULL && i<pos-1 ){
				aux = aux->getSig();
			}
			if(aux->getSig() != NULL) {
				Celda *aux2;
				aux2 = aux->getSig()->getSig();
				delete aux->getSig();
				aux->SetSig(aux2);
			}
		}
	}
}

void Lista::printLista () {
	Celda * aux = contenido;
	while (aux != NULL) {
		cout << aux->info << ' ';
		aux = aux -> sig;
	}
	cout << endl;
}


