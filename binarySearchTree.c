#include<stdio.h>
#include<stdlib.h>
#define N 1000000

typedef struct TreeNode
{
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
} Tree;

Tree *newNode(int data);  //Düğüm oluşturuyoruz
Tree *arrayToBST(int arr[], int start, int end); 
Tree *search(Tree *root, int key); 
int posOfNum(Tree *root, int data);

int main()
{
	int numArr[N], sNum, count = 0;
        for(int i = 0; i <= N; i++) { numArr[i] = i+1;}
	Tree *root = arrayToBST(numArr, 0, N-1);

	printf("------------------- BFS ---------------------\n");
        printf("\nBulmak istediğiniz sayıyı giriniz: ");
        scanf("%d", &sNum);
        printf("\n");

        if(search(root, sNum) == NULL)
                printf("\nSayı bulunamadı.\n\n");
        else
                printf("\n\nSayı bulundu: %d\nErişmek için adım sayısı: %d\n", search(root, sNum) -> data, posOfNum(root, sNum));

	return 0;
}


int posOfNum(Tree *root, int data){
        Tree *current = root;
        int count = 0;
        
        while(current -> data != data){
                count++;
                if(current != NULL) {
                        printf("%d -> ",current -> data);
                }
                if(current->data > data){
                        current = current -> left;
                }
                else {                
                        current = current -> right;
                }		
        }
        if(current -> data == data) printf("<<<< %d >>>>",current -> data);
        return count+1;
}

Tree *arrayToBST(int arr[], int start, int end)
{
	if (start > end) return NULL;
	int mid = (start + end)/2;

	Tree *root = newNode(arr[mid]);
	root -> left = arrayToBST(arr, start, mid-1);
	root -> right = arrayToBST(arr, mid+1, end);
	return root;
}

Tree *newNode(int data)
{
	Tree *node = (Tree*)malloc(sizeof(Tree));
	node -> data = data;
	node -> left = NULL;
	node -> right = NULL;

	return node;
}

Tree *search(Tree *root, int key)
{       
        if(root == NULL || root -> data == key) //Eleman bulundu
                return root;
        else if (key > root -> data) //Key kökten büyük ise demek aradığımız sayı kökün sağında aranmalı 
                return search(root -> right, key);
        else if (key < root -> data) //Key kökten küçük ise demek aradığımız sayı kökün solunda aranmalı
                return search(root -> left, key);
        else
                return NULL;
}