#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "time.h"

static int brojProizvoda = 0;
static int brojac = 0;
static int i, j;
int praviBrojProizvoda = 0;

// Izbornik / podizbornici
int menu()
{
	int izbor = 0;

	static PROIZVOD* polje = NULL;

	printf("\nIzaberite opciju:\n");
	printf("| 1.	Dodavanje proizvoda             |\n");
	printf("| 2.	Ispis proizvoda                 |\n");
	printf("| 3.	Trazenje po kategoriji          |\n");
	printf("| 4.	Sortiranje proizvoda po cijeni  |\n");
	printf("| 5.	Brisanje proizvoda              |\n");
	printf("| 6.	Izlaz iz programa               |\n");

	scanf("%d", &izbor);
	if (izbor != 1)
	{
		system("cls");
		printf("Pogresan unos!\n");
		scanf("%*[^\n]");
	}
	system("cls");

	switch (izbor)
	{
	case DODAVANJE_PROIZVODA:

		ucitavanjeProizvoda();
		if (brojProizvoda == 0)
		{
			kreiranjeDat();
		}
		dodavanjeProizvoda(polje);
		break;

	case ISPIS_PROIZVODA:

		if (polje != NULL)
		{
			free(polje);
			polje = NULL;
		}
		polje = (PROIZVOD*)ucitavanjeProizvoda();
		if (brojProizvoda == 0)
		{
			printf("Nema proizvoda!\n");
		}
		else
		{
			ispis(polje);
		}
		break;

	case TRAZENJE_KATEGORIJA:

		ucitavanjeProizvoda();
		if (brojProizvoda == 0)
		{
			printf("Nema proizvoda!\n");
			break;
		}
		while (izbor != 997)
		{
			izbor = menuPretrazivanja();
		}
		break;

	case SORTIRANJE_CIJENA:

		ucitavanjeProizvoda();
		if (brojProizvoda == 0)
		{
			printf("Nema proizvoda!\n");
			break;
		}
		while (izbor != 998)
		{
			izbor = menuSortiranja();
		}
		break;

	case BRISANJE_PROIZVODA:

		polje = (PROIZVOD*)ucitavanjeProizvoda();
		if (brojProizvoda == 0)
		{
			printf("Nema proizvoda.\n");
		}
		else
		{
			brisanjeProizvoda(polje);
		}
		break;

	case EXIT_3:

		izlaz(polje);
		return 999;
		break;

	default:

		printf("Pogresan unos! Pokusajte ponovno\n");

	}
	return izbor;
}

void dodavanjeProizvoda()
{
	FILE* fp = NULL;
	fp = fopen("proizvodi.bin", "rb+");
	if (fp == NULL)
	{
		perror("Dodavanje");
	}
	fread(&brojProizvoda, sizeof(int), 1, fp);
	printf("Trenutni broj proizvoda: %d\n", brojProizvoda);
	printf("Ukupan broj dodanih proizvoda: %d\n----------------------------------\n", praviBrojProizvoda);

	PROIZVOD proizvod;
	proizvod.id = generiranjeID();
	brojac++;

	getchar();
	printf("Unesite ime marke: ");
	scanf("%24[^\n]", proizvod.marka);
	getchar();
	printf("Unesite ime proizvoda: ");
	scanf("%30[^\n]", proizvod.imeProizvoda);
	getchar();
	printf("Unesite cijenu proizvoda: ");
	if (scanf("%d", &proizvod.cijena) != 1)
	{
		printf("Neispravan unos cijene.\n");
		fclose(fp);
		return;
	}
	getchar();

	system("cls");

	fseek(fp, sizeof(PROIZVOD) * brojProizvoda, SEEK_CUR);
	fwrite(&proizvod, sizeof(PROIZVOD), 1, fp);
	rewind(fp);
	brojProizvoda++;
	praviBrojProizvoda++;
	fwrite(&brojProizvoda, sizeof(int), 1, fp);

	fclose(fp);
}

void ispis(PROIZVOD* polje)
{
	for (i = 0; i < brojProizvoda; i++)
	{
		printf("\nID: %d  Ime marke :%s  Ime proizvoda:%s  Cijena: %d\n", (polje + i)->id, (polje + i)->marka, (polje + i)->imeProizvoda, (polje + i)->cijena);
	}
}

