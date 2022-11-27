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

	//addN(newNP, dumHeadP, &prevHeadP, &afterTailP);

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