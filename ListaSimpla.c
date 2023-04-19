#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

//  1. Definire structura
typedef struct Produs {
	int id;
	float pret;
	char* denumire;
	float cantitate;
}Produs;

//  2. Creare
Produs creareProdus(int id, float pret, const char* denumire, float cantitate) {
	Produs p;
	p.id = id;
	p.pret = pret;
	p.denumire = (char*)malloc(sizeof(char) * strlen(denumire) + 1);
	strcpy(p.denumire, denumire);
	p.cantitate = cantitate;
	return p;
}

//Citire din fisier part1
Produs citireProdus(FILE* f) {
	Produs p;
	char buffer[50];
	fscanf(f, "%d", &p.id);
	fscanf(f, "%f", &p.pret);
	fscanf(f, "%s", buffer);
	p.denumire = (char*)malloc(sizeof(char) * strlen(buffer) + 1);
	strcpy(p.denumire,buffer);
	fscanf(f, "%f", &p.cantitate);
	return p;
}

//  3. Afisare
void afisareProdus(Produs p) {
	printf("\n Id produs: %d \n Pret %5.2f RON \n Denumire : %s \n Cantitate : %5.2f ", p.id, p.pret, p.denumire, p.cantitate);
}

// 1.Definire structura pt Lista Simpla
typedef struct Nod {
	Produs info;
	struct Nod* next;
}Nod;

// 2.Creare Nod
Nod* creareNod(Produs info, Nod* next) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = creareProdus(info.id, info.pret, info.denumire, info.cantitate);
	nou->next = next;
	return nou;
}

// 3. Inserarile Inceput si/sau Final

Nod* inserareInceput(Nod* cap, Produs p) {
	Nod* nou = creareNod(p, NULL);

	if (cap) {
		nou->next = cap;
		cap = nou;
	}
	else {
		cap = nou;
	}
	return cap;
}

Nod* inserareFinal(Nod* cap, Produs pr) {
	Nod* nou = creareNod(pr, NULL);
	if (cap) {
		Nod* p = cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
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
			afisareProdus(p->info);
			p = p->next;
		}
	}
}

Nod* dezalocareLista(Nod* cap) {
	while (cap) {
		Nod* aux = cap;
		cap = cap->next;
		free(aux->info.denumire);
		free(aux);
	}
	return cap;
}

//Citire din fisier part2
Nod* citireDinFisierinLista(FILE* f) {
	Nod* lista = NULL;
	int nr=0;
	fscanf(f, "%d", &nr);
	for (int i = 0; i < nr; i++) {
		lista = inserareFinal(lista, citireProdus(f));
	}
	return lista;
}

//Sa se afiseze cea mai mare valoare a unui parametru

Produs pretulCelMaiMare(Nod* cap) {
	Produs maxPret;
	Nod* p;
	if (cap) {
		maxPret = creareProdus(cap->info.id, cap->info.pret, cap->info.denumire, cap->info.cantitate);
		p = cap->next;
		while (p) {
			if (p->info.pret > maxPret.pret) {
				maxPret = creareProdus(p->info.id, p->info.pret,p->info.denumire, p->info.cantitate);
			}
			p = p->next;
		}
	}
	return maxPret;
}

//stergerea unui produs in depedendeta de cantitate data ca parametru
Nod* stergeProdusDupaCantitate(Nod* cap, float cantitate) {
	if (cap) {
		if (cap->info.cantitate == cantitate) {
			Nod* aux = cap;
			cap = cap->next;
			free(aux->info.denumire);
			free(aux);
		}
		else {
			Nod* p = cap;
			while (p->next && p->next->info.cantitate!= cantitate) {
				p = p->next;
			}//p p.next p.next.next
			if (p->next) {
				Nod* aux = p->next;
				p->next = p->next->next;
				free(aux->info.denumire);
				free(aux);

			}
		}
	}
	return cap;
}

Produs cautareProdusDupaPret(Nod* cap, float pret) {
	if (cap) {
		Nod* p = cap;
		while (p && p->info.pret != pret) {//parcurg lista cat timp mai am noduri in lista si cat timp nu am gasit pretul cautat
			p = p->next;
		}
		if (p) {//mai am noduri in lista inseamna ca am gasit pretul
			return p->info;
		}
		else {//daca nu mai am noduri inseamna ca nu am avt pretul cautat in lista 10 12 20 
			//returnam un obiect fictiv 
			return creareProdus(-1,-1,"", -1);
		}
	}
	else {//daca nu exista lista
		//returnam un obiect fictiv 
		return creareProdus(-1, -1, "", -1);
	}
}

Produs cautareProdusDupaDenumire(Nod* cap, const char* denumire) {
	if (cap) {
		Nod* p = cap;
		while (p && strcmp(p->info.denumire, denumire) != 0) {//parcurg lista cat timp mai am noduri in lista si cat timp nu am gasit denumirea cautat
			p = p->next;
		}
		if (p) {//mai am noduri in lista inseamna ca am gasit denumirea
			return p->info;
		}
		else {//daca nu mai am noduri inseamna ca nu am avt denumirea cautat in lista 
			//returnam un obiect fictiv 
			return creareProdus(-1, -1, "", -1);
		}
	}
	else {//daca nu exista lista
		//returnam un obiect fictiv 
		return creareProdus(-1, -1, "", -1);
	}
}

void main() {
	//Branza, Paine, Lapte
	/*Nod* lista = NULL;
	lista = (inserareInceput(lista, creareProdus(1, 5.2, "Lapte", 2)));
	lista = (inserareInceput(lista, creareProdus(2, 3, "Paine", 3)));
	lista = (inserareInceput(lista, creareProdus(3, 15.5, "Branza de Vaci", 1)));
	afisareLista(lista);
	lista = dezalocareLista(lista);
	printf("\n \n Afisare lista dupa dezalocare: ");
	afisareLista(lista);*/
   
	printf("Afisare lista dupa citire: ");
	FILE* f = fopen("Produse.txt", "r");
	Nod* lista = citireDinFisierinLista(f);;
	afisareLista(lista);
	fclose(f);
	
	printf("\n \n Afisare pretului cel mai mare: ");
	afisareProdus(pretulCelMaiMare(lista));

	printf("\n \n Afisare produsului dupa pretul cautat(dat ca param): ");
	afisareProdus(cautareProdusDupaPret(lista, 4));

	printf("\n \n Afisare produsului dupa denumirea cautata(dat ca param): ");
	afisareProdus(cautareProdusDupaDenumire(lista, "Apa"));

	printf("\n \n Stergerea unui produs dupa cantitate data ca param: ");
	lista=stergeProdusDupaCantitate(lista, 5.5);
	afisareLista(lista);

	printf("\n \n Afisare lista dupa dezalocare: ");
	dezalocareLista(lista);
	fclose(f);
}
