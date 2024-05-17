#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


struct node {

	char data;
	int freq;
};
class huffmantree 
{
		
	huffmantree* left;
	huffmantree* right;
	huffmantree(char character,int frequency)
	{
		data = character;
		freq = frequency;
		left = right = NULL;
	}

	void findfreq(char s[])
	{
		int i = 0;

		int freq[26] = { 0 };

		while (s[i] != '\0')
		{
			freq[s[i] - 'a']++;
			i++;
		}
		printfreq(freq);
	}

	huffmantree* buildhuffmantree(int freq[], int top) 
	{

	Node* header = NULL;

	for (int i = 0; i < ASCII_SIZE; i++) 
	{

		if (freq[i].freq > 0) 
		{
			insertNode(&header, createNode(freq[i].ch, freq[i].freq));
		}
	}

	while (header != NULL && header->next != NULL) 
	{
		Node* left = header;
		Node* right = header->next;
		header = right->next;

		top = newNode('$', left->freq + right->freq);
		top->left = left;
		top->right = right;

		insertNode(&header, top);
	}

	return header;
	}


};
