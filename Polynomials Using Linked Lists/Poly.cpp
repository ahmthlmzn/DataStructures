//Ahmet Halim UZUN - 152120181048
//Mesut KIZILAY - 152120181053

#include <stdio.h>
#include "Poly.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstdlib>
#include <algorithm>
using namespace std;
void remove(PolyNode**, int);
#define DEG 100	//Maximum polinom derecesi

//-------------------------------------------------
// Creates a polynomial from an expression.
// Returns a pointer to the first PolyNode in the list (head of the list)
//
// Expression will be of the following sort:
// Ex1: 2.3x^4 + 5x^3 - 2.64x - 4
// Ex2: -4.555x^10 - 45.44
// Ex3: x^6 + 2x^4 - x^3 - 6.3x + 4.223 
// Ex4: 34
// Ex5: -x+1
// Ex6: -3x^4    +   4x
// Ex7: -2x  - 5
//

string removeSpaces(string str) {
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	return str;
}

PolyNode* CreatePoly(char* expr) {

	string str(expr);
	str = removeSpaces(str);
	int exprSize = str.size();
	//Artý ve eksi sayýlarýný buldurma
	int k = 1;
	for (int i = 1; i < exprSize; ++i) {
		if (str[i] == '+' || str[i] == '-') {
			k++;
		}
	}
	int artiEksiCount = k;

	//	Dize ayrýþtýrmasý için "+" iþaretlerini kullandýk 
	if (isdigit(str[0])) str.insert(0, "+");
	if (str[0] == 'x') str.insert(0, "+");
	str.append("+");
	exprSize = str.size();

	//	Artý Eksilerin diziye eklenme iþlemi
	k = 0;
	int j = 0;
	string artiEksiStr[DEG];
	for (int i = 1; i < exprSize; ++i) {
		if (str[i] == '+' || str[i] == '-') {
			artiEksiStr[k++] = str.substr(j, i - j);
			j = i;
		}
	}

	//  Katsayý ve üsse göre formatlama iþlemi
	for (int i = 0; i < artiEksiCount; ++i)
	{
		if (artiEksiStr[i][1] == 'x') {	//x +/- iþaretinden sonra
			artiEksiStr[i].insert(1, "1");	// katsayý olarak 1 alýr
		}
		bool flag = false;	// x'in mevcut olmadýðýný varsayarsak
		int len = artiEksiStr[i].size();
		for (int j = 1; j < len; ++j) {
			if (artiEksiStr[i][j] == 'x') {// x'in olup olmadýðýnýn kontrolü
				flag = true;	// x varsa
				if (j == len - 1) {	// ve x sonsa
					artiEksiStr[i].append("^1");	//üs 1 alýr
				}
				break;
			}
		}
		if (!flag)	//x yoksa: sabit bir terimimiz var
			artiEksiStr[i].append("x^0");	//"biçimlendirmeyi" alan
	}

	//	Katsayýlarý ve üsleri sayý olarak çýkarma
	int us[DEG] = { 0 };
	double katsayi[DEG] = { 0 };
	for (int i = 0; i < artiEksiCount; ++i)
	{
		int artiEksiSize = artiEksiStr[i].size();
		for (int j = 0; j < artiEksiSize; ++j)
		{
			if (artiEksiStr[i][j] == '^')
			{
				us[i] = stoi(artiEksiStr[i].substr(j + 1, artiEksiSize - j));
				katsayi[i] = stod(artiEksiStr[i].substr(0, j));
				break;
			}
		}
	}

	//	Maksimum üs aranýyor	
	int maxUs = 0;
	for (int k : us) {
		if (k >= maxUs) {
			maxUs = k;
		}
	}

	//	Derecesi = maxUs olan boþ polinomun tek terimlilerinin üretilmesi
	string newArtiEksi[DEG];
	for (int i = maxUs; i >= 0; i--) {
		newArtiEksi[i] = "+0x^" + to_string(i);
	}

	//	Ýki polinomun karýþtýrýlmasý : verilen & null
	for (int i = artiEksiCount; i >= 0; i--) {
		newArtiEksi[us[i]] = artiEksiStr[i];
	}

	//	Polinomun düzeltilmiþ verisiyonunu yazdýrýyoruz, burasý test amaçlý	
	std::string finalStr;
	for (int i = maxUs; i >= 0; i--)
		finalStr += newArtiEksi[i];
	//std::cout << "\nDüzeltilmis: " << finalStr << '\n';

	//	Katsayýlarý ve üsleri çýkarýyoruz  
	//	Verilen polinomun son biçiminden
	int finalSize = finalStr.size();
	int baslangic[DEG] = { 0 };
	int bitis[DEG] = { 0 };
	k = 0;
	for (int i = 0; i < finalSize; ++i) {
		if (finalStr.substr(i, 1) == "+" || finalStr.substr(i, 1) == "-") {
			baslangic[k] = i;
		}
		if (finalStr.substr(i, 1) == "x") {
			bitis[k++] = i;
		}
	}

	for (int i = 0; i < k; ++i) {
		katsayi[i] = stod(finalStr.substr(baslangic[i], bitis[i] - baslangic[i]));
		us[i] = maxUs - i;
	}

	//Artýk elimizde bulunan katsayý ve üs deðerlerinin AddNode'a gönderilmesi iþlemi

	int yeni_us[DEG];
	double yeni_katsayi[DEG];
	int z = 0;
	for (int i = 0; i < DEG; i++) {
		if (katsayi[i] != 0) {
			yeni_us[z] = us[i];
			yeni_katsayi[z] = katsayi[i];
			// cout << z + 1 << ".us:" << yeni_us[z] << " "; 
				z++;
		}
	}

	PolyNode* head = NULL;

	for (int i = 0; i < z; i++) {
		//cout << "katsayi[" << i << "]: " << yeni_katsayi[i] << endl;
		//cout << "yeni_us[" << i << "]: " << yeni_us[i] << endl;
		head = AddNode(head, yeni_katsayi[i], yeni_us[i]);
	}
	return head;
} //end-CreatePoly

