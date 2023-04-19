#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

typedef struct
{
	char* numeCandidat;
	char* programStudiu;
	float mediaBac;
	int codDosar;
}dosarCandidat;

typedef struct
{
	dosarCandidat inf;
	struct nodLS* next;
} nodLS;

typedef struct
{
	struct nodLS** vect;
	int nrElem;
} hashT;


int functieDispersieNume(const char numeCandidat[20], hashT tabela)
{
	return numeCandidat[0] % tabela.nrElem;
}


void inserareHashTable(hashT tabela, dosarCandidat s)
{
	if (tabela.vect != NULL)
	{
		//int pozitie = functieDispersie(tabela, s.nrGrupa);
		int pozitie = functieDispersieNume(s.numeCandidat, tabela);
		nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
		nou->inf.numeCandidat = (char*)malloc((strlen(s.numeCandidat) + 1) * sizeof(char));
		strcpy(nou->inf.numeCandidat, s.numeCandidat);
		nou->inf.programStudiu = (char*)malloc((strlen(s.programStudiu) + 1) * sizeof(char));
		strcpy(nou->inf.programStudiu, s.programStudiu);
		nou->inf.mediaBac = s.mediaBac;
		nou->inf.codDosar = s.codDosar;
		nou->next = NULL;
		if (tabela.vect[pozitie] == NULL)
			tabela.vect[pozitie] = nou;
		else
		{
			nodLS* temp = tabela.vect[pozitie];
			while (temp->next)
				temp = temp->next;
			temp->next = nou;
		}
	}
}

void traversareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp)
	{
		printf("\n Candidatul : %s  \n Programul de studiu : %s \n Media bac : %5.2f \n Cod dosar : %d",
			temp->inf.numeCandidat,temp->inf.programStudiu,temp->inf.mediaBac,temp->inf.codDosar);
		temp = temp->next;
	}
}

void traversareHashTable(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.nrElem; i++)
		{
			if (tabela.vect[i] != NULL)
			{
				printf("\nPozitie=%d", i);
				traversareLS(tabela.vect[i]);
			}
		}
	}
}

void dezalocareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp)
	{
		nodLS* temp2 = temp->next;
		free(temp->inf.numeCandidat);
		free(temp->inf.programStudiu);
		free(temp);
		temp = temp2;
	}
}

void dezalocareHashTable(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.nrElem; i++)
			if (tabela.vect[i] != NULL)
				dezalocareLS(tabela.vect[i]);
	}
	free(tabela.vect);
}

void main()
{
	int nrStud;
	hashT tabela;
	tabela.nrElem = 11;
	tabela.vect = (nodLS**)malloc(tabela.nrElem * sizeof(nodLS*));
	for (int i = 0; i < tabela.nrElem; i++)
		tabela.vect[i] = NULL;

	char buffer[20];
	char buffer1[20];
	dosarCandidat s;
	FILE* f = fopen("dosare.txt", "r");
	fscanf(f, "%d", &nrStud);
	for (int i = 0; i < nrStud; i++)
	{
		fscanf(f, "%s", buffer);
		s.numeCandidat = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.numeCandidat, buffer);	
		fscanf(f, "%s", buffer1);
		s.programStudiu = (char*)malloc((strlen(buffer1) + 1) * sizeof(char));
		strcpy(s.programStudiu, buffer1);
		fscanf(f, "%f", &s.mediaBac);
		fscanf(f, "%d", &s.codDosar);
		inserareHashTable(tabela, s);
		free(s.numeCandidat);
		free(s.programStudiu);
	}
	fclose(f);
	traversareHashTable(tabela);
	dezalocareHashTable(tabela);
}