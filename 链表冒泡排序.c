#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct node
{
    int data;

    struct node *next;
};

typedef struct node Node, *NODE;

void add(NODE h);
void sort(NODE h);
void printAll(NODE h);

int main()
{
    NODE head;
    head = (NODE)malloc(sizeof(Node));
    head->next = NULL;

    add(head);

    sort(head);

    printAll(head);

    return 0;
}

/*void add(NODE prev)
{
    char keyInput = 'y';

    printf("input a number\n>>>");
    scanf("%d", &prev->data);
    printf("continue? 'y' or 'n'\n>>>");
    scanf(" %c", &keyInput);

    while (keyInput == 'y' || keyInput == 'Y')
    {

        NODE curr;
        curr = (NODE)malloc(sizeof(Node));
        
        curr->next = prev->next;
        prev->next = curr;


        printf("input a number\n>>>");
        scanf("%d", &curr->data);

        printf("continue? 'y' or 'n'\n>>>");
        scanf(" %c", &keyInput);

        prev = curr;
    }
}*/
void add(NODE prev)
{
    int keyInput = 0;

    printf("input a number\n>>>");
    scanf("%d", &prev->data);

    while (1)
    {
        printf("input a number\n>>>");
        scanf("%d", &keyInput);

        if (keyInput == -1)
            break;


        NODE curr;
        curr = (NODE)malloc(sizeof(Node));

        curr->next = prev->next;
        prev->next = curr;

        curr->data = keyInput;
        
        prev = curr;
    }
}

void printAll(NODE h)
{
    while (h != NULL)
    {
        printf("%d ", h->data);

        h = h->next;
    }
}

void sort(NODE h)
{
    if (h->next == NULL)
        return;

    int t;
    sort(h->next);
    while (h->next != NULL)
    {
        if(h->data < h->next->data)
        {
            t = h->data;
            h->data = h->next->data;
            h->next->data = t;
        }       
        h = h->next;
    }
    
}
