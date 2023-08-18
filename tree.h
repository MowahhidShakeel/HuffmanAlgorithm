#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Node{
	char value;
	int freq;
	struct Node* left, *right;
};

struct Node* createNode(char c, int num) 
{
  struct Node* newNode = malloc(sizeof * newNode);
  newNode->freq = num;
  newNode->value = c;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}

struct Node* insertLeft(struct Node* root, int value, char c) {
  root->left = createNode(value);
  return root->left;
}

struct Node* insertRight(struct Node* root, int value, char c) {
  root->right = createNode(value);
  return root->left;
}