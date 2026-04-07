            // LINEAR QUEUE IMPLEMENTATION

#include <stdio.h>
#define MAX 5
int queue[MAX];
int front = -1;
int rear = -1;

void enqueue(int value){
    if(rear == MAX - 1){                       // Check if the queue is full
        printf("Queue Overflow \n");
        return;
    }
    if(front == -1){                           // If the queue is empty, set front to 0
        front = 0;
    }
        rear++;
        queue[rear] = value;                   // Insert the value at the rear of the queue
    }
void dequeue(){                                // Remove an element from the front of the queue
    if(front == -1 || front > rear){           // Check if the queue is empty
        printf("Queue Underflow \n");
        return;
    }
    printf("Deleted: %d\n", queue[front]);
       front++;
       
    if(front > rear){                         // If the queue becomes empty after deletion, reset front and rear
        front = rear -1;
    }
}
void display(){
    if(front == -1){                          // Check if the queue is empty
        printf("Queue is Empty \n"); 
    }
    for(int i = front; i <= rear; i++){       // Display the elements in the queue from front to rear
        printf("%d ", queue[i]);
       } printf("\n");
    }
    int main(){ 
        enqueue(10);
        enqueue(20);
        enqueue(30);                          // Enqueue some elements into the queue
        enqueue(40);
        enqueue(50);
        
        display();
        
        dequeue();
        dequeue();                           // Dequeue two elements from the queue
         
        display();                       
        enqueue(60);
        return 0;
    }
