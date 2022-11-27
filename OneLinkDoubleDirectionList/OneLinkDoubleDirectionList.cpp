#include <stdio.h>
#include <stdlib.h>

struct Node {
	float number;
	int link;
};

void initNode(float num, struct Node* nP);

void initDumNode(struct Node* nP);

void addN(struct Node* newNP, struct Node* dumHeadP, struct Node** prevHeadPP, struct Node** afterTailPP);

int main() {
	struct Node* dumHeadP = (struct Node*)malloc(sizeof(struct Node));
	initDumNode(dumHeadP);

	struct Node* dumTailP = (struct Node*)malloc(sizeof(struct Node));
	initDumNode(dumTailP);

	struct Node* prevHeadP = dumTailP;
	struct Node* afterTailP = dumHeadP;

	
}

void initNode(float num, struct Node* nP) {
	nP->number = num;
}

void initDumNode(struct Node* nP) {
	nP->link = 0;
}

void addN(struct Node* newNP, struct Node* dumHeadP, struct Node** prevHeadPP, struct Node** afterTailPP) {
	newNP->link = dumHeadP - *prevHeadPP;

	if ((*prevHeadPP)->link == 0) {
		*afterTailPP = newNP;
	}
	*prevHeadPP = newNP;
}