#include <stdio.h>
#include <stdlib.h>

struct Node {
    long value;
    struct Node* next;
};

struct LL_of_Pointers {
    struct Node* PTR;
    struct LL_of_Pointers* NEXT;
};

struct LL_of_Pointers* createLinkedList_of_Pointers(struct Node* ptr) {
    struct LL_of_Pointers* newNode = (struct LL_of_Pointers*)malloc(sizeof(struct LL_of_Pointers));
    newNode->PTR = ptr;
    newNode->NEXT = NULL;

    return newNode;
}

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

struct Node* createLinkedList(int num) {
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

struct Node* Addition(struct Node* num1, struct Node* num2) {
    struct Node* head = NULL;
    struct Node* tail = NULL;
    long carry = 0;

    while (num1 != NULL && num2 != NULL) {
        long temp1 = num1->value + num2->value + carry;
        long temp2 = temp1 % 10;
        carry = temp1 / 10;

        struct Node* newNode = createNode(temp2);
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        num1 = num1->next;
        num2 = num2->next;
    }

    while (num1 != NULL) {
        long temp1 = num1->value + carry;
        long temp2 = temp1 % 10;
        carry = temp1 / 10;

        struct Node* newNode = createNode(temp2);
        tail->next = newNode;
        tail = newNode;
        num1 = num1->next;
    }

    while (num2 != NULL) {
        int temp1 = num2->value + carry;
        int temp2 = temp1 % 10;
        carry = temp1 / 10;

        struct Node* newNode = createNode(temp2);
        tail->next = newNode;
        tail = newNode;
        num2 = num2->next;
    }

    if (carry > 0) {
        struct Node* newNode = createNode(carry);
        tail->next = newNode;
        tail = newNode;
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




struct LL_of_Pointers* Multiplication(struct Node* num1, struct Node* num2) {
    struct LL_of_Pointers* HEAD = NULL;
    struct LL_of_Pointers* TAIL = NULL;

    while (num2 != NULL) {
        struct Node* head = NULL;
        struct Node* tail = NULL;
        int carry = 0;
        struct Node* currentNum1 = num1;

        while (currentNum1 != NULL) {
            long temp1 = currentNum1->value * num2->value + carry;
            long temp2 = temp1 % 10;
            carry = temp1 / 10;

            struct Node* newNode = createNode(temp2);
            if (head == NULL) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }

            currentNum1 = currentNum1->next;  
        }

        if (carry > 0 && currentNum1 == NULL) {
            struct Node* carryNode = createNode(carry);
            tail->next = carryNode;
            tail = carryNode;
        }

        struct LL_of_Pointers* newNode = createLinkedList_of_Pointers(head);
        printf("Multiplication Result for this step: ");
        printLL(newNode->PTR);
        printf("\n"); 
        
        if (HEAD == NULL) {
            HEAD = newNode;
            TAIL = newNode;
        } else {
            TAIL->NEXT = newNode;
            TAIL = newNode;
        }

        num2 = num2->next;
    }

    return HEAD;
}



void insertAtBeginning(struct Node** head_ref, long new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    new_node->value = new_data;
    
    new_node->next = *head_ref;
    *head_ref = new_node; 
}


struct Node* AddPtr(struct LL_of_Pointers* head) {
    struct Node* result = head->PTR;
    long count=1;

    struct LL_of_Pointers* ptr=head->NEXT;

    while(ptr!=NULL){
        struct Node* ptrr=ptr->PTR;
        for(long i=0;i<count;i++){
            insertAtBeginning(&ptrr,0);
        }
        count++;

        result=Addition(result,ptrr);
        ptr=ptr->NEXT;
    }
    return result;

}


int main() {
    long num1, num2;
    printf("Enter number 1: ");
    scanf("%ld", &num1);

    printf("Enter number 2: ");
    scanf("%ld", &num2);

    if(num1<=0 || num2<=0){
        printf(" 0 se bada daal");
        return 0;
    }
    

    struct Node* head1 = createLinkedList(num1);
    printf("Linked List for Number 1: ");
    printLL(head1);
    printf("\n");

    struct Node* head2 = createLinkedList(num2);
    printf("Linked List for Number 2: ");
    printLL(head2);
    printf("\n");



    struct LL_of_Pointers* head3 = Multiplication(head1, head2);

    struct Node* ans = AddPtr(head3);
    
    printf("Result after Multiplication of Pointers:\n");
    printLL(ans);
    printf("\n");
    printf("\n");

    ans = reverseLL(ans);
    printf("Answer after reversing Linked List:\n");
    printf("--------------------------------------------------\n \n");
    printLL(ans);
    printf("\n");
    printf("\n");

    return 0;
}