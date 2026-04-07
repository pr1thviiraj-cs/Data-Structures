                                        // Circular Queue Implementation 


#include <stdio.h>
#define MAX 5
int queue[MAX];
int front = -1;
int rear = -1;

void enqueue(int value){
    if((rear+1) % MAX == front){               // Check if the queue is full
        printf("Queue Overflow\n");
        return;
    }
    if(front == -1){                  // If the queue is empty, set front and rear to 0
        front = rear = 0;
    }else {
        rear = (rear + 1) % MAX;        // Move rear to the next position in a circular manner
    }
    queue[rear] = value;
}
void dequeue(){
    if(front == -1){
        printf("Queue Underflow\n");
        return;
    }
    printf("Deleted Element: %d\n", queue[front]);
    if(front == rear){                   // If the queue has only one element, reset front and rear to -1
        front = rear = -1;
    }else {
        front = (front + 1) % MAX;           // Move front to the next position in a circular manner
    }
}
void display(){
    if(front == -1){
        printf("Queue is Empty\n");
        return;
    }
    int count = (rear - front + MAX) % MAX + 1;           // Calculate the number of elements in the queue
    for(int i = 0; i < count; i++){                       // Display the elements in the queue from front to rear in a circular manner
        printf("%d ",queue[(front + i) % MAX]);           // Access the elements in a circular manner using modulo operator
    }
    printf("\n");
}
int main(){
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);
     
    display();
    
    dequeue();
    dequeue();
    
    display();
    
    enqueue(60);
    enqueue(70);
    
    display();
    
    return 0;
}
