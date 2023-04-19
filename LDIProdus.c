//afisare i-f normal/pe coduri
//afisare f-i normal/pe coduri
//afisarea codurilor in ambele sensuri

//3
//while in care parcurg toata lista dubla
//suma fiecarui produs in parte (stoc *pret vanzare)
//total+=stoc*pret vanzare

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct Produs {
	int cod;
	char* denumire;
	int stoc;
	int prag_alerta;
	float pret;

}Produs;

Produs creareProdus(int cod, char* denumire, int stoc, int prag_alerta, float pret) {
	Produs p;
	p.cod = cod;
	p.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(p.denumire, denumire);
	p.stoc = stoc;
	p.prag_alerta = prag_alerta;
	p.pret = pret;
	return p;
}

Produs citireProdus(FILE* f) {
	Produs p;
	fscanf(f, "%d", &p.cod);
	char buffer[50];
	fscanf(f, "%s", buffer);
	p.denumire = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	strcpy(p.denumire, buffer);
	fscanf(f, "%d", &p.stoc);
	fscanf(f, "%d", &p.prag_alerta);
	fscanf(f, "%f", &p.pret);
	return p;
}

void afisareProdus(Produs p) {
	printf("\n Produs codul %d, are denumirea %s, mai sunt in stoc %d produse, pragul de alerta este %d, iar pretul unui produs este %5.2f", p.cod, p.denumire, p.stoc, p.prag_alerta, p.pret);
}

//ex2
void afisareCod(Produs p) {
	printf("%d", p.cod);
}
typedef struct Nod {
	Produs info;
	struct Nod* prev;
	struct Nod* next;
}Nod;

Nod* creareNod(Produs info, Nod* prev, Nod* next) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = creareProdus(info.cod, info.denumire, info.stoc, info.prag_alerta, info.pret);
	nou->prev = prev;
	nou->next = next;
	return nou;

}

typedef  struct LDI {
	Nod* prim;
	Nod* ultim;
}LDI;

LDI inserareInceput(LDI lista, Produs p) {
	Nod* nou = creareNod(p, NULL, NULL);
	if (lista.prim) {
		nou->next = lista.prim;
		lista.prim->prev = nou;
		lista.prim = nou;
	}
	else {
		lista.prim = lista.ultim = nou;
	}
	return lista;

}

LDI inserareFinal(LDI lista, Produs p) {
	Nod* nou = creareNod(p, NULL, NULL);
	if (lista.prim) {
		nou->prev = lista.ultim;
		lista.ultim->next = nou;
		lista.ultim = nou;

	}
	else {
		lista.prim = lista.ultim = nou;
	}
	return lista;
}

void afisareInceputFinal(LDI lista) {
	if (lista.prim) {
		Nod* p = lista.prim;
		while (p) {
			afisareProdus(p->info);
			p = p->next;

		}
	}

}

void afisareFinalInceput(LDI lista) {
	if (lista.prim) {
		Nod* p = lista.ultim;
		while (p) {
			afisareProdus(p->info);
			p = p->prev;
		}
	}
}

LDI dezalocareLista(LDI lista) {
	while (lista.prim) {
		Nod* p = lista.prim;
		lista.prim = lista.prim->next;
		free(p->info.denumire);
		free(p);
	}
	lista.ultim = NULL;
	return lista;
}

LDI citireListaDinFisier(FILE* f) {
	LDI lista;
	lista.prim = lista.ultim = NULL;
	int nr = 0;
	fscanf(f, "%d", &nr);
	for (int i = 0; i < nr; i++) {
		lista = inserareInceput(lista, citireProdus(f));
	}
	return lista;
}

//ex2
void afisareCodInceputFinal(LDI lista) {
	Nod* p = lista.prim;//10 5 9 
	while (p) {
		afisareCod(p->info);
		if (p->next != NULL) {
			printf(" -> ");
		}
		p = p->next;
	}
	printf("\n");
}

//ex2
void afisareCodFinalInceput(LDI lista) {
	Nod* p = lista.ultim;
	while (p) {
		afisareCod(p->info);
		if (p->prev != NULL) {
			printf(" -> ");
		}
		p = p->prev;
	}
	printf("\n");
}
//ex 3
float calculeazaIncasari(LDI lista) {
	float totalIncasari = 0.0;
	Nod* p = lista.prim;
	while (p) {
		totalIncasari += p->info.stoc * p->info.pret;
		p = p->next;
	}
	return totalIncasari;
}


//ex 4
//int areNevoieDeAprovizionare(LDI lista, char* denumire) {
//	Nod* p = lista.prim;
//	while (p) {
//		if (strcmp(p->info.denumire, denumire) == 0) {
//			if (p->info.stoc < p->info.prag_alerta) {
//				return 1; // produsul are nevoie de aprovizionare
//			}
//			else {
//				return 0; // produsul nu are nevoie de aprovizionare
//			}
//		}
//		p = p->next;
//	}
//	return -1; // produsul nu a fost gasit in lista
//}

