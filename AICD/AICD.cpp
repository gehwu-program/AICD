#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

struct Node {
    Node* next;
    Node* prev;
    int value;
};

struct LinkedList {
    Node* head;
    Node* tail;
    int size;
};

void initLinkedList(LinkedList* list) {
    list->head = nullptr;
    list->tail = nullptr;
    list->size = 0;
}

void appendFirst(LinkedList* list, int value) {
    Node* temp = new Node;
    temp->value = value;
    temp->prev = nullptr;
    temp->next = nullptr;

    if (list->head == nullptr) {
        list->head = temp;
        list->tail = temp;
    }
    else {
        temp->next = list->head;
        list->head->prev = temp;
        list->head = temp;
    }
    list->size++;
}

void appendLast(LinkedList* list, int value) {
    Node* temp = new Node;
    temp->value = value;
    temp->prev = nullptr;
    temp->next = nullptr;

    if (list->tail == nullptr) {
        list->head = temp;
        list->tail = temp;
    }
    else {
        temp->prev = list->tail;
        list->tail->next = temp;
        list->tail = temp;
    }
    list->size++;
}

Node* findElement(LinkedList* list, int index) {
    if (index < 0 || index >= list->size) return nullptr;

    Node* temp = list->head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return temp;
}

void removeElement(LinkedList* list, int index) {
    if (index < 0 || index >= list->size) return;

    if (index == 0) {
        Node* temp = list->head;
        list->head = list->head->next;
        if (list->head != nullptr) {
            list->head->prev = nullptr;
        }
        else {
            list->tail = nullptr;
        }
        delete temp;
    }
    else {
        Node* prev = findElement(list, index - 1);
        Node* temp = prev->next;
        prev->next = temp->next;
        if (temp->next != nullptr) {
            temp->next->prev = prev;
        }
        else {
            list->tail = prev;
        }
        delete temp;
    }
    list->size--;
}

void showList(LinkedList* list) {
    Node* temp = list->head;
    while (temp != nullptr) {
        cout << temp->value << " ";
        temp = temp->next;
    }
    cout << endl;
}

void clearList(LinkedList* list) {
    while (list->head != nullptr) {
        Node* temp = list->head;
        list->head = list->head->next;
        delete temp;
    }
    list->tail = nullptr;
    list->size = 0;
}

struct DynamicArray {
    int* data;
    int size;
    int capacity;
};

void initArray(DynamicArray* arr, int capacity) {
    arr->capacity = capacity;
    arr->size = 0;
    arr->data = new int[capacity];
}

void resizeArray(DynamicArray* arr, int newCapacity) {
    int* temp = new int[newCapacity];
    for (int i = 0; i < arr->size; i++) {
        temp[i] = arr->data[i];
    }
    for (int i = arr->size; i < newCapacity; i++) {
        temp[i] = 0;
    }
    delete[] arr->data;
    arr->data = temp;
    arr->capacity = newCapacity;
}

void increaseCapacity(DynamicArray* arr) {
    resizeArray(arr, arr->capacity * 2);
}

void insertElement(DynamicArray* arr, int index, int value) {
    if (index < 0 || index > arr->size) return;

    if (arr->size == arr->capacity) {
        increaseCapacity(arr);
    }

    for (int i = arr->size; i > index; i--) {
        arr->data[i] = arr->data[i - 1];
    }
    arr->data[index] = value;
    arr->size++;
}

void removeElement(DynamicArray* arr, int index) {
    if (index < 0 || index >= arr->size) return;

    for (int i = index; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }
    arr->size--;
}

int getElement(DynamicArray* arr, int index) {
    if (index < 0 || index >= arr->size) return 0;
    return arr->data[index];
}

void clearArray(DynamicArray* arr) {
    delete[] arr->data;
    arr->data = nullptr;
    arr->size = 0;
    arr->capacity = 0;
}

struct StackNode {
    string value;
    StackNode* next;
};

struct Stack {
    StackNode* top;
};

void initStack(Stack* stack) {
    stack->top = nullptr;
}

void pushStack(Stack* stack, string value) {
    StackNode* temp = new StackNode;
    temp->value = value;
    temp->next = stack->top;
    stack->top = temp;
}

