#include<stdio.h>
#include<stdlib.h>
#include<string.h>

# define MAX 20

struct node // BST definition as struct
{
    int phone;
    char name[20];
    struct node *left;
    struct node *right;
};

struct node *createNewNode(char name[], int phone)
{
    struct node * newNode;
    newNode = (struct node *)malloc(sizeof(struct node));

    //newnode is created and elements are assigned to it
    strcpy(newNode->name, name);
    newNode->phone = phone;
    newNode->left = newNode->right = NULL;

    return newNode;
}

struct node * insertPerson(struct node *root, char name[], int phone)
{
    if (root == NULL)
    {
        return createNewNode(name, phone);
    }
    
    if (phone < root->phone)
    {
        root->left = insertPerson(root->left, name, phone);
    }

    else if (phone > root->phone)
    {
        root->right = insertPerson(root->right, name, phone);
    }

    return root;
}

void inorderTraversal(struct node *root, char names[][MAX], int *index)
{
    if (root != NULL) {
        inorderTraversal(root->left, names, index);
        //printf("%s %d\n", root->name, root->phone);

        // if block
        strcpy(names[*index], root->name);
        (*index)++;

        inorderTraversal(root->right, names, index);
    }
}

// Function for sorting names
int compare(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

// function for compare and print 
int comparePrint(char names[][MAX], int counter)
{
    char search[MAX];

    while(1)
    {
        scanf("%s", search);
        if (strcmp(search, "-1") == 0)
        {
            break;
        }

        int found = 0, searchLength = strlen(search), count = 0; 
        for(int i=0; i<counter; i++)
        {
            // Karakter dizisi bulunan kontrol değişkeni
            if (strncmp(names[i], search, searchLength) == 0) 
            {  // strncmp fonksiyonu, bir string içinde başka bir string arar
                printf("%s\n", names[i]);
                found = 1;  // Karakter dizisi bulundu
                count++;
            }
        }

        if (!found) 
        {
            printf("nobody\n");
            break;
        }

        if (count == 1) 
        {
            break;
        }
    }
}

// Main function definition
int main()
{
    struct node *root = NULL;

    int phone;
    char person_name[MAX];

    // root = insertPerson(root, person_name, phone);

    while (1)
    {
        scanf("%s", person_name);

        if (strcmp(person_name, "-1") == 0)
        {
            break;
        }
        scanf("%d", &phone);

        // Insert to the tree
        root = insertPerson(root, person_name, phone);
    }

    // that array will hold the matched chars - CALISIYOR 
    char names[MAX][MAX];
    int counter = 0;

    inorderTraversal(root, names, &counter); // for taking all names into the array

    qsort(names, counter, sizeof(names[0]), compare); // SIRALAMA CALISIYOR

    // printf("Names: \n");
    // for(int i=0; i<counter; i++)
    // {
    //     printf("%s ", names[i]);
    // }
    // printf("\n");
    
    // while user not entries -1, input the characters

    comparePrint(names, counter);


    return 0;
}