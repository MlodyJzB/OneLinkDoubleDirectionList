#include <stdio.h>
#include <stdlib.h>

struct Node {
	float number;
	int link;
};

void initNode(float num, struct Node* nP);

void initDumNode(struct Node* nP);

void addN(struct Node* newNP, struct Node* dumHeadP, struct Node** prevHeadPP, struct Node** afterTailPP);

bool isDummy(struct Node* nP);

struct Node* findN(float toFind, struct Node** prevDestPP, struct Node* dumTailP, struct Node* afterTailP);

void deleteN(struct Node* toDel, struct Node* prev);

void showT(struct Node* dumTailP, struct Node* afterTailP);

int main() {
	struct Node* dumHeadP = (struct Node*)malloc(sizeof(struct Node));
	initDumNode(dumHeadP);

	struct Node* dumTailP = (struct Node*)malloc(sizeof(struct Node));
	initDumNode(dumTailP);

	struct Node* prevHeadP = dumTailP;
	struct Node* afterTailP = dumHeadP;

	struct Node* newNP = (struct Node*)malloc(sizeof(struct Node));
	initNode(3, newNP);
	struct Node* newNP2 = (struct Node*)malloc(sizeof(struct Node));
	initNode(4, newNP2);
	struct Node* newNP3 = (struct Node*)malloc(sizeof(struct Node));
	initNode(5, newNP3);

	addN(newNP, dumHeadP, &prevHeadP, &afterTailP);
	addN(newNP2, dumHeadP, &prevHeadP, &afterTailP);
	addN(newNP3, dumHeadP, &prevHeadP, &afterTailP);

	showT(dumTailP, afterTailP);
}

void initNode(float num, struct Node* nP) {
	nP->number = num;
}

void initDumNode(struct Node* nP) {
	nP->link = 0;
}

void addN(struct Node* newNP, struct Node* dumHeadP, struct Node** prevHeadPP, struct Node** afterTailPP) {
	newNP->link = dumHeadP - *prevHeadPP; // link to dummyHead

	if (isDummy(*prevHeadPP)) {
		*afterTailPP = newNP;
	}
	else {
		(*prevHeadPP)->link += (newNP - dumHeadP); // link to added node instead of link to dummy head

	}

	*prevHeadPP = newNP;
}

bool isDummy(struct Node* nP) {
	return nP->link == 0;
}

struct Node* findN(float toFind, struct Node** prevDestPP, struct Node* dumTailP, struct Node* afterTailP) {
	struct Node* cur = afterTailP;
	struct Node* prevCur = dumTailP;
	
	while ((cur->number != toFind) && (cur->link != 0)) {
		struct Node* temp = cur;
		cur = prevCur + cur->link;
		prevCur = temp;
	}
	*prevDestPP = prevCur;
	return cur;
}

void deleteN(struct Node* toDel, struct Node* prev) {
	struct Node* next = prev + toDel->link;
	if (!isDummy(next)) {
		next->link += (toDel - prev);
	}
	if (!isDummy(prev)) {
		prev->link += (next - toDel);
	}

	free(toDel);
}

void showT(struct Node* dumTailP, struct Node* afterTailP) {
	struct Node* cur = afterTailP;
	struct Node* prevCur = dumTailP;

	while (!isDummy(cur)) {
		printf("%.3f ", cur->number);

		struct Node* temp = cur;
		cur = prevCur + cur->link;
		prevCur = temp;
	}
}