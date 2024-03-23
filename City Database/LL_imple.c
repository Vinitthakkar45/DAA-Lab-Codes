#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct Node {
    char *arr;
    int x;
    int y;
    struct Node* next;
};


struct Node* createNode(char city[], int x, int y);
void printdet(struct Node* node);
struct Node* insert(struct Node* head, struct Node* node);
struct Node* deleteCity(struct Node* head, char city[]);
struct Node* deleteCoordinate(struct Node* head, int x, int y);
void searchCity(struct Node* head, char city[]);
void searchCoordinate(struct Node* head, int x, int y);
int calculateDistance(int x1, int y1, int x2, int y2);
void printLL(struct Node* head, int distance, int x, int y);


struct Node* createNode(char city[], int x, int y) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->arr = (char*)malloc(strlen(city) + 1);
    strcpy(node->arr, city);
    node->x = x;
    node->y = y;
    node->next = NULL;
    return node;
}

void printdet(struct Node* node) {
    printf("City Name: %s\n", node->arr);
    printf("Co-ordinates : (%d , %d)\n", node->x, node->y);
    printf("\n");
}

struct Node* insert(struct Node* head, struct Node* node) {
    if (head == NULL) {
        return node; 
    }
    node->next = head; 
    return node;
}

struct Node* deleteCity(struct Node* head, char city[]) {
    if (strcmp(head->arr, city) == 0) {
        head = head->next;      
        return head;      
    }
    struct Node* curr = head;
    while (curr->next != NULL && strcmp(curr->next->arr, city) != 0) {
        curr = curr->next;
    }
    if (curr->next == NULL) {
        return head;
    }
    curr->next = curr->next->next;
    return head;
}

struct Node* deleteCoordinate(struct Node* head, int x, int y) {
    if (head->x == x && head->y == y) {
        head = head->next;      
        return head;      
    }
    struct Node* curr = head;
    while (curr->next != NULL && (curr->next->x != x || curr->next->y != y)) {
        curr = curr->next;
    }
    if (curr->next == NULL) {
        return head;
    }
    curr->next = curr->next->next;
    return head;
}

void searchCity(struct Node* head, char city[]) {
    struct Node* curr = head;
    while (curr != NULL && strcmp(curr->arr, city) != 0) {
        curr = curr->next;
    }
    if (curr == NULL) {
        printf("No such city Found!\n");
        return;
    }
    printdet(curr);
}

void searchCoordinate(struct Node* head, int x, int y) {
    struct Node* curr = head;
    while (curr != NULL && (curr->x != x || curr->y != y)) {
        curr = curr->next;
    }
    if (curr == NULL) {
        printf("No such Co-ordinates Found!\n");
        return;
    }
    printdet(curr);
}

int calculateDistance(int x1, int y1, int x2, int y2) {
    int sum1 = pow(x2 - x1, 2);
    int sum2 = pow(y2 - y1, 2);
    return sqrt(sum1 + sum2);
}

void printLL(struct Node* head, int distance, int x, int y) {
    struct Node* curr = head;
    while (curr != NULL) {
        int ans = calculateDistance(curr->x, curr->y, x, y);
        if (ans <= distance) {
            printf("Distance from city : %d \n",ans);
            printdet(curr);
        }
        curr = curr->next;
    }
}

int main() {
    struct Node* head = NULL;
    int choice;

    do {
        printf("Enter your choice:\n");
        printf("1. Insert a city\n");
        printf("2. Details of cities with distance less than a distance of your choice from given point of your choice\n");
        printf("3. Search a city\n");
        printf("4. Search by coordinates and Pint details\n");
        printf("5. Delete a city\n");
        printf("6. Search by coordinates and Delete\n");
        printf("7. Exit\n");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
            {
                char cityName[100];
                int x, y;
                printf("Enter city name: ");
                scanf("%s", cityName);
                printf("Enter coordinates (x y): ");
                scanf("%d %d", &x, &y);
                head = insert(head, createNode(cityName, x, y));
                printf("City inserted!\n");
            }
                break;
            case 2:
            {   int dist,xd,yd;
                printf("Enter sepcified distance: ");
                scanf("%d", &dist);
                printf("Enter coordinates (x y) to find distace from all cities: ");
                scanf("%d %d", &xd, &yd);
                printf("Details of cities with distance less than given distance %d from given point!\n",dist);
                printLL(head, dist, xd, yd);
            }
                break;
            case 3:
            {
                printf("Enter the city name to search : ");
                char cityToSearch[100];
                scanf("%s", cityToSearch);
                searchCity(head, cityToSearch);
                printf("City Found!\n");
            }
                break;
            case 4:
            {
                printf("Enter coordinates to search and print details of (x y): ");
                int xToSerach, yToSearch;
                scanf("%d %d", &xToSerach, &yToSearch);
                searchCoordinate(head, xToSerach, yToSearch);
                printf("City Found!\n");
            }
                break;
            case 5:
            {
                printf("Enter the city name to search and delete: ");
                char cityToDelete[100];
                scanf("%s", cityToDelete);
                searchCity(head, cityToDelete);
                head = deleteCity(head, cityToDelete);
                printf("Deletion Done!\n");
            }
                break;
            case 6:
            {
                printf("Enter coordinates to search and delete (x y): ");
                int xToDelete, yToDelete;
                scanf("%d %d", &xToDelete, &yToDelete);
                searchCoordinate(head, xToDelete, yToDelete);
                head = deleteCoordinate(head, xToDelete, yToDelete);
                printf("Deletion Done!\n");
            }
                break;
            
            case 7:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 7);

    return 0;
}
