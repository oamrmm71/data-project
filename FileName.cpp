#include <stdio.h>
#include <stdlib.h>
#include <conio.h>



class huffmantree {
	char data;
	int freq;

	huffmantree* left;
	huffmantree* right;
	huffmantree(char character,int frequency)
	{
		data = character;
		freq = frequency;
		left = right = NULL;
	}
};
huffmantree* buildhuffmantree(int freq[], int top) {
	Node* head = NULL;

	for (int i = 0; i < ASCII_SIZE; i++) {
		if (freq[i].freq > 0) {
			insertNode(&head, createNode(freq[i].ch, freq[i].freq));
		}
	}

	while (head != NULL && head->next != NULL) {
		Node* left = head;
		Node* right = head->next;
		head = right->next;

		top = newNode('$', left->freq + right->freq);
		top->left = left;
		top->right = right;

		insertNode(&head, top);
	}

	return head;
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

