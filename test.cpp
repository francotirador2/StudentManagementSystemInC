#include <stdio.h>
#include "List.h"
#include "Tree.h"


char * toString(void * d) {
	char * tmp= (char*)d;
	return tmp;
}

int equals(void * a, void * b){
	return (strcmp((char*)a,(char*)b) == 0);
}

int main() {

	
	Tree tree = newTree(toString,toString,equals);
	tree.root = insertInTree(tree,tree.root,(void*)"eminem");
	tree.root = insertInTree(tree,tree.root,(void*)"akon");
	tree.root = insertInTree(tree,tree.root,(void*)"50cent");
	tree.root = insertInTree(tree,tree.root,(void*)"enrique");
	//inorder(tree,tree.root);
	
	/*
	while (1) {
		TreeNode * tmp = getLeftMost(tree.root);
		if (tmp) {
			tree.root = deleteFromTree(tree,tree.root,tree.key(tmp->data));
			printf("\n");
			inorder(tree,tree.root);
		} else break;
	} */
	
	List list = getTreeAsList(tree);
	printList(list);
	
	
	
	/* List list = newList(toString,equals);
	appendToList(&list,(void*)"Hello");
	appendToList(&list,(void*)"World");
	appendToList(&list,(void*)"abcd");
	printList(list);
	
	ListNode * tmp = findInList(&list,(void*)"abcd");
	if (tmp) printf("%s",list.toString(tmp->data));
	else printf("Not found\n"); */ 
	
	return 0;
}