int menuPretrazivanja()
{
	int izbor = 0;
	PROIZVOD* polje = NULL;
	polje = (PROIZVOD*)ucitavanjeProizvoda();

	printf("\nPretrazivanje po:\n");
	printf("| 1. ID-u						|\n");
	printf("| 2. Imenu tvrtke/marke			|\n");
	printf("| 3. Imenu proizvode			|\n");
	printf("| 4. Cijeni					    |\n");
	printf("| 5. Povratak					|\n");

	scanf("%d", &izbor);
	if (izbor != 1)
	{
		system("cls");
		printf("Pogresan unos!\n");
		scanf("%*[^\n]");
	}

	system("cls");

	switch (izbor)
	{
	case PRETRAZIVANJE_ID:

		pretrazivanjeID(polje);
		break;

	case PRETRAZIVANJE_MARKA:

		pretrazivanjeMarka(polje);
		break;

	case PRETRAZIVANJE_IMENA:

		pretrazivanjeImena(polje);
		break;

	case PRETRAZIVANJE_CIJENA:

		pretrazivanjeCijena(polje);
		break;

	case EXIT_1:

		return 997;

	default: printf("Odabrali ste pogresan broj!\nMolim pokusajte ponovno.\n");

	}
	return izbor;
}

int menuSortiranja()
{
	int izbor = 0;
	PROIZVOD* polje = NULL;
	polje = (PROIZVOD*)ucitavanjeProizvoda();

	printf("\nSortiranje po:                                                          \n\n");
	printf("| 1. Cijeni uzlazno      |\n");
	printf("| 2. Cijeni silazno      |\n");
	printf("| 3. Povratak            |\n");

	scanf("%d", &izbor);
	if (izbor != 1)
	{
		system("cls");
		printf("Pogresan unos!\n");
		scanf("%*[^\n]");
	}

	system("cls");

	switch (izbor)
	{
	case SORT_UZL:

		SortCijenaUzl(polje);
		break;

	case SORT_SIL:

		SortCijenaSil(polje);
		break;

	case EXIT_2:

		return 998;
	}
	return izbor;
}

void kreiranjeDat()
{
	FILE* fp = NULL;
	fp = fopen("proizvodi.bin", "wb");

	if (fp == NULL)
	{
		perror("Kreiranje");
	}

	fwrite(&brojProizvoda, sizeof(int), 1, fp);

	fclose(fp);
}

int generiranjeID()
{
	static int brojac = 1;
	int ID = brojac;
	brojac++;
	return ID;
}

void* ucitavanjeProizvoda()
{
	FILE* fp = fopen("proizvodi.bin", "rb");
	if (fp == NULL)
	{
		return NULL;
	}

	fread(&brojProizvoda, sizeof(int), 1, fp);

	// koristiti dinamicko zauzimanje memorije za bilo koji tip podatka...
	// koristiti funkcije malloc(), calloc(), realloc(), free()
	PROIZVOD* polje = NULL;
	polje = (PROIZVOD*)calloc(brojProizvoda, sizeof(PROIZVOD));
	if (polje == NULL)
	{
		perror("Zauzimanje memorije");
		return NULL;
	}

	fread(polje, sizeof(PROIZVOD), brojProizvoda, fp);

	fclose(fp);

	return polje;
}

void* pretrazivanjeID(PROIZVOD* polje)
{
	int trazenID, brojac = 0;

	printf("Unesite broj ID-a kojeg trazite:\n");
	scanf("%d", &trazenID);
	if (trazenID != 1)
	{
		system("cls");
		printf("Pogresan unos!\n");
		scanf("%*[^\n]");
	}

	for (i = 0; i < brojProizvoda; i++)
	{
		if (trazenID == (polje + i)->id)
		{

			printf("\nID: %d  Ime marke : % s  Ime proizvoda : % s  Cijena : % d\n", (polje + i)->id, (polje + i)->marka, (polje + i)->imeProizvoda, (polje + i)->cijena);
			brojac++;
		}
	}
	if (brojac == 0)
	{
		printf("\nTrazen ID nije pronadjen.\n");
	}
	return NULL;
}


void* pretrazivanjeMarka(PROIZVOD* polje)
{
	char trazenaMarka[50];
	int brojac = 0;

	printf("Upisite ime marku trazenog proizvoda:\n");
	getchar();
	scanf("%49[^\n]", trazenaMarka);

	for (i = 0; i < brojProizvoda; i++)
	{
		if (!strcmp(trazenaMarka, (polje + i)->marka))
		{

			printf("\nID: %d  Ime marke : % s  Ime proizvoda : % s  Cijena : % d\n", (polje + i)->id, (polje + i)->marka, (polje + i)->imeProizvoda, (polje + i)->cijena);
			brojac++;
		}
	}
	if (brojac == 0)
	{
		printf("\nMarka nije pronadjena.\n");
	}
	return NULL;
}


