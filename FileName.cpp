#include <stdio.h>
#include <stdlib.h>

struct treeNode
{
	int data;
	treeNode* left = NULL, * right = NULL;
};

treeNode* insert(treeNode* root, int data)
{
	if (root == NULL) //A
	{
		root = (treeNode*)malloc(sizeof(treeNode));
		root->data = data;
		root->left = root->right = NULL;
	}
	else if (data < root->data) //B
		root->left = insert(root->left, data);
	else if (data > root->data) //C
		root->right = insert(root->right, data);
	return root;//D
}


void inOrderTraversal(treeNode* root)
{
	if (root == NULL)
		return;

	inOrderTraversal(root->left);
	printf("%d ", root->data);
	inOrderTraversal(root->right);
}


void postOrderTraversal(treeNode* root)
{
	if (root == NULL) //A
		return;

	postOrderTraversal(root->left); //B
	postOrderTraversal(root->right); //C
	printf("%d ", root->data); //D
}

void preOrderTraversal(treeNode* root)
{
	if (root == NULL)
		return;

	printf("%d ", root->data);
	preOrderTraversal(root->left);
	preOrderTraversal(root->right);
}

treeNode* leftMost(treeNode* r)
{
	if (!r->left)
	{
		printf("%d\n ", r->data);
		return r;
	}
	return leftMost(r->left);
}

treeNode* deleteNode(treeNode* root, int data)
{
	if (root == NULL) //A
		return root;
	if (data < root->data) //B
		root->left = deleteNode(root->left, data);
	else if (data > root->data) //C
		root->right = deleteNode(root->right, data);
	else //D
	{
		if (!root->left) //D1
		{
			treeNode* tmp = root->right;
			free(root);
			return tmp;
		}
		else if (!root->right) //D2
		{
			treeNode* tmp = root->left;
			free(root);
			return tmp;

		}
		else //D3
		{
			treeNode* ios = leftMost(root->right);
			root->data = ios->data;
			root->right = deleteNode(root->right, ios->data);
		}

	}
	return root; //E
}

int getHeight(treeNode* r)
{
	if (r == NULL)
		return -1;

	int left = getHeight(r->left);
	int right = getHeight(r->right);

	if (left > right)
		return left + 1;
	else
		return right + 1;
}

treeNode* findParent(treeNode* node, treeNode* r, int* lr)
{
	if (node == NULL)
		return NULL;

	if (node->left == r)
	{
		*lr = -1;
		return node;
	}
	if (node->right == r)
	{
		*lr = 1;
		return node;
	}
	if (r->data > node->data)
		return findParent(node->right, r, lr);
	else if (r->data < node->data)
		return findParent(node->left, r, lr);
	else
		return NULL;
}

void isBalanced(treeNode* root, treeNode* r, bool* done)
{
	if (r == NULL)
		return;

	isBalanced(root, r->left, done);
	isBalanced(root, r->right, done);
	if (abs(getHeight(r->left) - getHeight(r->right)) >= 2)
	{
		*done = false;
		//L
		if (getHeight(r->left) > getHeight(r->right))
		{
			//LL
			if (getHeight(r->left->left) > getHeight(r->left->right))
			{
				int lr = 0;
				treeNode* a = r, * b = r->left, * c = r->left->left;
				treeNode* b_rc = b->right;
				treeNode* aParent = findParent(root, a, &lr);

				if (aParent)
					if (lr == 1)
						aParent->right = b;
					else
						aParent->left = b;

				b->right = a;
				a->left = b_rc;

				if (!aParent)
					root = b;
			}
			//LR
			else
			{
				int lr = 0;
				treeNode* a = r, * b = r->left, * c = r->left->right;
				treeNode* c_lc = c->left, * c_rc = c->right;
				treeNode* aParent = findParent(root, a, &lr);

				//Remove C-children
				c->left = c->right = NULL;

				//Remove A-left
				a->left = NULL;

				if (aParent)
					if (lr == 1)
						aParent->right = c;
					else
						aParent->left = c;

				c->right = a;
				c->left = b;

				b->right = c_lc;
				a->left = c_rc;

				if (!aParent)
					root = c;
			}
		}
		//R
		else
		{
			//RR
			if (getHeight(r->right->right) > getHeight(r->right->left))
			{
				int lr = 0;
				treeNode* a = r, * b = r->right, * c = r->right->right;
				treeNode* b_lc = b->left;
				treeNode* aParent = findParent(root, a, &lr);

				if (aParent)
					if (lr == 1)
						aParent->right = b;
					else
						aParent->left = b;

				b->left = a;
				a->right = b_lc;

				if (!aParent)
					root = b;
			}
			//RL
			else
			{
				int lr = 0;
				treeNode* a = r, * b = r->right, * c = r->right->left;
				treeNode* c_lc = c->left, * c_rc = c->right;
				treeNode* aParent = findParent(root, a, &lr);

				//Remove C-children
				c->left = c->right = NULL;

				//Remove A-left
				a->right = NULL;

				if (aParent)
					if (lr == 1)
						aParent->right = c;
					else
						aParent->left = c;

				c->right = b;
				c->left = a;

				b->left = c_rc;
				a->right = c_lc;

				if (!aParent)
					root = c;
			}
		}
	}
}

void AVLbalance(treeNode* root)
{
	bool done;

	do
	{
		done = true;
		isBalanced(root, root, &done);
	} while (!done);
}


int main()
{

	treeNode* myTree = NULL;
	myTree = insert(myTree, 50);
	myTree = insert(myTree, 100);
	myTree = insert(myTree, 30);
	myTree = insert(myTree, 150);
	myTree = insert(myTree, 120);
	myTree = insert(myTree, 80);
	myTree = insert(myTree, 110);
	myTree = insert(myTree, 20);
	myTree = insert(myTree, 25);

	//int x = abs(getHeight(myTree->left->left->right->left) - getHeight(myTree->left->left->right->right));

	//	printf("%d", x);

	AVLbalance(myTree);


	//printf("%d\n", getHeight(myTree));
	//printf("%d\n", getHeight(myTree->right));
	//printf("%d\n", getHeight(myTree->left));



	//printf("Postorder: ");
	//postOrderTraversal(myTree);

	//printf("\n\nInorder: ");
	//inOrderTraversal(myTree);

	//printf("\n\nPreorder: ");
	//preOrderTraversal(myTree);

	//printf("\n\nLeftmost: ");
	//leftMost(myTree);

	//treeNode* a = myTree->left;
	//int lr = 0;
	//treeNode* parent = findParent(myTree, a, &lr);

	//printf("%d\t %d", parent->data,lr);


	return 0;
}