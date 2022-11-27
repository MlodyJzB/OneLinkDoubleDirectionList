#include <stdio.h>

struct Node {
	float number;
	int link;
};

void addN(struct Node* newNP, struct Node* dumHeadP, struct Node** prevHeadPP, struct Node** afterTailPP);

int main() {

}

void addN(struct Node* newNP, struct Node* dumHeadP, struct Node** prevHeadPP, struct Node** afterTailPP) {
	newNP->link = dumHeadP - *prevHeadPP;

	if ((*prevHeadPP)->link == 0) {
		*afterTailPP = newNP;
	}
	*prevHeadPP = newNP;
}