/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node{
    int data;
    struct Node* prev;
    struct Node* next;
}Node;

Node* createNode(int data) {
    Node* newNode;
    newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}

int isEmpty(Node **head) {
    return head == NULL;
}

void push(int data, Node **head, Node **tail) {
    Node* newNode = createNode(data);

    //Checking linked list is empty or not
    if(*head == NULL) {
        (*head) = newNode;
        (*tail) = newNode;
        return;
    }

    (*head)->prev = newNode;
    newNode->next = (*head);
    (*head) = newNode;
}

void append(int data, Node **head, Node **tail) {
    Node* newNode = createNode(data);

    //Checking linked list is empty or not
    if(*head == NULL) {
        (*head) = newNode;
        (*tail) = newNode;
        return;
    }


    (*tail)->next = newNode;
    newNode->prev = (*tail);
    (*tail) = newNode;
}

void printLinkedList(Node* node) {
    while(node != NULL) {
        printf("%d", node->data);
        node = node -> next;
    }
    printf("\n");
}

void printReverseLinkedList(Node* node) {
    while(node != NULL) {
        printf("%d-->", node->data);
        node = node -> prev;
    }
    printf("NULL\n");
}

void multiplyLL(Node* headMultiplier, Node* tailMultiplier, Node* headMultiplicand, Node* tailMultiplicand, Node **headResult, Node **tailResult, int base) {

    //Creating lookup table
    Node *lookupHead[base];
    Node *lookupTail[base];
    int i;
    for(i = 0; i < base; i++){
        lookupHead[i] = NULL;
        lookupTail[i] = NULL;
    }
    /*
    printf("===============\n");
    printLinkedList(headMultiplier);
    printLinkedList(headMultiplicand);
    printf("%d\n", base);
    printf("===============\n");
    */


    /*
        15 Multiplier
    x    2 Multiplicand
    ------
        30 Product
    */

    Node *currentMultiplicand = tailMultiplicand;
    Node *currentResult = NULL;
    Node *shiftPtr = NULL;
    while(currentMultiplicand) {

        Node *headProduct = NULL;
        Node *tailProduct = NULL;

        if (lookupHead[currentMultiplicand->data] != NULL) {
            headProduct = lookupHead[currentMultiplicand->data];
            tailProduct = lookupTail[currentMultiplicand->data];
        }

        else {
            int multiplyCarry = 0;
            int value;
            Node *currentMultiplier = tailMultiplier;
            while(currentMultiplier) {

                int temp = ((currentMultiplier->data)*(currentMultiplicand->data)+multiplyCarry);
                value = temp % base;
                multiplyCarry = temp / base;
                push(value, &headProduct, &tailProduct);
                if (currentMultiplier == headMultiplier && temp >= base) {
                    push(multiplyCarry, &headProduct, &tailProduct);
                }
                //printf("%d ile %d carpiliyor\n",currentMultiplier->data, currentMultiplicand->data);
                currentMultiplier = currentMultiplier->prev;
            }

            lookupHead[currentMultiplicand->data] = headProduct;
            lookupTail[currentMultiplicand->data] = tailProduct;

        }


        if((*headResult) == NULL) {
            Node *currentProduct = headProduct;
            while(currentProduct != NULL) {
                append(currentProduct->data, headResult, tailResult);
                currentProduct = currentProduct->next;
            }
            shiftPtr = *tailResult;
        }

        else {
            int carry = 0;
            int value;
            int temp;
            /*
            printLinkedList(headResult);
            printLinkedList(headProduct);
            printf("================\n");
            */
            currentResult = shiftPtr->prev;
            while (currentResult != NULL) {
                //printf("Result: %d, Product: %d\n", currentResult->data, tailProduct->data);
                temp = currentResult->data + tailProduct->data + carry;
                value = temp % base;
                carry = temp / base;
                currentResult->data = value;


                tailProduct = tailProduct->prev;
                currentResult = currentResult->prev;
            }

            //Adding last digits like:  the 9's in the product
            /*
              990765 ->Result
            993320   ->Product
           +---------
            */


            while (tailProduct != NULL) {
                temp = tailProduct->data + carry;
                value = temp % base;
                carry = temp / base;
                push(value, headResult, tailResult);
                tailProduct = tailProduct -> prev;
            }

            if (temp >= base) push(carry, headResult, tailResult);

            shiftPtr = shiftPtr->prev;

            /*
            printf("The result is: \t");

            printf("=========\n");
            */
        }


        /*
           361
           323
        ------
          1083
          722
        1083
        ------
        116603
        */


        /*
        printLinkedList(headProduct);
        printf("\t");
        printReverseLinkedList(tailProduct);
        */

        currentMultiplicand = currentMultiplicand->prev;
    }
    //printLinkedList(headResult);
}

