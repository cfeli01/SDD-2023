#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct Proiect {
	unsigned int cod;
	char* titlu;
	char* benefeciar;
	unsigned char nrExecutanti;
	float buget;
}Proiect;

Proiect creareProiect(unsigned int cod, const char* titlu, const char* benefeciar, unsigned char nrExecutanti, float buget) {
	Proiect p;
	p.cod = cod;
	p.titlu = (char*)malloc(sizeof(char) * strlen(titlu) + 1);
	strcpy(p.titlu, titlu);
	p.benefeciar = (char*)malloc(sizeof(char) * strlen(benefeciar) + 1);
	strcpy(p.benefeciar, benefeciar);
	p.nrExecutanti = nrExecutanti;
	p.buget = buget;
	return p;
}

Proiect citiredinfisier(FILE* f) {
	Proiect p;
	char buffer[50];
	char buffer2[50];
	fscanf(f, "%d", &p.cod);
	fscanf(f, "%s", buffer);
	p.titlu = (char*)malloc(sizeof(char) * strlen(buffer) + 1);
	strcpy(p.titlu, buffer);
	fscanf(f, "%s", buffer2);
	p.benefeciar = (char*)malloc(sizeof(char) * strlen(buffer2) + 1);
	strcpy(p.benefeciar, buffer2);
	fscanf(f, "%s", &p.nrExecutanti);
	fscanf(f, "%f", &p.buget);
	return p;
}

void afisareProiect(Proiect p) {
	printf("\n Cod : %d , titlu : %s , beneficiar : %s , nr Executanti : %c , buget: %5.2f", p.cod, p.titlu, p.benefeciar, p.nrExecutanti, p.buget);
}

typedef struct Nod {
	Proiect info;
	struct Nod* prev;
	struct Nod* next;
}Nod;

Nod* creareNod(Proiect info, Nod* prev, Nod* next) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = creareProiect(info.cod,info.titlu,info.benefeciar,info.nrExecutanti,info.buget);
	nou->prev = prev;
	nou->next = next;
	return nou;
}

typedef struct LDI {
	Nod* prim;
	Nod* ultim;
}LDI;

LDI inserareInceput(LDI lista, Proiect p) {
	Nod* nou = creareNod(p, NULL, NULL);
	if (lista.prim) {
		nou->next = lista.prim;
		lista.prim->prev = nou;
		lista.prim = nou;
	}
	else {
		lista.prim=lista.ultim = nou;
	}
	return lista;
}

LDI inserareFinal(LDI lista, Proiect p) {
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
			afisareProiect(p->info);
			p = p->next;
		}
	}
}

void afisareFinalInceput(LDI lista) {
	if (lista.prim) {
		Nod* p = lista.ultim;
		while (p) {
			afisareProiect(p->info);
			p = p->prev;
		}
	}
}

LDI dezalocareLDI(LDI lista){
	while (lista.prim) {
		Nod* aux = lista.prim;
		lista.prim = lista.prim->next;
		free(aux->info.titlu);
		free(aux->info.benefeciar);
		free(aux);
	}
	lista.ultim = NULL;
	return lista;
}

LDI citirelistadinfisier(FILE* f) {
	LDI lista;
	lista.prim = lista.ultim = NULL;
	int nr = 0;
	fscanf(f, "%d", &nr);
	for (int i = 0; i < nr; i++) {
		lista = inserareInceput(lista, citiredinfisier(f));
	}
	return lista;
}

void cautareBugetDupabeneficiar(LDI lista, const char* beneficiar) {
	if (lista.prim) {
		Nod* p = lista.prim;
		while (p && strcmp(p->info.benefeciar, beneficiar) != 0) {
			p = p->next;
		}
		if (p) {
			afisareProiect(p->info);
		}
		else {
			return -1;
		}
	}
	else {
		return-1;
	}
}
Proiect cautareProiectDupaBuget(LDI lista, float buget) {
	if (lista.prim) {
		Nod* p = lista.prim;
		while (p && p->info.buget != buget) {
			p = p->next;
		}
		if (p) {
			return p->info;
		}
		else { 
			return creareProiect(-1, -1, "","", - 1);
		}
	}
	else {
		return creareProiect(-1, -1, "","", - 1);
	}
}

float calculeazaBugetTotalExecutanti(LDI lista) {
	float bugettotal = 0.0;
	Nod* p = lista.prim;
	while (p) {
		bugettotal += p->info.buget * p->info.cod; //merge mai mult stoc*pret
		p = p->next;
	}
	return bugettotal;
}



void main() {
	//Nadin,Alex, Anatolie
	LDI lista;
	lista.prim = lista.ultim = NULL;
	lista = inserareInceput(lista, creareProiect(1, "Automobile", "Alex", '1', 5000));
	lista = inserareInceput(lista, creareProiect(2, "Biciclete", "Nadin", '2', 1999.9));
	lista = inserareFinal(lista, creareProiect(3, "Trotinete", "Anatolie", '1', 1000));
	printf("Afisare lista Inceput Final :");
	afisareInceputFinal(lista);
	printf("\n \n Afisare lista Inceput Final :");
	afisareFinalInceput(lista);
	printf("\n Afisare lista dupa dezalocare :");
	lista = dezalocareLDI(lista);


	FILE* f = fopen("produse.txt", "r");
	LDI lista1;
	lista1.prim = lista1.ultim = NULL;
	lista1 = citirelistadinfisier(f);
	printf("\n \n Afisare lista Inceput Final cu citirea datelor din FISIER:");
	afisareInceputFinal(lista1);

	printf("\n \n Afisare cautare buget dupa Beneficiar");
	cautareBugetDupabeneficiar(lista1, "Andrei");
	
	printf("\n \n Afisare cautare proiect dupa un buget dat ca parametru");
	afisareProiect(cautareProiectDupaBuget(lista1, 100));

	float buget = calculeazaBugetTotalExecutanti(lista1);
	printf(" \n Bugetul total pentru toti executantii este: %5.2f", buget);
	

	printf("\n Afisare lista dupa dezalocare :");
	lista1 = dezalocareLDI(lista1);
	fclose(f);


}