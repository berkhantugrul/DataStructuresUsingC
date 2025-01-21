#include<stdio.h>
#include<stdlib.h>
# define MAX 200 // max array length is defined as 200

// tree and node values are hold with struct node
struct node
{
    int value;
    struct node *left;
    struct node *right;
};

// functions' definitions
int FindHeight(struct node *root);
struct node *createNewNode(int data);
int getBalance(struct node *root);
struct node *insertTree(int array[], int index, int size);
void print(struct node *root, int level, int array[], int index, int size);
void printByLevel(struct node *root, int array[], int size);


// main function
int main()
{
    int size = 1, value;

    // create array with defined max size
    int array[MAX];
    
    // int *array = (int)malloc(sizeof(int));

    // while value not equal to -2, input repeatly and insert to the array
    scanf("%d", &value);
    while(value != -2)
    {
        array[size] = value;
        size++;

        scanf("%d", &value);
    }

    // create the root
    struct node *root = insertTree(array, 1, size);

    //insertTree(array,index, size);

    // print tree level by level
    printByLevel(root, array, size);

    /*
    // print the normal array
    for (int i=0; i<size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    printf("%d\n", size);*/

    return 0;
}

int FindHeight(struct node *root)
{
    if (root == NULL)
    {
        return 0;
    }

    int right_height = FindHeight(root->right);
    int left_height = FindHeight(root->left);

    // sol yukselik veya sag yukseklik arasindan hangisi buyukse, ona 1 ekle ve al (1 ekleme nedeni root node)
    return 1 + (left_height > right_height ? left_height : right_height);
}

// create the newnode 
struct node *createNewNode(int data)
{
    if (data == -1)
        return NULL;

    struct node * newNode = (struct node *)malloc(sizeof(struct node));
    newNode->value = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// get the balnce factor
int getBalance(struct node *root)
{
    if (root == NULL)
    { 
        return 0;
    }

    int right_balance = FindHeight(root->right);
    int left_balance = FindHeight(root->left);

    return left_balance - right_balance;
}

// inserting the values to the tree
struct node *insertTree(int array[], int index, int size) // index = total number-1
{
    if (index >= size || array[index] == -1)
    {
        return NULL;
    }

    struct node * root = createNewNode(array[index]);
    
    root->left = insertTree(array, 2*index, size);
    root->right = insertTree(array, (2*index)+1, size);

    return root;
}

// print the specific level 
void print(struct node *root, int level, int array[], int index, int size)
{
    if (root == NULL)
    {
        return;
    }

    // print the root level
    if (level == 1)
    {   
        printf("%d", root->value);

        // print childs and relations // no relation of root
        if (index > 1) 
        {
            int parent_index = index / 2;
            printf(" (%d %s)", array[parent_index], (index % 2 == 0) ? "L":"R");
        }
        
        int balance = getBalance(root);
        printf(" (%d B) ", balance);
    }

    else if (level > 1)
    {
        print(root->left, level-1, array, 2 * index, size);
        print(root->right, level-1, array, (2*index)+1, size);
    }
}

// print level-by-level
void printByLevel(struct node *root, int array[], int size)
{
    int height = FindHeight(root);

    for (int i=1; i<height+1; i++)
    {
        print(root, i, array, 1, size);
        printf("\n");
    }
}