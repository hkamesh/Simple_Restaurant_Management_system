#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structures for the stack and queue
typedef struct Order {
    int orderID;
    char foodItem[50];
    char customerName[50];
    struct Order* next;
} Order;

typedef struct Queue {
    Order* front;
    Order* rear;
} Queue;

typedef struct Stack {
    Order* top;
} Stack;

// Queue operations
void enqueue(Queue* q, int orderID, char* foodItem, char* customerName) {
    Order* newOrder = (Order*)malloc(sizeof(Order));
    newOrder->orderID = orderID;
    strcpy(newOrder->foodItem, foodItem);
    strcpy(newOrder->customerName, customerName);
    newOrder->next = NULL;
    
    if (q->rear == NULL) {
        q->front = q->rear = newOrder;
    } else {
        q->rear->next = newOrder;
        q->rear = newOrder;
    }
    printf("Order %d placed by %s for %s\n", orderID, customerName, foodItem);
}

Order* dequeue(Queue* q) {
    if (q->front == NULL) {
        printf("No orders in the queue!\n");
        return NULL;
    }
    Order* temp = q->front;
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    return temp;
}

// Stack operations
void push(Stack* s, Order* order) {
    order->next = s->top;
    s->top = order;
    printf("Order %d moved to kitchen for %s\n", order->orderID, order->foodItem);
}

Order* pop(Stack* s) {
    if (s->top == NULL) {
        printf("No orders in the kitchen!\n");
        return NULL;
    }
    Order* temp = s->top;
    s->top = s->top->next;
    return temp;
}

// View pending orders (queue)
void viewPendingOrders(Queue* q) {
    if (q->front == NULL) {
        printf("No pending orders.\n");
        return;
    }
    Order* temp = q->front;
    printf("Pending Orders:\n");
    while (temp != NULL) {
        printf("Order %d: %s placed by %s\n", temp->orderID, temp->foodItem, temp->customerName);
        temp = temp->next;
    }
}

// View processed orders (stack)
void viewProcessedOrders(Stack* s) {
    if (s->top == NULL) {
        printf("No processed orders.\n");
        return;
    }
    Order* temp = s->top;
    printf("Processed Orders:\n");
    while (temp != NULL) {
        printf("Order %d: %s processed for %s\n", temp->orderID, temp->foodItem, temp->customerName);
        temp = temp->next;
    }
}

int main() {
    Queue queue = {NULL, NULL};
    Stack stack = {NULL};
    int choice, orderID;
    char foodItem[50], customerName[50];

    while (1) {
        printf("\n1. Place an Order\n2. Process an Order\n3. View Pending Orders\n4. View Processed Orders\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter Order ID: ");
                scanf("%d", &orderID);
                printf("Enter Food Item: ");
                scanf(" %[^\n]%*c", foodItem);  // Take input with spaces
                printf("Enter Customer Name: ");
                scanf(" %[^\n]%*c", customerName);  // Take input with spaces
                enqueue(&queue, orderID, foodItem, customerName);
                break;
            case 2:
                {
                    Order* order = dequeue(&queue);
                    if (order != NULL) {
                        push(&stack, order);
                    }
                }
                break;
            case 3:
                viewPendingOrders(&queue);
                break;
            case 4:
                viewProcessedOrders(&stack);
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
