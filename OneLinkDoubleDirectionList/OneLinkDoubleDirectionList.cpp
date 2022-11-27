#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// defines for actions switch
#define ADD 1
#define DEL 2
#define FIND 3
#define EDIT 4
#define DISPT 5
#define DISPH 6
#define EXIT 0

struct Node {
	float number;
	long long link;
};

void initNode(float num, struct Node* nP);

void initDumNode(struct Node* nP);

void addN(struct Node* newNP, struct Node* dumHeadP, struct Node** prevHeadPP, struct Node** afterTailPP);

bool isDummy(struct Node* nP);

struct Node* findN(float toFind, struct Node** prevDestPP, struct Node* dumTailP, struct Node* afterTailP);

void deleteN(struct Node* toDel, struct Node* prevNP, struct Node** prevHeadPP, struct Node** afterTailPP);

void editN(float num, struct Node* toEdit);

void dispT(struct Node* dumTailP, struct Node* afterTailP);

void dispH(struct Node* dumHeadP, struct Node* prevHeadP);

int getState();

void printActions();

int main() {
	struct Node* dumHeadP = (struct Node*)malloc(sizeof(struct Node));
	initDumNode(dumHeadP);

	struct Node* dumTailP = (struct Node*)malloc(sizeof(struct Node));
	initDumNode(dumTailP);

	struct Node* prevHeadP = dumTailP;
	struct Node* afterTailP = dumHeadP;

	struct Node* foundP = dumHeadP;
	struct Node* prevFoundP = dumTailP;

	while (1) {
		// menu loop based od switch to run actions

		printActions();
		printf("\nChoose action: ");

		int state = getState();

		switch (state) {
		case ADD: {
			float numToAdd;
			printf("Provide float to add: ");
			scanf_s("%f", &numToAdd);

			struct Node* toAddP = (struct Node*)malloc(sizeof(struct Node));
			initNode(numToAdd, toAddP);

			addN(toAddP, dumHeadP, &prevHeadP, &afterTailP);
			break;
		}

		case DEL: {
			if (foundP != dumHeadP) {
				deleteN(foundP, prevFoundP, &prevHeadP, &afterTailP);
				foundP = dumHeadP;
			}
			else {
				printf("\nProvide float to delete!\n");
				_getch();
			}
			break;
		}

		case FIND: {
			float numToFind;
			printf("Provide float to find: ");
			scanf_s("%f", &numToFind);

			foundP = findN(numToFind, &prevFoundP, dumTailP, afterTailP);

			if (foundP == dumHeadP) {
				printf("\nProvided float not found!\n");
			}

			break;
		}

		case EDIT: {

			float newNum;
			printf("Provide new float: ");
			scanf_s("%f", &newNum);

			if (foundP != dumHeadP) {
				editN(newNum, foundP);
				foundP = dumHeadP;
			}
			else {
				printf("\nProvide float to edit!\n");
				_getch();
			}
			break;
		}

		case DISPT: {
			dispT(dumTailP, afterTailP);
			_getch();
			break;
		}
		case DISPH: {
			dispH(dumHeadP, prevHeadP);
			_getch();
			break;
		}

		case EXIT: {
			return 0;
			break;
		}

		default: {
			printf("Incorrect action!\n");
		}

		}

		printActions();
		printf("\nChoose action: ");
	}

	return 0;
}

void initNode(float num, struct Node* nP) {
	// init node

	nP->number = num;
	return;
}

void initDumNode(struct Node* nP) {
	// init dummy node (head or tail)

	nP->link = 0;
	return;
}

void addN(struct Node* newNP, struct Node* dumHeadP, struct Node** prevHeadPP, struct Node** afterTailPP) {
	// add provided node to the end of a list

	newNP->link = dumHeadP - *prevHeadPP; // link to dummyHead

	if (isDummy(*prevHeadPP)) {
		*afterTailPP = newNP;
	}
	else {
		(*prevHeadPP)->link += (newNP - dumHeadP); // link to added node instead of link to dummy head

	}

	*prevHeadPP = newNP;
	return;
}

bool isDummy(struct Node* nP) {
	// check if node is dummy

	return nP->link == 0;
}

struct Node* findN(float toFind, struct Node** prevDestPP, struct Node* dumTailP, struct Node* afterTailP) {
	// find node by provided float and return it, provide parent node pointer of found node

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
	// delete provided node, keeps list order, change prevHead and afterTail if is deleted
	
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
	return;
}

void editN(float num, struct Node* toEdit) {
	// gives new float value to the provided node

	toEdit->number = num;
	return;
}

void dispT(struct Node* dumTailP, struct Node* afterTailP) {
	// display whole list starting with afterTail node

	struct Node* curP = afterTailP;
	struct Node* prevCurP = dumTailP;

	while (!isDummy(curP)) {
		printf("%.3f ", curP->number);

		struct Node* temp = curP;
		curP = prevCurP + curP->link;
		prevCurP = temp;
	}
	printf("\n");
	return;
}

void dispH(struct Node* dumHeadP, struct Node* prevHeadP) {
	// display whole list starting with prevHead node

	struct Node* curP = prevHeadP;
	struct Node* prevCurP = dumHeadP;

	while (!isDummy(curP)) {
		printf("%.3f ", curP->number);

		struct Node* temp = curP;
		curP = prevCurP - curP->link;
		prevCurP = temp;
	}
	printf("\n");
	return;
}

int getState() {
	// ask for state number till valid (0-6)

	int state;

	do {
		scanf_s("%d", &state);
		getchar();
	} while ((state < 0) || (state > 6));

	return state;
}

void printActions() {
	// print possible actions

	system("cls");
	printf("Possible actions: \n1 - Add item\n2 - Delete item\n3 - Find item\n4 - Edit item\n5 - Show all items from beginning\n6 - Show all items from end\n0 - Exit\n");
	return;
}
