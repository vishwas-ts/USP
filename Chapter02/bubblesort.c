#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static int count = 0;

static int onepass(int a[], int n) {
	int i;
	int interchanges = 0;
	int temp;

	for (i = 0; i < n - 1; i++) {
		if (a[i] > a[i+1]) {
			temp = a[i];
			a[i] = a[i+1];
			a[i+1] = temp;
			interchanges = 1;
			count++;
		}

	}
	return interchanges;
}

void clear_count(void) {
	count = 0;
}

int get_count(void) {
	return count;
}


void bubblesort(int a[], int n) {

	int i;
	for (i = 0; i < n - 1; i++) 
		if (!onepass(a, n - i))
			break;

}

int main(int argc, char *argv[]) {

	int a[] = {2, 1, 5, 3, 4};

	int n = sizeof(a)/sizeof(a[0]);

	clear_count();
	bubblesort(a, n);

	printf("After sort, the array is: ");
	for (int i = 0; i < n; i++) 
		printf("%d, ", a[i]);
	printf("\n");

	printf("The number of interchange count is %d\n", get_count());
	return 0;
}
