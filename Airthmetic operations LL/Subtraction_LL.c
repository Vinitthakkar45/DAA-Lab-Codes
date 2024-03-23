#include <stdio.h>
#include <stdlib.h>

struct Node {
    long value;
    struct Node* next;
};

struct Node* createNode(long value) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->value = value;
    node->next = NULL;
    return node;
}

void printLL(struct Node* node) {
    while (node != NULL) {
        printf("%ld", node->value);
        node = node->next;
    }
}

struct Node* createLinkedList(long num) {
    struct Node* head = NULL;
    struct Node* tail = NULL;

    while (num > 0) {
        long temp = num % 10;
        struct Node* newNode = createNode(temp);
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        num /= 10;
    }
    return head;
}

struct Node* Subtraction(struct Node* head1, struct Node* head2) {
    struct Node* head = NULL;
    struct Node* tail = NULL;
    int borrow = 0;

    while (head1 != NULL || head2 != NULL) {
        long val1 = (head1 != NULL) ? head1->value : 0;
        long val2 = (head2 != NULL) ? head2->value : 0;

        long diff = val1 - val2 - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        struct Node* newNode = createNode(diff);
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        if (head1 != NULL) head1 = head1->next;
        if (head2 != NULL) head2 = head2->next;
    }

    // If there's a remaining borrow, it becomes a negative result
    if (borrow == 1) {
        printf("Error: Negative result not supported for subtraction.\n");
        return NULL;
    }
    return head;
}

struct  Node* reverseLL(struct Node* head){
    struct Node* prev=NULL;
    struct Node* next=NULL;
    struct Node* current=head;
    
    while(current!=NULL){
        next=current->next;
        current->next=prev;
        prev=current;
        current=next;
    }
    return prev;
}


int main() {
    long num1, num2;
    printf("Enter number 1: ");
    scanf("%ld", &num1);
    printf("Enter number 2: ");
    scanf("%ld", &num2);

    struct Node* head1 = createLinkedList(num1);
    printLL(head1);
    printf("\n");

    struct Node* head2 = createLinkedList(num2);
    printLL(head2);
    printf("\n");

    struct Node* head3 = Subtraction(head1, head2);
    printLL(head3);
    printf("\n");

    head3=reverseLL(head3);
    if(head3!=NULL){
        printf("Answer after reversing Linked List:\n");
        printLL(head3);
    }

    while (head1 != NULL) {
        struct Node* temp = head1;
        head1 = head1->next;
        free(temp);
    }

    while (head2 != NULL) {
        struct Node* temp = head2;
        head2 = head2->next;
        free(temp);
    }

    while (head3 != NULL) {
        struct Node* temp = head3;
        head3 = head3->next;
        free(temp);
    }

    return 0;
}