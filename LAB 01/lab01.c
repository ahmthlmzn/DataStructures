//Ahmet Halim UZUN - 152120181048
//Mesut KIZILAY - 152120181053

#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
char A[100][100];
float a = 0, b = 0;
int xCounter(int, int, int, int);  //Blob say�s�n� ve pixel say�s�n� bulan fonksiyonu olu�turma.
int main()
{
	FILE* textfile;
	int row, col;
	int i, j;
	char ch;
	char filename[50];
	printf("Enter the filename : ");
	gets(filename, 50);  // Kullan�c�dan a��lacak dosyan�n ad�n� alma.
	printf("\n");

	textfile = fopen(filename, "r");
	if (!textfile)
	{
		printf("The file doesn't exist.\n\n");
		exit(0);
	}

	fscanf_s(textfile, "%d %d", &row, &col);

	for (i = 0; i < row; i++)  // txt dosyas�ndaki elemanlar� okutup, matrisin i�erisine aktarma.
	{
		for (j = 0; j < col; j++)
		{
			fscanf_s(textfile, "%c", &ch);
			if (ch != '\n')
			{
				A[i][j] = ch;
			}
			else
				j--;
		}
	}

	printf("  ");
	for (int i = 0; i < col; i++)
	{
		printf("%d", i % 10);
	}
	printf("\n +");
	for (int i = 0; i < col; i++)
	{
		printf("-");
	}
	printf("+\n");
	for (i = 0; i < row; i++)
	{
		printf("%d|", i % 10);
		for (j = 0; j < col; j++)
		{
			printf("%c", A[i][j]);  // Olu�turulan matrisi output ekran�na yazd�rma.
		}
		printf("|%d", i % 10);
		printf("\n");
	}
	printf(" +");
	for (int i = 0; i < col; i++)
	{
		printf("-");
	}
	printf("+\n  ");
	for (int i = 0; i < col; i++)
	{
		printf("%d", i % 10);
	}

	printf("\n\n");
	int blob_Sayisi = 0;
	int b�y�kl�k, k = 0;;
	int pixel_Counter[50];
	float comrow[50], comcol[50];


	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			a = 0;
			b = 0;
			b�y�kl�k = xCounter(row, col, i, j);  // Olu�turulan fonksiyonu �a��r�p, istenilen i�lemlerin hesaplanmas�.
			if (b�y�kl�k > 0)
			{
				pixel_Counter[blob_Sayisi] = b�y�kl�k;
				blob_Sayisi++;
				comrow[k] = a / (float)b�y�kl�k;
				comcol[k] = b / (float)b�y�kl�k;
				k++;
			}
		}
	}

	printf("+--------+--------------+-----------+--------------+\n");
	printf("|  BLOB  |  NoOfPixels  |  CoM RoW  |  CoM Column  |\n");
	printf("+--------+--------------+-----------+--------------+\n");
	for (int i = 0; i < blob_Sayisi; i++)
	{
		printf("|%8d|%14d|%11.2f|%14.2f|\n", i + 1, pixel_Counter[i], comrow[i], comcol[i]);  // Hesaplanan de�erlerin yazd�r�lmas�.
	}
	printf("+--------+--------------+-----------+--------------+\n");
	printf("\n");
	system("pause");
}

int xCounter(int r, int c, int i, int j)  // �stenilen hesaplamalar� yapan recursive fonksiyon.
{
	if ((i < 0 || i >= r) || (j < 0 || j >= c))
		return 0;
	if (A[i][j] == ' ')
		return 0;
	else
	{
		A[i][j] = ' ';
		a = a + i, b = b + j;
		return (1 + xCounter(r, c, i, j + 1) +
			xCounter(r, c, i + 1, j) +
			xCounter(r, c, i - 1, j) +
			xCounter(r, c, i, j - 1));
	}
}