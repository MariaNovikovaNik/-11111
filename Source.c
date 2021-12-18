#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>


int main(void) {
	system("cls");
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int C = 0;
	int g = 0, m = 0, e = 0, tmp_g, N;
	float eps = 0, b = 0;
	int counter_g = 0, counter_m = 0, COUNTER = 0, check;
	int ARRg[40], ARRm[40], residue[40], ARRe[40], bx[40], A[40];

	printf("Введите пораждающий многочлен: ");
	scanf_s("%d", &g);
	printf("\nВведите сообщение: ");
	scanf_s("%d", &m);
	printf("\nВведите вероятность ошибки на бит: ");
	scanf_s("%f", &b);
	printf("g(x) = %d	m(x) = %d	Pb = %f\n", g, m, b);

	for (int i = 0; i < 40; i++) {
		A[i] = 0;
	}

	tmp_g = g;
	int i = 0;
	while (tmp_g != 0) {
		ARRg[i] = tmp_g % 2;
		i++;
		tmp_g >>= 1;
		counter_g++;
	}

	int tmp_m = m;
	i = 0;
	while (tmp_m != 0) {
		ARRm[i] = tmp_m % 2;
		i++;
		tmp_m >>= 1;
		counter_m++;
	}
	printf("Сообщение: ");
	for (int i = counter_m - 1; i >= 0; i--) {
		printf("%d ", ARRm[i]);
	}
	printf("\nПорождающий многочлен: ");
	for (int i = counter_g - 1; i >= 0; i--) {
		printf("%d ", ARRg[i]);
	}
	printf("\n");

	for (i = counter_m - 1; i >= 0; i--) {
		residue[i] = ARRm[i];
	}

	for (i = counter_m - 1; i >= 0; i--) {
		if (residue[i] == 0) {
			continue;
		}
		if (i < counter_g - 1) {
			break;
		}
		int i_tmp = i;
		for (int j = counter_g - 1; j >= 0; j--) {

			if (residue[i_tmp] == ARRg[j]) {
				residue[i_tmp] = 0;
			}
			else { residue[i_tmp] = 1; }
			i_tmp--;
		}
	}

	printf("Остаток от деления:  ");
	for (int i = counter_m - 1; i >= 0; i--) {
		printf("%d ", residue[i]);
	}


	for (int i = counter_m - 1; i >= 0; i--) {
		ARRm[i + counter_g - 1] = ARRm[i];
		ARRm[i] = 0;
	}

	printf("\nax: ");

	for (int i = counter_g - 2; i >= 0; i--) {
		ARRm[i] = residue[i];
	}

	for (int i = counter_m + counter_g - 2; i >= 0; i--) { //получили a(x)
		printf("%d ", ARRm[i]);
	}

	float Final = 0;
	////верхний предел ошибки декодирования
	//for (int i_tmp = 0; i_tmp < counter_m - 2; i_tmp++) {
	//	C = factorial(counter_g + counter_m - 2) / (factorial(counter_g + counter_m - 2 - i_tmp) * factorial(i_tmp));
	//	Final = Final + (C * pow(b, i_tmp) * pow((1 - b), (counter_g + counter_m - 2 - i_tmp)));
	//}


	int stop = pow(2, (counter_m)) - 1;
	//точная величина ошибки
	for (int m = 1; m <= stop; m++) {
		int counter = 0;
		counter_m = 0;
		tmp_m = m * g;


		i = 0;
		while (tmp_m != 0) {
			ARRm[i] = tmp_m % 2;
			i++;
			tmp_m >>= 1;
			counter_m++;
		}

		printf("\n\nax: ");
		for (int i = counter_m - 1; i >= 0; i--) {
			printf("%d ", ARRm[i]);
		}


		for (int i = counter_m - 1; i >= 0; i--) { //получили a(x)
			if (ARRm[i] == 1) {
				counter++;
			}
			printf("%d ", ARRm[i]);
		}
		A[counter]++;
		printf("\nA: ");
		for (int i = 0; i < counter_m + counter_g - 1; i++) {

			printf("%d ", A[i]);
		}
	}
	int n = counter_g + counter_m - 1;
	float p = 1 - b;
	float final2 = 1 * pow((1 - b), (counter_m - 1)); // 1 так как слово с нулевым весом есть всегда
	int counter_A = 0;

	for (int i = 0; i < counter_m - 1; i++) {
		if (A[i] != 0) {
			break;
		}
		counter_A++;
	}
	for (int i_tmp = 0; i_tmp < counter_A; i_tmp++) {
		C = factorial(counter_m - 1) / (factorial(counter_m - 1 - i_tmp) * factorial(i_tmp));
		Final = Final + (C * pow(b, i_tmp) * pow((1 - b), (counter_m - 2 - i_tmp)));
	}
	printf("\n\n\nВерхний предел %f\n\n", (1 - Final));
	for (int i = 0; i < counter_m - 1; i++) {

		final2 = final2 + A[i] * pow(b, i) * pow(p, (n));
		n--;
	}
	printf("\n\nТочное значение веротности ошибки декодирования %f\n", final2);

}

int factorial(n) {
	return (n < 2) ? 1 : n * factorial(n - 1);
}