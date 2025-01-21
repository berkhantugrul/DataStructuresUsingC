// 20290369

#include<stdio.h>
# define MAX 1000

int queue[MAX];
int front = -1;
int rear = -1;

void insert(int data)
{
    if (rear == MAX-1)
        printf("Overflow");
    else if (front == -1 && rear == -1)
        front = rear = 0;
    else
        rear++;    

    queue[rear] = data;
}

void dequeue()
{   
    int fvalue, rvalue;
    if (front == -1)
        printf("Underflow");
    else
    {
        fvalue = queue[front];
        rvalue = queue[rear];

        front++;
        rear--;
    }
}

int main()
{
    int num, counter = 0, step = 0, total = 0;

    scanf("%d", &num);

    while(num != -1)
    {
        insert(num);
        counter++;

        scanf("%d", &num);

    }

    scanf("%d", &step);

    int *maxes = (int *)malloc(step * sizeof(int)); //gerekise malloc tanimla
    int *orders = (int *)malloc(step * sizeof(int));


    for (int i=0; i<step; i++)
    {
        if (queue[front] >= queue[rear])
        {
            maxes[i] = queue[front];
            orders[i] = front+1;
            total = total + maxes[i];
        }

        else if (queue[rear] > queue[front])
        {
            maxes[i] = queue[rear];
            orders[i] = rear+1;
            total = total + maxes[i];
        }

        dequeue();

    }

    printf("%d\n", total);
    
    for (int i=0; i<step; i++)
    {
        printf("%d %d\n", maxes[i], orders[i]);
    }
    

    free(orders);
    free(maxes);
    return 0;
}