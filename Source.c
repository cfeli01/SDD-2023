#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

typedef struct ContBancar{
	char* titular;
	int suma;
}ContBancar;

ContBancar creareCont(const char* titular, int suma){
	ContBancar cont;
	cont.titular = (char*)malloc(sizeof(char) * (strlen(titular) + 1));
	strcpy(cont.titular, titular);
	cont.suma = suma;
	return cont;
}

ContBancar afisareCont(ContBancar c){
	printf("\n Titularul %s are in cont suma %d", c.titular, c.suma);
}

typedef struct Nod {
	ContBancar info;
	struct Nod* next;
}Nod;

Nod* creareNod(Nod* next, ContBancar info) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->info = creareCont(info.titular, info.suma);
	nod->next = next;
	return nod;
}

Nod* inserareInceput(Nod* cap, ContBancar info) {
	Nod* nou = creareNod(NULL, info);
	if (cap) {
		nou->next = cap;
		cap = nou;
	}
	else {
		cap = nou;
	}
	return cap;
}

void afisareLista(Nod* cap) {
	if (cap) {
		Nod* p = cap;
		while (p) {
			afisareCont(p->info);
		    p = p->next;
		}

	}
	
}

void dezalocareLista(Nod** cap) {
	if (*cap) {
		while (*cap) {
			Nod* aux = *cap;
			*cap = (*cap)->next;
			free(aux->info.titular);
			free(aux);
		}
	}
	
}

void cautareDupaSuma(Nod* cap, int sum,ContBancar * c) {
	if (cap) {
		Nod* p = cap;
		while (p && p->info.suma != sum) {
			p = p->next;
		}
		if (p) {
			*c= p->info;
		}
		else {
			//lista exista dar nu am gasit suma 
			//cont fictiv
			*c=creareCont("", -1);
		}
	}
	else {
		//cont fictiv
		*c= creareCont("", -1);
	}
}
typedef struct HashTable {
	int dim;
	Nod** vector;
}HashTable;

HashTable initHashTable(int dim) {
	HashTable h;
	h.dim = dim;
	h.vector = (Nod**)malloc(sizeof(Nod*) * dim);
	for (int i = 0; i < h.dim; i++) {
		h.vector[i] = NULL;
	}
	return h;
}

int HCode(int sum, HashTable h) {
	return sum % h.dim;/// returneaza restul impartirrii sumei la h.dim  0 1 2 3 4 
}

int hcode2(const char* titular, HashTable h) {
	return titular[0] % h.dim;
}

int hcode3(const char* titular, HashTable h) {
	int sum = 0;
	for (int i = 0; i < strlen(titular); i++) {
		sum += titular[i];
	}
	return sum % h.dim;
}
HashTable inserareHashTable(HashTable h, ContBancar cont) {
	if (h.vector) {
		int poz = hcode2(cont.titular, h);
		h.vector[poz] = inserareInceput(h.vector[poz], cont);
	}
	return h;
}

void afisareHashTable(HashTable h) {
	if (h.vector) {		
		for (int i = 0; i < h.dim; i++) {
			printf("\n pe pozitia %d: \n", i);
			afisareLista(h.vector[i]);
		}
	}
}

HashTable dezalocareHashTable(HashTable h) {
	if (h.vector) {
		for (int i = 0; i < h.dim; i++) {
			 dezalocareLista(&h.vector[i]);
		}
		h.dim = 0;
		free(h.vector);
		h.vector = NULL;
	}
	return h;
}

ContBancar cautareinHashtableDupaSuma(HashTable h, int sum) {
	if (h.vector) {
		int poz = HCode(sum, h);
		ContBancar c;
		cautareDupaSuma(h.vector[poz], sum, &c);
	}
	else {
		return creareCont("", -1);
	}
}
ContBancar cautareinHashtabDupaTitular(HashTable h, const char* titular) {
	if (h.vector) {
		int contor = 0;
		for (int i = 0; i < h.dim; i++) {
			Nod* p = h.vector[i];
			while (p) {
				if (strcmp(titular, p->info.titular) == 0) {
					contor = 1;
					return p->info;
				}
				p = p->next;
			}
		}
		if (contor == 0) {
			return creareCont("", -1);
		}
	}
	else {
		return creareCont("", -1);
	}
}
void main() {
	HashTable h = initHashTable(5);
	ContBancar cont = creareCont("Mircea", 31);
	inserareHashTable(h, cont);
	afisareHashTable(h);
	printf("\n afisare hash table\n");

	h = inserareHashTable(h, creareCont("Andrei Matei", 20));
	h = inserareHashTable(h, creareCont("Ana", 21));
	h = inserareHashTable(h, creareCont("Alex", 35));
	h = inserareHashTable(h, creareCont("Maxim", 24));
	h = inserareHashTable(h, creareCont("Marius", 51));
	h = inserareHashTable(h, creareCont("Ilie", 60));
	afisareHashTable(h);
}
