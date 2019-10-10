#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
	
	void * data;
	struct ListNode * next;
	
} ListNode;

typedef struct List {
	
	ListNode * head;
	ListNode * tail;
	char * (*toString)(void*); //function to print node value
	int (*equal) (void*,void*); //function to check if two data items are equal
} List;

List newList(char*(*toString)(void*),int(equal)(void*,void*)) {
	List list;
	list.head = list.tail = NULL;
	list.toString = toString;
	list.equal = equal;
	return list;
}

ListNode * newListNode(void * data) {
	ListNode * node = (ListNode*)malloc(sizeof(ListNode));
	node->next = NULL;
	node->data = data;
	return node;
}

void appendToList(List * list, void * data) {
	
	ListNode * newNode = newListNode(data);
	if (list->head) {
		list->tail->next = newNode;
		list->tail = newNode;
	} else {
		list->head = newNode;
		list->tail = newNode;
	}
}

ListNode * findInList(List * list, void * data) {
	if (list) {
		ListNode * cur = list->head;
		while (cur) {
			if (list->equal(data,cur->data)) return cur;
			cur = cur->next;
		}
	}
	return NULL;
}

void removeFromList(List * list, void * data) {
	
}

void printList(List list) {
	ListNode * cur = list.head;
	while (cur) {
		printf("%s\n",list.toString(cur->data));
		cur = cur->next;
	}
}

/*
char * listToString(List list) {
	
	if (list.head) {
		ListNode * cur = list.head;
		char * result = "[";
		while (cur) {
			result = strcat(result,list.toString(cur->data));
			result = strcat(result,", ");
			cur = cur->next;
		}
	} else return "[]";
} */
