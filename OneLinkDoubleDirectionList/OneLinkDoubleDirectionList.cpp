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

void deleteN(struct Node* toDel, struct Node* prevNP, struct Node** prevHeadPP, struct Node** afterTailPP);

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
	struct Node* curP = afterTailP;
	struct Node* prevCurP = dumTailP;
	
	while ((curP->number != toFind) && (curP->link != 0)) {
		struct Node* temp = curP;
		curP = prevCurP + curP->link;
		prevCurP = temp;
	}
	*prevDestPP = prevCurP;
	return curP;
}

void deleteN(struct Node* toDel, struct Node* prevNP, struct Node** prevHeadPP, struct Node** afterTailPP) {
	struct Node* nextP = prevNP + toDel->link;

	if (isDummy(nextP)) {
		*prevHeadPP = prevNP;
	}
	else {
		nextP->link += (toDel - prevNP);
	}
	if (isDummy(prevNP)) {
		*afterTailPP = nextP;
	}
	else {
		prevNP->link += (nextP - toDel);
	}

	free(toDel);
}

void showT(struct Node* dumTailP, struct Node* afterTailP) {
	struct Node* curP = afterTailP;
	struct Node* prevCurP = dumTailP;

	while (!isDummy(curP)) {
		printf("%.3f ", curP->number);

		struct Node* temp = curP;
		curP = prevCurP + curP->link;
		prevCurP = temp;
	}
}