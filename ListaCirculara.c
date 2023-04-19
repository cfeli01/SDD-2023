#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct Rezervare
{
	unsigned int id;
	char* denumire_hotel;
	unsigned char nr_camere_rezervate;//0-9
	char* nume_client;//abc
	char* perioada_rezervarii;
	float suma_de_plata;

}Rezervare;

Rezervare creareRezervare(unsigned int id, const char* denumire_hotel, unsigned char nr_camere_rezervate, const char* nume_client, const char* perioada_rezervarii, float suma_de_plata)
{
	Rezervare r;
	r.id = id;
	r.denumire_hotel = (char*)malloc(sizeof(char) * (strlen(denumire_hotel) + 1));
	strcpy(r.denumire_hotel, denumire_hotel);
	r.nr_camere_rezervate = nr_camere_rezervate;
	r.nume_client = (char*)malloc(sizeof(char) * (strlen(nume_client) + 1));
	strcpy(r.nume_client, nume_client);
	r.perioada_rezervarii = (char*)malloc(sizeof(char) * (strlen(perioada_rezervarii) + 1));
	strcpy(r.perioada_rezervarii, perioada_rezervarii);
	r.suma_de_plata = suma_de_plata;
	return r;
}
void afisareRezervare(Rezervare rez)
{
	printf("\nRezervarea cu id-ul %d in hotelul %s are %c camere rezervate, %s este clientul, care a rezervat in perioada %s si are de plata %5.2f", rez.id, rez.denumire_hotel, rez.nr_camere_rezervate, rez.nume_client, rez.perioada_rezervarii, rez.suma_de_plata);
}

typedef struct Nod
{
	Rezervare info;
	struct Nod* next;
	struct Nod* prev;
}Nod;
Nod* creareNod(Rezervare r, Nod* next, Nod* prev)
{
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->info = creareRezervare(r.id, r.denumire_hotel, r.nr_camere_rezervate, r.nume_client, r.perioada_rezervarii, r.suma_de_plata);
	nod->next = next;
	nod->prev = prev;
	return nod;
}
typedef struct DLL
{
	Nod* prim;
	Nod* ultim;
}DLL;

DLL inserareInceput(DLL lista, Rezervare r)
{
	Nod* nou = creareNod(r, NULL, NULL);
	if (lista.prim)
	{
		nou->next = lista.prim;
		lista.prim->prev = nou;
		lista.prim = nou;
	}
	else
	{
		lista.prim = lista.ultim = nou;
		
	}
	return lista;
}
DLL inserareFinal(DLL lista, Rezervare r)
{
	Nod* nou = creareNod(r, NULL, NULL);
	if (lista.ultim)
	{
		nou->prev = lista.ultim;
		lista.ultim->next = nou;
		lista.ultim = nou;
	}
	else
	{
		lista.prim = lista.ultim = nou;
		
	}
	return lista;
}

void afisareInceputFinal(DLL lista)
{
	if (lista.prim)
	{
		afisareRezervare(lista.prim->info);
		Nod* aux = lista.prim->next;

		while (aux!=lista.prim)
		{
			afisareRezervare(aux->info);
			aux = aux->next;
		}
	}
}
void afisareFinalInceput(DLL lista)
{
	if (lista.ultim)
	{
		afisareRezervare(lista.ultim->info);
		Nod* aux = lista.ultim->prev;
		while (aux!=lista.ultim)
		{
			afisareRezervare(aux->info);
			aux = aux->prev;
		}
	}
}

void dezalocareListaDubla(DLL* lista)
{
	if ((*lista).prim)
	{
		while ((*lista).prim)
		{
			Nod* aux = (*lista).prim;
			(*lista).prim = (*lista).prim->next;
			free(aux->info.denumire_hotel, aux->info.nume_client, aux->info.perioada_rezervarii);
			free(aux);
		}
		(*lista).ultim = NULL;
	}
}
DLL inserareInceputListaDublaCirculara(DLL lista, Rezervare r)
{
	Nod* nou = creareNod(r, NULL, NULL);
	if (lista.prim) {
		nou->next = lista.prim;
		lista.prim->prev = nou;
		lista.ultim->next = nou;
		nou->prev = lista.ultim;
		lista.prim = nou;
	}
	else {
		lista.prim = lista.ultim = nou;
		nou->prev = nou;
		nou->next = nou;
	}
	return lista;
}

