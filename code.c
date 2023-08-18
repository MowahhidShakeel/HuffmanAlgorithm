#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE *fp;
char c;
int* ASCII;	//The array for checking frequency of characters an storing in array
int count =0; //Maintaining count of unique characters
int check=2; //Used while building tree
struct Node* arr;

struct Node{
	char value;
	int freq;
	struct Node* left, *right, *top;
};

struct Node* createNode(char c, int num) 
{
  struct Node* newNode = malloc(sizeof * newNode);
  newNode->freq = num;
  newNode->value = c;
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->top = NULL;

  return newNode;
}

struct Node* insertLeft(struct Node* root, int value, char c) {
  root->left = createNode(c, value);
  return root->left;
}

struct Node* insertRight(struct Node* root, int value, char c) {
  root->right = createNode(c, value);
  return root->left;
}

void createTree(struct Node* node){
	
	if (check > count)
	return;

	struct Node* parent = createNode("", -1);
	if (node->freq <= arr[check].freq)
	{
		parent->left = node;
		parent->right = &arr[check];
	}
	else 
	{
		parent->right = node;
		parent->left = &arr[check];
	}
	check++;
	parent->freq = parent->left->freq + parent->right->freq;
	createTree(parent);
}


int main(int argc, char *argv[])
{
	
	ASCII = malloc(sizeof(int)*128);	//Initialzing array, 128 characters are the limit
	if (ASCII == NULL)
	{
		perror("Error!");
		exit(EXIT_FAILURE);
	}
	
	fp = fopen ("text.txt","r");	//Opening file to read
	 if (fp == NULL)
	 {
       	 	 perror("Error! File not Opened");
       	 	 return (-1);
  	 }
  	 	
  	 while (c != EOF)	//Reading the values
  	 {
  	 	c = (char)fgetc(fp);
  	 	if (ASCII[(int)c] ==0)
  	 	{
  	 		count++;
  	 	}
  	 	ASCII[(int)c]++;
  	 }

  	
	struct Node* arr = malloc(count * sizeof *arr);
	if (arr == NULL)
	{
		perror("ERROR!");
		exit(EXIT_FAILURE);
	}

	struct Node* temp = malloc(sizeof *temp);
	if (temp == NULL)
	{
		perror("ERROR!");
		exit(EXIT_FAILURE);
	}
	int x;
	int j=0;

	for (x = 32; x < 128; x++)	//Placing the values in struct array
	{
		if (ASCII[x]!= 0)
	  	 	{
	  	 		arr[j].value = x;
	  	 		arr[j].freq = ASCII[x];
	  	 		j++;
	  	 	}
	}
  	printf("Unique characters: %d\n", count);
  	 for (int i=0; i<j-1; i++)	//Sorting
  	 {
  	 	for (int k=0; k<j-i-1; k++)
  	 	{
  	 		if (arr[k].freq > arr[k + 1].freq)
  	 		{
  	 			temp->value = arr[k].value;
  	 			temp->freq = arr[k].freq;
  				arr[k].value = arr[k+1].value;
	 			arr[k].freq = arr[k+1].freq;
  	 			arr[k+1].value = temp->value;
  	 			arr[k+1].freq = temp->freq;
  	 		}
  	 	}
  	 }
	char dump = "";
  	 
	struct Node* root = createNode(dump, -1);
	root->left = &arr[1];
	root->right = &arr[0];
	root->freq = root->left->freq + root->right->freq;
	createTree(root);
	
	
	printf("Root Freq: %d\n", root->freq);
	printf("Root Left Freq: %d\n", root->left->freq);
	printf("Root Right Freq: %d\n", root->right->freq);

  	 for (int i=0; i<j; i++)	 
  	 {
  	 	printf("%c  %d\n", arr[i].value, arr[i].freq);
  	 }
  	 
  	 //free(ASCII);
  	 //free(arr);
  	 
  	 exit(0);
  	 
}