/// -------------------------------------------------
/// Walk over the poly nodes & delete them
///

void DeletePoly(PolyNode* poly) {
	// Fill this in
	if (poly && poly->next)
	{
		PolyNode* p, * q;
		p = poly;
		while (p)
		{
			q = p->next;
			free(p);
			p = q;
		}
	}
	poly = NULL;
} // end-DeletePoly
	
//-------------------------------------------------
// Adds a node (coefficient, exponent) to poly. If there already 
// is a node with the same exponent, then you simply add the coefficient
// to the existing coefficient. If not, you add a new node to polynomial
// Returns a pointer to the possibly new head of the polynomial.
//

PolyNode* AddNode(PolyNode *head, double coef, int exp){
	// Fill this in
	PolyNode* poly = new PolyNode();
	poly->coef = coef; poly->exp = exp;
	poly->next = NULL;

	PolyNode* q = NULL;
	PolyNode* p = head;

	while (p != NULL && exp <= p->exp)
	{
		if (exp == p->exp)
		{
			p->coef += coef;
			//break;
		}
		q = p;
		p = p->next;
	}
	if (q == NULL)
	{
		poly->next = head;
		head = poly;
	}
	else if (exp != q->exp)
	{
		poly->next = q->next;
		q->next = poly;
	}
	remove(&head, 0);
	return head;
} // end-AddNode

void remove(PolyNode** head, int num)
{
	PolyNode* temp = *head;
	PolyNode* prev = NULL;

	if (temp != NULL && temp->coef == num)
	{
		*head = temp->next;
		delete temp;
		return;
	}

	while (temp != NULL && temp->coef != num)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
	{
		return;
	}
	prev->next = temp->next;
	delete temp;
}

//-------------------------------------------------
// Adds two polynomials and returns a new polynomial that contains the result
// Computes: poly3 = poly1 + poly2 and returns poly3
//

PolyNode *Add(PolyNode *poly1, PolyNode *poly2){
	// Fill this in
	
	PolyNode* poly3 = NULL;
	while (poly1 && poly2)
	{
		if (poly1->exp > poly2->exp)
		{
			poly3 = AddNode(poly3, poly1->coef, poly1->exp);
			poly1 = poly1->next;
		}
		else if (poly1->exp < poly2->exp)
		{
			poly3 = AddNode(poly3, poly2->coef, poly2->exp);
			poly2 = poly2->next;
		}
		else
		{
			poly3 = AddNode(poly3, poly1->coef + poly2->coef, poly1->exp);
			poly1 = poly1->next;
			poly2 = poly2->next;
		}
	}
	while (poly1 || poly2)
	{
		if (poly1->next)
		{
			poly3 = AddNode(poly3, poly1->coef, poly1->exp);
			poly1 = poly1->next;
		}
		if (poly2->next)
		{
			poly3 = AddNode(poly3, poly2->coef, poly2->exp);
			poly2 = poly2->next;
		}
	}

	return poly3;
} //end-Add

