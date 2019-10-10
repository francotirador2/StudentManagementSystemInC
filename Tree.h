#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "List.h"

typedef struct TreeNode {
	void * data;
	struct TreeNode * left , * right;
} TreeNode;

typedef struct Tree {
	
	TreeNode * root;
	char * (*toString)(void*);
	char * (*key)(void*);
	int (*equal)(void*,void*);
} Tree;

Tree newTree(char*(*toString)(void*), char*(*key)(void*), int(*equal)(void*,void*)) {
	
	Tree tree;
	tree.root = NULL;
	tree.toString = toString;
	tree.key = key;
	//tree.equal = equal;
	return tree;
	
}

TreeNode * newTreeNode(void * data) {
	TreeNode * x = (TreeNode*)malloc(sizeof(TreeNode));
	x->data = data;
	x->left = x->right = NULL;
	return x;
}

TreeNode * insertInTree(Tree tree, TreeNode * root, void * data) {
	
	if (root) {
		
		char * nodeKey = tree.key(root->data);
		char * key = tree.key(data);
		
		if (strcmp(key,nodeKey) < 0) root->left = insertInTree(tree,root->left,data);
		else if (strcmp(key,nodeKey) > 0) root->right = insertInTree(tree,root->right,data);
		else root->data = data;
		
		return root;
		
	} 
	
	return newTreeNode(data);
	
}

TreeNode * findInTree(Tree tree, TreeNode * root, char * key) {
	
	if (root) {
		char * nodeKey = tree.key(root->data);
		if (strcmp(key,nodeKey) < 0) return findInTree(tree,root->left,key);
		else if (strcmp(key,nodeKey) > 0) return findInTree(tree,root->right,key);
		return root;
	} 
	return NULL;
}

TreeNode * getLeftMost(TreeNode * root) {
	
	while (root && root->left) {
		root = root->left;
	}
	return root;
}

TreeNode * deleteFromTree(Tree tree, TreeNode * root, char * key) {
	
	if (root) {
		
		char * nodeKey = tree.key(root->data);
		if (strcmp(key,nodeKey) < 0) root->left = deleteFromTree(tree,root->left,key);
		else if (strcmp(key,nodeKey) > 0) root->right = deleteFromTree(tree,root->right,key);
		else {
			if (root->left == NULL && root->right == NULL) return NULL;
			else if (root->left == NULL && root->right != NULL) return root->right;
			else if (root->left != NULL && root->right == NULL) return root->left;
			else {
				TreeNode * tmp = getLeftMost(root->right);
				root->data = tmp->data;
				root->right = deleteFromTree(tree,root->right,tree.key(tmp->data));
			}
		}
		
		return root;
	}
	
	return NULL;
}

void inorder(Tree tree, TreeNode * root) {
	
	if (root) {
		inorder(tree,root->left);
		printf("%s\n",tree.toString(root->data));
		inorder(tree,root->right);
	}
}

void printTree(Tree tree) { inorder(tree,tree.root); }

void copyData(TreeNode * root, List * list) {
	if (root) {
		
		copyData(root->left,list);
		appendToList(list,root->data);
		copyData(root->right,list);
	}
}

List getTreeAsList(Tree tree) {
	List list = newList(tree.toString,tree.equal);
	copyData(tree.root,&list);
	return list;
}