void addLL(Node* headAddend, Node* tailAddend, Node* headAdder, Node* tailAdder, Node **headResult, Node **tailResult, int base) {

    int carry = 0;
    int value;
    int temp;
    Node *currentAddend = tailAddend;
    Node *currentAdder = tailAdder;
    while (currentAddend != NULL && currentAdder != NULL) {
        temp = currentAddend->data + currentAdder->data + carry;
        value = temp % base;
        carry = temp / base;
        push(value, headResult, tailResult);
        currentAddend = currentAddend->prev;
        currentAdder = currentAdder->prev;
    }

    while (currentAddend != NULL) {
        temp = currentAddend->data + carry;
        value = temp % base;
        carry = temp / base;
        push(value, headResult, tailResult);
        currentAddend = currentAddend->prev;
    }

    while (currentAdder != NULL) {
        temp = currentAdder->data + carry;
        value = temp % base;
        carry = temp / base;
        push(value, headResult, tailResult);
        currentAdder = currentAdder->prev;
    }

    if (temp >= base) push(carry, headResult, tailResult);

}

void addLL2(Node* head1, Node* tail1, Node* head2, Node* tail2, Node **headResult, Node **tailResult, int base) {

    int carry = 0;
    int value;
    int temp;
    Node *current1 = tail1;
    Node *current2 = tail2;
    while (current1 != NULL || current2 != NULL || carry != 0) {
        int a = (current1 == NULL) ? 0 : current1->data;
        int b = (current2 == NULL) ? 0 : current2->data;
        temp = a + b + carry;
        value = temp % base;
        carry = temp / base;
        push(value, headResult, tailResult);

        if (current1 != NULL) current1 = current1->prev;
        if (current2 != NULL) current2 = current2->prev;





    }

}

void baseConverter(Node* headMultiplier, Node* tailMultiplier,
                   Node* headMultiplicand, Node* tailMultiplicand,
                   Node** headDecimalMultiplier, Node** tailDecimalMultiplier,
                   Node** headDecimalMultiplicand, Node** tailDecimalMultiplicand,
                   Node** headDecimalResult, Node** tailDecimalResult, int base) {

    Node *headBaseNumber = NULL;
    Node *tailBaseNumber = NULL;
    append(base, &headBaseNumber, &tailBaseNumber);

    Node* currentMultiplier = headMultiplier;
    Node* currentMultiplicand = headMultiplicand;

    append(0, headDecimalMultiplier, tailDecimalMultiplier);
    append(0, headDecimalMultiplicand, tailDecimalMultiplicand);
    while (currentMultiplier != NULL || currentMultiplicand != NULL) {


        if (currentMultiplier != NULL) {
            Node* headDigit =NULL ; Node* tailDigit = NULL;
            append(currentMultiplier->data, &headDigit, &tailDigit);

            Node *headProduct = NULL; Node *tailProduct = NULL;
            multiplyLL(*headDecimalMultiplier,*tailDecimalMultiplier, headBaseNumber, tailBaseNumber, &headProduct, &tailProduct, 10);
            Node *headTempResult = NULL; Node *tailTempResult = NULL;
            addLL(headProduct, tailProduct, headDigit, tailDigit, &headTempResult, &tailTempResult, 10);

            *headDecimalMultiplier = headTempResult;
            *tailDecimalMultiplier = tailTempResult;

            currentMultiplier = currentMultiplier->next;
        }

        if (currentMultiplicand != NULL) {

            Node* headDigit =NULL ; Node* tailDigit = NULL;
            append(currentMultiplicand->data, &headDigit, &tailDigit);

            Node *headProduct = NULL; Node *tailProduct = NULL;
            multiplyLL(*headDecimalMultiplicand,*tailDecimalMultiplicand, headBaseNumber, tailBaseNumber, &headProduct, &tailProduct, 10);
            Node *headTempResult = NULL; Node *tailTempResult = NULL;
            addLL(headProduct, tailProduct, headDigit, tailDigit, &headTempResult, &tailTempResult, 10);

            *headDecimalMultiplicand = headTempResult;
            *tailDecimalMultiplicand = tailTempResult;

            currentMultiplicand = currentMultiplicand->next;
        }
    }

    //Multiplying numbers in decimal
    multiplyLL(*headDecimalMultiplier, *tailDecimalMultiplier, *headDecimalMultiplicand, *tailDecimalMultiplicand, headDecimalResult, tailDecimalResult, 10);

}