//tot ex 4 alta varianta
void verificareAprovizionare(LDI lista,const char* denumire) {
	//char denumire[50];
	//printf("Introduceti numele produsului: ");
	//fgets(denumire, 50, stdin); // citeste denumirea produsului de la tastatura
	//strtok(denumire, "\n"); // elimina caracterul newline ('\n') din sirul citit      //fara linia asta imi zice niciun produs nu exista pe stoc

	Nod* p = lista.prim;
	if (p) {
		while (p) {
			if (strcmp(p->info.denumire, denumire) == 0) { // daca numele produsului coincide cu cel introdus
				if (p->info.stoc < p->info.prag_alerta) { // daca stocul produsului este mai mic decat pragul de alerta
					printf("Produsul %s are nevoie de aprovizionare\n", denumire);
				}
				else {
					printf("Produsul %s nu are nevoie de aprovizionare\n", denumire);
				}
				return;
			}
			p = p->next;
		}
		printf("Produsul %s nu exista pe stoc\n", denumire); // daca produsul nu a fost gasit in lista
	}
	else {
		printf("\n nu exista lista");
	}
}

LDI AdaugaAdaos(LDI lista, int nr) {
	if (lista.prim) {
		Nod* p = lista.prim;
		while (p) {
			if (p->info.stoc < nr) {
				p->info.pret *= 1.5;
			}
			p = p->next;
		}
	}
	return lista;
}
int NrProduseCuStocSubPrag(LDI lista) {
	int nr = 0;
	if (lista.prim) {
		Nod* p = lista.prim;
		while (p) {
			if (p->info.stoc < p->info.prag_alerta) {
				nr++;
			}
			p = p->next;
		}
	}
	return nr;
}
Produs* puneinvector(LDI lista) {
	int nr = NrProduseCuStocSubPrag(lista);
	Produs* vector = (Produs*)malloc(sizeof(Produs) * nr);
	int contor = 0;
	if (lista.prim) {
		Nod* p = lista.prim;
		while (p) {
			if (p->info.stoc < p->info.prag_alerta) {
				vector[contor++] = p->info;
				//contor++;
			}
			p = p->next;
		}
	}
	return vector;
}
void main() {
	LDI lista;
	lista.prim = lista.ultim = NULL;

	lista = inserareInceput(lista, creareProdus(54, "apa", 9, 10, 3.4)); //are nevoie
	lista = inserareInceput(lista, creareProdus(45, "paine", 100, 94, 2.4)); //nu are nevoie
	lista = inserareInceput(lista, creareProdus(12, "lapte", 45, 30, 7.3)); //are nevoie
	lista = inserareInceput(lista, creareProdus(13, "mustar", 60, 65, 12.5)); //are nevoie
	lista = inserareInceput(lista, creareProdus(7, "suc", 3, 10, 5)); //are nevoie
	printf("----Afisare lista inceput final----\n");
	afisareInceputFinal(lista);
	printf("\n");
	printf("\n----Afisare lista final inceput----\n");
	afisareFinalInceput(lista);

	printf("\n\n----Ex 3----");
	float incasariTotale = calculeazaIncasari(lista);
	printf("\nIncasari totale: %5.2f", calculeazaIncasari(lista));
	printf("\n\n----Ex 2----\n ");
	afisareCodFinalInceput(lista);
	printf("\n");
	afisareCodInceputFinal(lista);

	/*printf("\n\n----Ex 4----\n");
	if (areNevoieDeAprovizionare(lista, "apa")) {
		printf("Produsul 'apa' are nevoie de aprovizionare.\n");
	}
	else {
		printf("Produsul 'apa' nu are nevoie de aprovizionare.\n");
	}*/

	//FILE* f = fopen("Produse.txt", "r");
	//LDI lista2 = citireListaDinFisier(f);
	//printf("\n----Citire din fisier----");
	//afisareInceputFinal(lista2);
	//printf("\n");
	printf("\n\n----Ex 4----\n");
	verificareAprovizionare(lista,"apa");
	verificareAprovizionare(lista,"apsaka");
	printf("\n\n----Ex 6----\n");
	lista = AdaugaAdaos(lista, 20);
	afisareInceputFinal(lista);
	printf("\n\n----Ex 5----\n");
	int nr = NrProduseCuStocSubPrag(lista);
	Produs* vector = puneinvector(lista);
	for (int i = 0; i < nr; i++) {
		afisareProdus(vector[i]);
	}
}


//cum fac sa afiseze codurile din fisierul text?