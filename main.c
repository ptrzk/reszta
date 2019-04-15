#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int wydaj(int reszta, int off, int size, int* nom, int* ilosci, int* wydane, int* reszty)
{
	nom += off;
	ilosci += off;
	wydane += off;
	reszty += off;
	for (int i=0; i<size; i++) {
		wydane[i] = MIN(reszta / nom[i], ilosci[i]);
		reszta -= wydane[i] * nom[i];
		reszty[i] = reszta;
		if (!reszta) return (0);
	}
	return (reszta);
}

void wypisz(int size, int* nom, int* ilosci)
{
	for (int i=0; i<size; i++)
		printf("%d: %d\n", nom[i], ilosci[i]);
}

int main()
{
	const int size = 8;
	int nom[] = {200, 100, 50, 20, 10, 5, 2, 1};
	char str[20];
	int ilosci[size];
	int wydane[size];
	int reszty[size];

	for (int i=0; i<size; i++) {
		printf("%d: ", nom[i]);
		fgets(str, 20, stdin);
		ilosci[i] = atoi(str);
		wydane[i] = 0;
	}
	puts("\nreszta: ");
	fgets(str, 20, stdin);
	int reszta = atoi(str);
	putchar('\n');

	reszta = wydaj(reszta, 0, size, nom, ilosci, wydane, reszty);
	int mreszta = reszta;
	while (reszta) {
		int i;
		for (i=size-1; i>=0; i--)
			if (wydane[i] && nom[i] > reszta) {
				wydane[i]--;
				reszty[i] += nom[i];
				break;
			}
		if (i < 0) {
			printf("Brak banknotów!\nDo wydania: %d\n", mreszta);
			return (-1);
		} else {
			reszta = wydaj(reszty[i], i + 1, size - i - 1, nom, ilosci, wydane, reszty);
			mreszta = MIN(mreszta, reszta);
		}
	}
	wypisz(size, nom, wydane);
}