void* pretrazivanjeImena(PROIZVOD* polje)
{
	char trazenProizvod[50];
	int brojac = 0;

	printf("Upisite ime proizvoda kojeg trazite:\n");
	getchar();
	scanf("%49[^\n]", trazenProizvod);

	for (i = 0; i < brojProizvoda; i++)
	{
		if (!strcmp(trazenProizvod, (polje + i)->imeProizvoda))
		{

			printf("\nID: %d  Ime marke : % s  Ime proizvoda : % s  Cijena : % d\n", (polje + i)->id, (polje + i)->marka, (polje + i)->imeProizvoda, (polje + i)->cijena);
			brojac++;
		}
	}
	if (brojac == 0)
	{
		printf("\nTrazen proizvod nije pronadjen.\n");
	}
	return NULL;
}


void* pretrazivanjeCijena(PROIZVOD* polje)
{
	int trazenaCijena, brojac = 0;

	printf("Unesite broj cijene koju trazite:\n");
	scanf("%d", &trazenaCijena);
	if (trazenaCijena != 1)
	{
		system("cls");
		printf("Pogresan unos!\n");
		scanf("%*[^\n]");
	}

	for (i = 0; i < brojProizvoda; i++)
	{
		if (trazenaCijena == (polje + i)->cijena)
		{

			printf("\nID: %d  Ime marke : % s  Ime proizvoda : % s  Cijena : % d\n", (polje + i)->id, (polje + i)->marka, (polje + i)->imeProizvoda, (polje + i)->cijena);

			brojac++;
		}
	}
	if (brojac == 0)
	{
		printf("\nTrazena cijena nije pronadjena.\n");
		return NULL;
	}
}

int compareCijenaUzl(const void* a, const void* b)
{
	PROIZVOD* proizvodA = (PROIZVOD*)a;
	PROIZVOD* proizvodB = (PROIZVOD*)b;

	if (proizvodA->cijena < proizvodB->cijena) return -1;
	if (proizvodA->cijena > proizvodB->cijena) return 1;
	return 0;
}

int compareCijenaSil(const void* a, const void* b)
{
	PROIZVOD* proizvodA = (PROIZVOD*)a;
	PROIZVOD* proizvodB = (PROIZVOD*)b;

	if (proizvodA->cijena > proizvodB->cijena) return -1;
	if (proizvodA->cijena < proizvodB->cijena) return 1;
	return 0;
}

void SortCijenaUzl(PROIZVOD* polje)
{
	qsort(polje, brojProizvoda, sizeof(PROIZVOD), compareCijenaUzl);

	printf("Sortirani proizvodi po cijeni uzlazno:\n\n");
	for (int i = 0; i < brojProizvoda; i++)
	{
		printf("ID: %d\t Ime marke: %-20s Ime proizvoda: %-20s Cijena: %d\n", polje[i].id, polje[i].marka, polje[i].imeProizvoda, polje[i].cijena);
	}
}

void SortCijenaSil(PROIZVOD* polje)
{
	qsort(polje, brojProizvoda, sizeof(PROIZVOD), compareCijenaSil);

	printf("Sortirani proizvodi po cijeni silazno:\n\n");
	for (int i = 0; i < brojProizvoda; i++)
	{
		printf("ID: %d\t Ime marke: %-20s Ime proizvoda: %-20s Cijena: %d\n", polje[i].id, polje[i].marka, polje[i].imeProizvoda, polje[i].cijena);
	}
}

void brisanjeProizvoda(PROIZVOD* polje)
{
	FILE* fp = NULL;
	fp = fopen("proizvodi.bin", "wb");
	if (fp == NULL)
	{
		perror("Brisanje");
	}

	rewind(fp);
	fseek(fp, sizeof(int), SEEK_CUR);

	int idZaBrisanje, brojac = 0;

	printf("Unesite ID proizvoda koji zelite obrisati:\n");
	ispis(polje);

	scanf("%d", &idZaBrisanje);

	for (i = 0; i < brojProizvoda; i++)
	{
		if (idZaBrisanje != (polje + i)->id)
		{
			fwrite((polje + i), sizeof(PROIZVOD), 1, fp);
			brojac++;
		}
	}
	system("cls");

	rewind(fp);
	fwrite(&brojac, sizeof(int), 1, fp);
	fclose(fp);

}

void izlaz(PROIZVOD* polje)
{
	printf("Zelite li pri izlasku izbrisati datoteku ili je zadrzati?\n");
	printf("Ukoliko zelite izbrisati datoteku napisite 'DA'\n\n");

	char uvjet[7];
	scanf("%6s", uvjet);
	system("cls");

	if (!strcmp("DA", uvjet))
	{

		remove("proizvodi.bin") == 0 ? printf("Datoteka proizvodi.bin uspjesno izbrisana.\n") : printf("Datoteka neuspjesno izbrisana ili ne postoji.\n");
		printf("\nIzlaz iz programa.\n");
		free(polje);
		polje = NULL;

	}
	else
	{
		free(polje);
		polje = NULL;
		printf("Zadrzali ste datoteku.\n\nIzlaz iz programa.\n");
	}
}
