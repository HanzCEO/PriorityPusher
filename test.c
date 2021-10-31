// Bubble sort test
#include <stdio.h>
#include <stdlib.h>

typedef struct apple {
	unsigned seed;
	unsigned tasty;
} apple;

void swap(apple *ap, apple *bp) {
	apple tmp = *ap;
	*ap = *bp;
	*bp = tmp;
}

int main() {
	apple a1 = {2, 6};
	apple a2 = {2, 7};
	apple a3 = {4, 3};

	apple apples[3] = {a1, a2, a3};

	// Bubble sort
	

	for (int i = 2; i >= 0; i--) printf("[%d] ===---===---===\nSeed : %u\nTasty: %u\n", i, apples[i].seed, apples[i].tasty);
	return 0;
}
