#include <stdio.h>
#include <stdlib.h>

// Kırmızı-Siyah Ağacı düğüm renkleri
typedef enum { RED, BLACK } Color;

// Kırmızı-Siyah Ağacı düğüm yapısı
typedef struct Node {
    int data;                // Düğümün değeri
    Color color;             // Düğümün rengi (RED veya BLACK)
    struct Node *left, *right, *parent; // Sol, sağ ve ebeveyn düğümleri
} Node;

Node *root = NULL; // Ağacın kök düğümü

// Yeni bir düğüm oluşturma fonksiyonu
Node *createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = RED; // Yeni düğümler başlangıçta kırmızı olur
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

// Ağacı sola döndürme işlemi
void rotateLeft(Node **root, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Ağacı sağa döndürme işlemi
void rotateRight(Node **root, Node *y) {
    Node *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

// Ağaca düğüm ekledikten sonra Kırmızı-Siyah özelliklerini koruma
void fixInsert(Node **root, Node *z) {
    while (z->parent && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotateLeft(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateRight(root, z->parent->parent);
            }
        } else {
            Node *y = z->parent->parent->left;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotateRight(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateLeft(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

// Ağaca yeni bir düğüm ekleme
void insert(Node **root, int data) {
    Node *z = createNode(data);
    Node *y = NULL;
    Node *x = *root;

    while (x != NULL) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == NULL)
        *root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    fixInsert(root, z);
}

// Ağacı inorder sıralama ile yazdırma
void inorder(Node *root) {
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d\n", root->data);

    inorder(root->right);
}

// Ağacı seviyelere göre yazdırma (level order traversal)
void printLevelOrder(Node *root) {
    if (root == NULL)
        return;

    // Kuyruk veri yapısını oluştur
    Node **queue = (Node **)malloc(1000 * sizeof(Node *));
    int front = 0, rear = 0;

    queue[rear++] = root; // Kök düğümü kuyruğa ekle
    printf("\n");
    while (front < rear) {
        int levelSize = rear - front; // Mevcut seviyedeki düğüm sayısı

        for (int i = 0; i < levelSize; i++) {
            Node *current = queue[front++];
            printf("%d %c", current->data, current->color == RED ? 'R' : 'B');

            if (current->parent != NULL) {
                printf(" (%d %c)", current->parent->data,
                       current == current->parent->left ? 'L' : 'R');
            }
            printf(" ");

            // Çocukları kuyruğa ekle
            if (current->left)
                queue[rear++] = current->left;
            if (current->right)
                queue[rear++] = current->right;
        }
        printf("\n"); // Bir sonraki seviyeye geç
    }

    free(queue); // Kuyruğu temizle
}

int main() {
    int data;

    while (1) {
        scanf("%d", &data);
        if (data == -1)
            break;
        insert(&root, data);
    }

    inorder(root);

    printLevelOrder(root);

    return 0;
}
