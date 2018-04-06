/*
Write a C function alternateMergeLinkedList() which inserts nodes of the second list
into alternate positions of the first list. The nodes of the second list should only be inserted when
there are alternate positions available in the first list.
The function prototype is given as follows:

void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2);

For an example, assume that given two linked lists are LinkedList1 and LinkedList2:
LinkedList1: 1 2 3
LinkedList2: 4 5 6 7
The resulting linked lists are:
LinkedList1: 1 4 2 5 3 6
LinkedList2: 7

The second list should become empty when the first list is larger than the second list. For an
example, assume that given two linked lists are LinkedList1 and LinkedList2:
LinkedList1: 1 5 7 3 9 11
LinkedList2: 6 10 2 4
The resulting Linked Lists are: LinkedList1: 1 6 5 10 7 2 3 4 9 11
LinkedList2: empty

A sample input and output session is given below (if the current linked lists are Linked list 1: 1 2
3 and Linked list 2: 4 5 6 7):
Linked list 1: 1 2 3
Linked list 2: 4 5 6 7
Please input your choice(1/2/3/0): 3
Linked list 1: 1 4 2 5 3 6
Linked list 2: 7
*/

///////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
2017/18 S2
Submission Deadline: March 30th, 2018 (Friday) 11.59 pm
Purpose: Implementing the required functions for Question 2 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// This is for question 2. You should not change the prototype of this function
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2);

// You may use the following functions or you may write your own
void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll1, ll2;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll1.head = NULL;
	ll1.size = 0;

	//Initialize the linked list 2 as an empty linked list
	ll2.head = NULL;
	ll2.size = 0;

	printf("1: Insert an integer to the linked list 1:\n");
	printf("2: Insert an integer to the linked list 2:\n");
	printf("3: Create the alternate merged linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list 1: ");
			scanf("%d", &i);
			j = insertNode(&ll1, ll1.size, i);
			printf("Linked list 1: ");
			printList(&ll1);
			break;
		case 2:
			printf("Input an integer that you want to add to the linked list 2: ");
			scanf("%d", &i);
			j = insertNode(&ll2, ll2.size, i);
			printf("Linked list 2: ");
			printList(&ll2);
			break;
		case 3:
			alternateMergeLinkedList(&ll1, &ll2); // You need to code this function
			printf("Linked list 1: ");
			printList(&ll1);
			printf("Linked list 2: ");
			printList(&ll2);
			break;
		case 0:
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)
{
	ListNode *LN1, *LN2;

    //counter
    LN1 = ll1->head;
    LN2 = ll2->head;

    while(LN1 != '\0' && LN2 != '\0')
    {
        //break away and insert index 0 node from list 2 into list 1
        ll2->head = LN2->next;
        LN2->next = LN1->next;
        LN1->next = LN2;

        //move cursors pointing to the nodes
        LN1 = LN1->next->next;
        LN2 = ll2->head;

        //update the size of the list
        ++(ll1->size);
        --(ll2->size);
    }
}

//////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;
	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}

	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