void createOutputFile(Node* headMultiplier, Node* headMultiplicand, Node* headResult, Node* headDecimalMultiplier, Node* headDecimalMultiplicand, Node* headDecimalResult) {
    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    while (headMultiplier != NULL) {
        fprintf(outputFile, "%d", headMultiplier->data);
        headMultiplier = headMultiplier->next;
    }
    fprintf(outputFile, "\n");

    while (headMultiplicand != NULL) {
        fprintf(outputFile, "%d", headMultiplicand->data);
        headMultiplicand = headMultiplicand->next;
    }
    fprintf(outputFile, "\n");

    while (headResult != NULL) {
        fprintf(outputFile, "%d", headResult->data);
        headResult = headResult->next;
    }
    fprintf(outputFile, "\n");

    while (headDecimalMultiplier != NULL) {
        fprintf(outputFile, "%d", headDecimalMultiplier->data);
        headDecimalMultiplier = headDecimalMultiplier->next;
    }
    fprintf(outputFile, "\n");

    while (headDecimalMultiplicand != NULL) {
        fprintf(outputFile, "%d", headDecimalMultiplicand->data);
        headDecimalMultiplicand = headDecimalMultiplicand->next;
    }
    fprintf(outputFile, "\n");

    while (headDecimalResult != NULL) {
        fprintf(outputFile, "%d", headDecimalResult->data);
        headDecimalResult = headDecimalResult->next;
    }
    fprintf(outputFile, "\n");

    fclose(outputFile);
}

int main(int argc,char* argv[])
{
    if(argc==1)
        printf("Error message!");
    if(argc>=2)
    {

    int base;
    Node *headMultiplier = NULL;
    Node *tailMultiplier = NULL;
    Node *headMultiplicand = NULL;
    Node *tailMultiplicand = NULL;
    Node *headResult = NULL;
    Node *tailResult = NULL;

    //File reading
    FILE* ptr;
    char ch;

    ptr = fopen(argv[1], "r");

    if (NULL == ptr) {
        printf("file can't be opened \n");
    }

    do {
        ch = fgetc(ptr);

        if(ch != '\n') append(ch - '0', &headMultiplier, &tailMultiplier);


        // Checking if character is not EOF.
        // If it is EOF stop eading.
    } while (ch != '\n');

    do {
        ch = fgetc(ptr);
        //printf("%c", ch);
        if(ch != '\n') append(ch - '0', &headMultiplicand, &tailMultiplicand);
        // Checking if character is not EOF.
        // If it is EOF stop eading.
    } while (ch != '\n');

    base = fgetc(ptr) - '0';
    if(base==1) base = 10;

    // Closing the file
    fclose(ptr);


    multiplyLL(headMultiplier, tailMultiplier, headMultiplicand, tailMultiplicand, &headResult, &tailResult, base);

    Node* headDecimalMultiplier = NULL;
    Node* tailDecimalMultiplier = NULL;
    Node* headDecimalMultiplicand = NULL;
    Node* tailDecimalMultiplicand = NULL;
    Node* headDecimalResult = NULL;
    Node* tailDecimalResult = NULL;

    baseConverter(headMultiplier, tailMultiplier, headMultiplicand, tailMultiplicand,
                  &headDecimalMultiplier, &tailDecimalMultiplier,
                  &headDecimalMultiplicand, &tailDecimalMultiplicand,
                  &headDecimalResult, &tailDecimalResult, base);


    printLinkedList(headMultiplier);
    printLinkedList(headMultiplicand);
    printLinkedList(headResult);
    printLinkedList(headDecimalMultiplier);
    printLinkedList(headDecimalMultiplicand);
    printLinkedList(headDecimalResult);


    createOutputFile(headMultiplier, headMultiplicand, headResult, headDecimalMultiplier, headDecimalMultiplicand, headDecimalResult);
}
}
