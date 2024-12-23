#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Структура элемента стека
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Функция для создания нового элемента стека
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Функция для добавления элемента в стек
void push(Node** top, int data) {
    Node* newNode = createNode(data);
    newNode->next = *top;
    *top = newNode;
}

// Функция для удаления элемента из стека
int pop(Node** top) {
    if (*top == NULL) {
        printf("Stack is empty! Cannot perform pop.\n");
        return -1;
    }
    Node* temp = *top;
    int poppedData = temp->data;
    *top = (*top)->next;
    free(temp);
    return poppedData;
}

// Функция для проверки, пуст ли стек
bool isEmpty(Node* top) {
    return top == NULL;
}

// Функция для получения верхнего элемента стека
int peek(Node* top) {
    if (isEmpty(top)) {
        printf("Stack is empty!\n");
        return -1;
    }
    return top->data;
}

// Функция для очистки стека
void clearStack(Node** top) {
    while (!isEmpty(*top)) {
        pop(top);
    }
    printf("Stack successfully cleared.\n");
}

// Функция для подсчета количества элементов в стеке
int countStack(Node* top) {
    int count = 0;
    Node* current = top;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Функция для вывода всех элементов стека
void printStack(Node* top) {
    if (isEmpty(top)) {
        printf("Stack is empty.\n");
        return;
    }
    Node* current = top;
    printf("Stack elements: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Функция для сохранения стека в файл
void saveStackToFile(Node* top, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Failed to open file for writing.\n");
        return;
    }
    Node* current = top;
    while (current != NULL) {
        fprintf(file, "%d\n", current->data);
        current = current->next;
    }
    fclose(file);
    printf("Stack saved to file '%s'.\n", filename);
}

// Функция для загрузки стека из файла
void loadStackFromFile(Node** top, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open file for reading.\n");
        return;
    }
    int data;
    clearStack(top);
    while (fscanf(file, "%d", &data) != EOF) {
        push(top, data);
    }
    fclose(file);
    printf("Stack loaded from file '%s'.\n", filename);
}

// Функция для отображения меню
void showMenu() {
    printf("\nMenu:\n");
    printf("1. Push an element onto the stack\n");
    printf("2. Pop an element from the stack\n");
    printf("3. View the top element of the stack\n");
    printf("4. Check if the stack is empty\n");
    printf("5. Count the number of elements in the stack\n");
    printf("6. Print all elements in the stack\n");
    printf("7. Save the stack to a file\n");
    printf("8. Load the stack from a file\n");
    printf("9. Clear the stack\n");
    printf("0. Exit\n");
}

// Главная функция для тестирования реализации стека
int main() {
    Node* stack = NULL; // Инициализация пустого стека
    int choice, value;
    char filename[100];

    do {
        showMenu();
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to push: ");
                scanf("%d", &value);
                push(&stack, value);
                printf("Element %d pushed onto the stack.\n", value);
                break;

            case 2:
                value = pop(&stack);
                if (value != -1) {
                    printf("Popped element: %d\n", value);
                }
                break;

            case 3:
                value = peek(stack);
                if (value != -1) {
                    printf("Top element: %d\n", value);
                }
                break;

            case 4:
                if (isEmpty(stack)) {
                    printf("Stack is empty.\n");
                } else {
                    printf("Stack is not empty.\n");
                }
                break;

            case 5:
                printf("Number of elements in the stack: %d\n", countStack(stack));
                break;

            case 6:
                printStack(stack);
                break;

            case 7:
                printf("Enter the filename: ");
                scanf("%s", filename);
                saveStackToFile(stack, filename);
                break;

            case 8:
                printf("Enter the filename: ");
                scanf("%s", filename);
                loadStackFromFile(&stack, filename);
                break;

            case 9:
                clearStack(&stack);
                break;

            case 0:
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid input! Please try again.\n");
                break;
        }
    } while (choice != 0);

    clearStack(&stack);
    return 0;
}