void popStack(Stack* stack) {
    if (stack->top == nullptr) return;

    StackNode* temp = stack->top;
    stack->top = stack->top->next;
    delete temp;
}

string topStack(Stack* stack) {
    if (stack->top != nullptr) {
        return stack->top->value;
    }
    return "";
}

bool isEmptyStack(Stack* stack) {
    return stack->top == nullptr;
}

int sizeStack(Stack* stack) {
    int count = 0;
    StackNode* current = stack->top;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

void clearStack(Stack* stack) {
    while (!isEmptyStack(stack)) {
        popStack(stack);
    }
}


int getPriority(string operation) {
    if (operation == "+" || operation == "-")
        return 1;
    if (operation == "*" || operation == "/")
        return 2;
    if (operation == "^")
        return 3;
    if (operation == "sin" || operation == "cos")
        return 4;
    return 0;
}

bool isRightAssociative(string operation) {
    return operation == "^";
}

bool isOperation(string str) {
    return str == "+" || str == "-" || str == "*" || str == "/" || str == "^";
}

bool isFunction(string str) {
    return str == "sin" || str == "cos";
}

bool isNumber(string str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isdigit(c) && c != '.') return false;
    }
    return true;
}

string marshallingYard(string expression) {
    Stack stack;
    initStack(&stack);
    string output = "";
    string token;

    stringstream ss(expression);
    while (ss >> token) {
        if (isNumber(token)) {
            output += token + " ";
        }
        else if (isFunction(token)) {
            pushStack(&stack, token);
        }
        else if (isOperation(token)) {
            while (!isEmptyStack(&stack) &&
                (isOperation(topStack(&stack)) || isFunction(topStack(&stack))) &&
                (getPriority(topStack(&stack)) > getPriority(token) ||
                    (getPriority(topStack(&stack)) == getPriority(token) && !isRightAssociative(token)))) {
                output += topStack(&stack) + " ";
                popStack(&stack);
            }
            pushStack(&stack, token);
        }
        else if (token == "(") {
            pushStack(&stack, token);
        }
        else if (token == ")") {
            while (!isEmptyStack(&stack) && topStack(&stack) != "(") {
                output += topStack(&stack) + " ";
                popStack(&stack);
            }
            popStack(&stack); 
            if (!isEmptyStack(&stack) && isFunction(topStack(&stack))) {
                output += topStack(&stack) + " ";
                popStack(&stack);
            }
        }
    }

    while (!isEmptyStack(&stack)) {
        output += topStack(&stack) + " ";
        popStack(&stack);
    }

    clearStack(&stack);
    return output;
}

double evaluateRPN(string rpnExpression) {
    Stack stack;
    initStack(&stack);
    string token;

    stringstream ss(rpnExpression);
    while (ss >> token) {
        if (isNumber(token)) {
            pushStack(&stack, token);
        }
        else if (isOperation(token) || isFunction(token)) {
            double result = 0;

            if (isFunction(token)) {
                if (isEmptyStack(&stack)) return 0;

                double a = stod(topStack(&stack));
                popStack(&stack);

                if (token == "sin") result = sin(a);
                else if (token == "cos") result = cos(a);
            }
            else {
                if (isEmptyStack(&stack)) return 0;
                double b = stod(topStack(&stack));
                popStack(&stack);

                if (isEmptyStack(&stack)) return 0;
                double a = stod(topStack(&stack));
                popStack(&stack);

                if (token == "+") result = a + b;
                else if (token == "-") result = a - b;
                else if (token == "*") result = a * b;
                else if (token == "/") result = a / b;
                else if (token == "^") result = pow(a, b);
            }

            pushStack(&stack, to_string(result));
        }
    }

    if (!isEmptyStack(&stack)) {
        double result = stod(topStack(&stack));
        clearStack(&stack);
        return result;
    }

    return 0;
}

int main() {
    setlocale(LC_ALL, "RU");
    cout << "Введите выражение (через пробел): " << endl;
    string expression;
    getline(cin, expression);

    string reversePolNotation = marshallingYard(expression);
    cout << "Обратная польская нотация: " << reversePolNotation << endl;

    double result = evaluateRPN(reversePolNotation);
    cout << "Результат: " << result << endl;


    return 0;
}