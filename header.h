#define _CRT_SECURE_NO_WARNINGS
#ifndef HEADER_H
#define HEADER_H

typedef struct
{
	int id;
	int cijena;
	char marka[50];
	char imeProizvoda[50];
}PROIZVOD;

enum menu
{
	DODAVANJE_PROIZVODA = 1,
	ISPIS_PROIZVODA = 2,
	TRAZENJE_KATEGORIJA = 3,
	SORTIRANJE_CIJENA = 4,
	BRISANJE_PROIZVODA = 5,
	EXIT_3 = 6,
	AZURIRANJE_PROIZVODA = 7,
};
enum menuPretrazivanje
{
	PRETRAZIVANJE_ID = 1,
	PRETRAZIVANJE_MARKA = 2,
	PRETRAZIVANJE_IMENA = 3,
	PRETRAZIVANJE_CIJENA = 4,
	EXIT_1 = 5,
};
enum menuSortiranje
{
	SORT_UZL = 1,
	SORT_SIL = 2,
	EXIT_2 = 3,
};

extern int praviBrojProizvoda; // prati koliko je proizvoda dodano u povijesti cijelog programa
int menu();
void kreiranjeDat();
int menuPretrazivanja();
int menuSortiranja();
int generiranjeID();
void dodavanjeProizvoda();
void* ucitavanjeProizvoda();
void azuriranjeProizvoda(PROIZVOD* polje);
void ispis(PROIZVOD*);
void* pretrazivanjeID(PROIZVOD*);
void* pretrazivanjeMarka(PROIZVOD*);
void* pretrazivanjeImena(PROIZVOD*);
void* pretrazivanjeCijena(PROIZVOD*);
void subZaSortSil(PROIZVOD*, PROIZVOD*);
void subZaSortUzl(PROIZVOD*, PROIZVOD*);
void SortCijenaUzl(PROIZVOD*);
void SortCijenaSil(PROIZVOD*);
void brisanjeProizvoda(PROIZVOD*);
void izlaz(PROIZVOD*);
int compareCijenaUzl(const void* a, const void* b);
int compareCijenaSil(const void* a, const void* b);

#endif