//-------------------------------------------------
// Subtracts poly2 from poly1 and returns the resulting polynomial
// Computes: poly3 = poly1 - poly2 and returns poly3
//

PolyNode *Subtract(PolyNode *poly1, PolyNode *poly2){
	// Fill this in
	PolyNode* poly3 = NULL;
	while (poly1 && poly2)
	{
		if (poly1->exp > poly2->exp)
		{
			poly3 = AddNode(poly3, poly1->coef, poly1->exp);
			poly1 = poly1->next;
		}
		else if (poly1->exp < poly2->exp)
		{
			poly3 = AddNode(poly3, poly2->coef, poly2->exp);
			poly2 = poly2->next;
		}
		else
		{
			poly3 = AddNode(poly3, poly1->coef - poly2->coef, poly1->exp);
			poly1 = poly1->next;
			poly2 = poly2->next;
		}
	}
	while (poly1 || poly2)
	{
		if (poly1->next)
		{
			poly3 = AddNode(poly3, poly1->coef, poly1->exp);
			poly1 = poly1->next;
		}
		if (poly2->next)
		{
			poly3 = AddNode(poly3, poly2->coef, poly2->exp);
			poly2 = poly2->next;
		}
	}

	return poly3;
} //end-Substract

//-------------------------------------------------
// Multiplies poly1 and poly2 and returns the resulting polynomial
// Computes: poly3 = poly1 * poly2 and returns poly3
//

PolyNode *Multiply(PolyNode *poly1, PolyNode *poly2){
	// Fill this in
	PolyNode* poly3 = NULL;
	PolyNode* temp_poly1, * temp_poly2;
	temp_poly1 = poly1;
	temp_poly2 = poly2;
	while (temp_poly1 != NULL) {
		while (temp_poly2 != NULL) {
			
			int coeff, power;
			coeff = temp_poly1->coef * temp_poly2->coef;
			power = temp_poly1->exp + temp_poly2->exp;
			poly3 = AddNode(poly3, coeff, power);
			temp_poly2 = temp_poly2->next;
		}
		temp_poly2 = poly2;
		temp_poly1 = temp_poly1->next;
	}
	return poly3;
} //end-Multiply

//-------------------------------------------------
// Evaluates the polynomial at a particular "x" value and returns the result
//

double Evaluate(PolyNode *poly, double x){
	// Fill this in
	PolyNode* tmp = poly;
	double sonuc = 0;
	while (tmp != NULL)
	{
		sonuc += tmp->coef * pow(x, tmp->exp);
		tmp = tmp->next;
	}
	//cout << "\nResult : " << res;

	return sonuc;
} //end-Evaluate

//-------------------------------------------------
// Computes the derivative of the polynomial and returns it
// Ex: poly(x) = 3x^4 - 2x + 1-->Derivative(poly) = 12x^3 - 2
//

PolyNode* Derivative(PolyNode* poly) {
	// Fill this in

	PolyNode* head = poly;
	PolyNode* result = NULL;
	
	while (head != NULL) 
	{
		head->coef = head->coef * head->exp;
		head->exp = head->exp - 1;
		result = AddNode(result, head->coef, head->exp);
		head = head->next;
	}
	return result;
} //end-Derivative

//-------------------------------------------------
// Plots the polynomial in the range [x1, x2].
// -39<=x1<x2<=39
// -12<=y<=12
// On the middle of the screen you gotta have x & y axis plotted
// During evaluation, if "y" value does not fit on the screen,
// then just skip it. Otherwise put a '*' char depicting the curve
//

void Plot(PolyNode *poly, int x1, int x2){
	 //Fill this in	
	char command_line[25][80];
	if (-39 <= x1 && x2 <= 39)
	{
		for (int i = 24; i >= 0; i--)
		{
			for (int j = 0; j <= 78; j++)
			{
				if (round(Evaluate(poly, j - 39)) == i - 12)
				{
					command_line[i][j] = '*';
				}
				else
				{
					command_line[i][j] = ' ';
				}
				if (j == 39)
				{
					command_line[i][j] = '|';
					if (i % 5 == 2)
					{
						command_line[i][j] = '+';
					}
				}
				if (i == 12)
				{
					command_line[i][j] = '-';
					if (j % 5 == 4)
					{
						command_line[i][j] = '+';
					}
				}
				cout << command_line[i][j];
			}
			cout << endl;
		}
	}
	else
	{
		cout << "ERROR! Variables are out of range." << endl << endl;
	}
} //end-Plot
