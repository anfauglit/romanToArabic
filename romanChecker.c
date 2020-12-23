#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *strToPrimes (char *s) {
	int *primeForm;
	primeForm = malloc(sizeof(int) * (strlen(s) + 1));
	int primeVal;
	int flag = 1;
	for (int i = 0; i < strlen(s) && flag; ++i) {
		switch (s[i]) {
			case 'I':
				primeVal = 1;
				break;
			case 'V':
				primeVal = 5;
				break;
			case 'X':
				primeVal = 10;
				break;
			case 'L':
				primeVal = 50;
				break;
			case 'C':
				primeVal = 100;
				break;
			case 'D':
				primeVal = 500;
				break;
			case 'M':
				primeVal = 1000;
				break;
			default:
				flag = 0;	
		}
		primeForm[i] = primeVal;
	}
	if (flag)
		return primeForm;
	else
		return NULL;	
}

int main(int argc, char **argv) {
	
	char *s = argv[1];

	int* pr = strToPrimes(s);

	if (pr == NULL) {
		printf("Non-valid symbol is present.\n");
		return 0;
	}
	
	int uCounter = 0; // counter for number of unit digits in Roman notation
	int aCounter = 0; // counter for number of other digits in Roman notation
	int sum = 0;
	int uElement = 1000; // current value of a unit
	int i = 0;

	while (i < strlen(s) && uElement > 0) {
		if (pr[i] < uElement) {
			// monitors when you need to switch to the next digit in decimal representation of
			// a Roman number
			uElement /= 10; 
			uCounter = 0;
			aCounter = 0;
		} else {
			if (pr[i] >= uElement * 10 || (uCounter > 1 && pr[i] != uElement) || uCounter > 3)
				// (1) block the cases when Roman digits that are prohibited in the given position 
				// of decimal number appear
				// (2) block cases when a sequence of more than one Roman unit digits is followed by 
				// a numberal of the same rank
				// (3) block the case when there are more than 3 consequitive unit digits 
				break;
			if (pr[i] == uElement) {
				sum += pr[i];
				uCounter++;
			} else if (++aCounter > 1) {
				// block multiple appearences of Roman digits other then units
				break;
			} else if (uCounter == 1) {
				sum += pr[i] - 2 * uElement;
				uCounter = 0;
				aCounter = 0;
				uElement /= 10; 
			} else {	
				sum += pr[i];	
			}
			i++;
		}
	}

	printf("%s\n", s);

	if (i == strlen(s)) 
		printf("Roman notation is legit. Converted number: %i\n", sum);
	else
		printf("Roman notation is not legit\n");
		
	free(pr);
	return 0;
}