DLL inserareFinalListaDublaCirculara(DLL lista, Rezervare r)
{
	Nod* nou = creareNod(r, NULL, NULL);

	if (lista.ultim) {
		nou->next = lista.prim;
		lista.ultim->next = nou;
		lista.prim->prev = nou;
		nou->prev = lista.ultim;
		lista.ultim = nou;
	}
	else {
		lista.prim = lista.ultim = nou;
		nou->prev = nou;
		nou->next = nou;
	}
	return lista;
}
void afisareListaDublaCircularaInceputFinal(DLL cap)
{
	if (cap.prim) {
		afisareRezervare(cap.prim->info);
		Nod* aux = cap.prim->next;
		while (aux != cap.prim) {
			afisareRezervare(aux->info);
			aux = aux->next;
		}
	}
}
void afisareListaDublaCircularaFinalInceput(DLL cap) {
	if (cap.ultim) {
		afisareRezervare(cap.ultim->info);
		Nod* aux = cap.ultim->prev;
		while (aux != cap.ultim) {
			afisareRezervare(aux->info);
			aux = aux->prev;
		}
	}
}
float InacasariPotentiale(DLL list, const char* data) {
	float total = 0;
	if (list.prim) {
		if (strcmp(list.prim->info.perioada_rezervarii, data) == 0) {
			int nr = list.prim->info.nr_camere_rezervate - '0';//'0' =48  50-48 50-'0'
			total += nr * list.prim->info.suma_de_plata;
		}
		Nod* p = list.prim->next;
		while (p!=list.prim) {
			if (strcmp(p->info.perioada_rezervarii, data) == 0) {
				int nr = p->info.nr_camere_rezervate-'0';//'0' =48  50-48 50-'0'
				total += nr * p->info.suma_de_plata;
			}
			p = p->next;
		}
	}
	return total;
	
}
int NrCamere(DLL list, const char* hotel) {
	int total = 0;
	if (list.prim) {
		if (strcmp(list.prim->info.denumire_hotel, hotel) == 0) {
			int nr = list.prim->info.nr_camere_rezervate - '0';//'0' =48  50-48 50-'0'
			total += nr;
		}
		Nod* p = list.prim->next;
		while (p != list.prim) {
			if (strcmp(p->info.denumire_hotel, hotel) == 0) {
				int nr = p->info.nr_camere_rezervate - '0';//'0' =48  50-48 50-'0'
				total += nr;
			}
			p = p->next;
		}
	}
	return total;

}
int returnareluna(Rezervare r) {
	int luna = 0;

	luna = 10 * (r.perioada_rezervarii[3]-'0') + (r.perioada_rezervarii[4]-'0');
	return luna;
}
void afisarelunileRezervarilor(DLL cap)
{
	if (cap.prim) {
		printf(" %d", returnareluna(cap.prim->info));
		Nod* aux = cap.prim->next;
		while (aux != cap.prim) {
			printf(" %d", returnareluna(aux->info));
			aux = aux->next;
		}
	}
}
void main()
{
	//DLL lista;
	//lista.prim = lista.ultim = NULL;
	////conteaza daca pun inserareInceput sau inserareFinal?
	//lista = inserareInceput(lista, creareRezervare(100, "Hotel1", 2,"Popescu Ion", "20 martie-22 martie", 100));
	//lista = inserareInceput(lista, creareRezervare(101, "Hotel2", 4, "Radu Ana", "12 feb-15 feb", 933.66));
	//lista = inserareInceput(lista, creareRezervare(102, "Hotel3", 1, "Iancu Vladd", "23 apr-26 apr", 232.76));
	//lista = inserareFinal(lista, creareRezervare(103, "Hotel4", 3, "Pavel Maria", "5 iun-7 iun", 500.2));
	//lista = inserareFinal(lista, creareRezervare(104, "Hotel5", 1, "Ionescu Denisa", "1 aug-4 aug", 235.7));
	//printf("\n Afisare lista dubla inceput -> final: ");
	//afisareInceputFinal(lista);
	//printf("\n");
	//printf("\n Afisare lista dubla final -> inceput: ");
	//afisareFinalInceput(lista);
	//printf("\n");
	DLL list;
	list.prim = list.ultim = NULL;
	//"20.03.2022-23.03.2022";
	list = inserareInceputListaDublaCirculara(list, creareRezervare(100, "Hotel1", '2', "Popescu Ion", "20.03.2022", 100));
	list = inserareInceputListaDublaCirculara(list, creareRezervare(101, "Hotel2", '4', "Radu Ana", "20.03.2022", 933.66));
	list = inserareInceputListaDublaCirculara(list, creareRezervare(102, "Hotel3", '1', "Iancu Vladd", "20.03.2022", 232.76));
	list = inserareInceputListaDublaCirculara(list, creareRezervare(103, "Hotel4", '3', "Pavel Maria", "20.12.2022", 500.2));
	list = inserareInceputListaDublaCirculara(list, creareRezervare(104, "Hotel5", '1', "Ionescu Denisa", "20.03.2022", 200.8));

	list = inserareFinalListaDublaCirculara(list, creareRezervare(104, "Hotel5", '1', "Ionescu Denisa", "20.03.2022", 200.8));
	list = inserareFinalListaDublaCirculara(list, creareRezervare(104, "Hotel5", '1', "Ionescu Denisa", "20.03.2022", 200.8));
	list = inserareFinalListaDublaCirculara(list, creareRezervare(104, "Hotel5", '1', "Ionescu Denisa", "20.03.2022", 200.8));
	list = inserareFinalListaDublaCirculara(list, creareRezervare(104, "Hotel5", '1', "Ionescu Denisa", "20.03.2022", 200.8));
	list = inserareFinalListaDublaCirculara(list, creareRezervare(104, "Hotel5", '1', "Ionescu Denisa", "20.03.2022", 200.8));

	printf("\n---- Ex 2 ---- Afisare lista dubla circulara inceput - final: ");
	afisareListaDublaCircularaInceputFinal(list);
	printf("\n");
	printf("\n ---- Ex 3 ---- Afisare lista dubla circulara final - inceput: ");
	afisareListaDublaCircularaFinalInceput(list);

	printf("\n ---- Ex 4 ----  ");
	printf("\n incasari la o data %5.2f", InacasariPotentiale(list, "20.03.2022"));


	printf("\n ---- Ex 5 ----  ");
	printf("\n nr camere la un anumit hotel %d", NrCamere(list,"Hotel5"));
	afisarelunileRezervarilor(list);
}

//la ex 2 doar functia de inserare? si o functie de afisare a inserarilor?
//la ex 3 functia de afisare inversa fata de ex 2?
