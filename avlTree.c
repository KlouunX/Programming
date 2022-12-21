#include<stdio.h>
#include<stdlib.h>
#define MAX 1000000

typedef struct avlTree
{
	int key;
	struct avlTree *left;
	struct avlTree *right;
	int height;
} avl;

int height(avl *N);
int max(int a, int b);
avl *newNode(int key);
avl *rightRotate(avl *y);
avl *leftRotate(avl *x);
int getBalance(avl *N);
avl *insert(avl *node, int key);
void preOrder(avl *root);
int posOfNum(avl *root, int data);
avl *search(avl *root, int key);

int main()
{
        avl *root = NULL;
        int count = 1, number;

        while(count <= MAX)
        {
                root = insert(root, count);
                count++;
        }

        printf("------------------- AVL ---------------------\n");
        printf("\nHangi sayiyi bulmak istiyorsun?: ");
        scanf("%d", &number);
        if(search(root, number) == NULL)
                printf("\nSayı bulunamadı.\n\n");
        else
                printf("\n\nSayı bulundu: %d\nErişmek için adım sayısı: %d\n", search(root, number) -> key, posOfNum(root, number));

        return 0;
}

avl *search(avl *root, int key)
{       
        if(root == NULL || root -> key == key) //Eleman bulundu
                return root;
        else if (key > root -> key) //Key kökten büyük ise demek aradığımız sayı kökün sağında aranmalı 
                return search(root -> right, key);
        else if (key < root -> key) //Key kökten küçük ise demek aradığımız sayı kökün solunda aranmalı
                return search(root -> left, key);
        else
                return NULL;
}

int posOfNum(avl *root, int data){
        avl *current = root;
        int count = 0;
        
        while(current -> key != data){
                count++;
                if(current != NULL) {
                        printf("%d -> ", current -> key);
                }
                if(current -> key > data){
                        current = current -> left;
                }
                else {                
                        current = current -> right;
                }		
        }
        if(current -> key == data) printf("<<<< %d >>>>\n",current -> key);
        return count+1;
}

int height(avl *N)
{
	if (N == NULL)
		return 0;
	return N -> height;
}

int max(int a, int b)
{
	return (a > b)? a : b;
}


avl *newNode(int key)
{
	avl *node = (avl*)malloc(sizeof(avl));
	node -> key = key;
	node -> left = NULL;
	node -> right = NULL;
	node -> height = 1; 
	return(node);
}


avl *rightRotate(avl *y)
{
	avl *x = y -> left;
	avl *T2 = x -> right;

	x -> right = y;
	y -> left = T2;
	y -> height = max(height(y -> left), height(y -> right)) + 1;
	x -> height = max(height(x -> left), height(x -> right)) + 1;

	return x;
}


avl *leftRotate(avl *x)
{
	avl *y = x -> right;
	avl *T2 = y -> left;

	y -> left = x;
	x -> right = T2;

	x -> height = max(height(x -> left), height(x -> right)) + 1;
	y -> height = max(height(y -> left), height(y -> right)) + 1;

	return y;
}

int getBalance(avl *N)
{
	if (N == NULL)
		return 0;
	return height(N -> left) - height(N -> right);
}

avl *insert(avl *node, int key)
{
	if (node == NULL)
		return(newNode(key));

	if (key < node -> key)
		node -> left = insert(node -> left, key);
	else if (key > node -> key)
		node->right = insert(node -> right, key);
	else 
		return node;

	node -> height = 1 + max(height(node -> left), height(node -> right));

	int balance = getBalance(node);
	if (balance > 1 && key < node -> left->key)
		return rightRotate(node);

	if (balance < -1 && key > node -> right -> key)
		return leftRotate(node);

	if (balance > 1 && key > node -> left -> key)
	{
		node -> left = leftRotate(node -> left);
		return rightRotate(node);
	}

	if (balance < -1 && key < node -> right -> key)
	{
		node -> right = rightRotate(node -> right);
		return leftRotate(node);
	}

	return node;
}

void preOrder(avl *root)
{
    if(root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}


