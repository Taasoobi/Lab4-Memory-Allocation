#include <stdio.h>
#include <stdlib.h>

struct node{
int id;
int start;
int end;
struct node* link;
}* blockPtr = NULL;

typedef struct node blockType;

int sizePM;
int remaining;
int fitType;


void Params() {
    printf("Enter the size of physical memory: ");
    scanf("%d", &sizePM);
    remaining = sizePM;

    blockPtr = (blockType *)malloc(sizeof(blockType));
    blockPtr->id = -1;
    blockPtr->start = 0;
    blockPtr->end = 0;
    blockPtr->link = NULL;
    printf("Enter hole-fitting algorithm (0 = first fit, 1 = best fit): ");
    scanf("%d", &fitType);
return;
}

void displayTable() {
    blockType* currentPtr = blockPtr->link;
    printf("ID\tStart\tEnd");
    printf("\n------------------\n");
    while (currentPtr != NULL){
        printf("%d\t%d\t%d\n", currentPtr->id, currentPtr->start, currentPtr->end);
        currentPtr = currentPtr->link;
    }
return;
}

void firstFit() {
    int blockID,blockSize; 
    blockType* currentPtr = blockPtr;
    blockType* newBlockPtr;
    int holeStart, holeEnd, holeSize;

    printf("Enter block id: ");
    scanf("%d", &blockID); 
    printf("Enter block size: ");
    scanf("%d", &blockSize); 

    if(blockSize > remaining){
        printf("Not enough memory...");
        return;
    }

    newBlockPtr = (blockType *)malloc(sizeof(blockType));
    newBlockPtr->id = blockID;

    if(blockPtr->link == NULL) {
        newBlockPtr->start = blockPtr->end;
        newBlockPtr->end = newBlockPtr->start + blockSize;
        newBlockPtr->link = NULL;
        blockPtr->link = newBlockPtr;
        remaining -= blockSize;
        return;
    }

    while (currentPtr != NULL){
    
        if (blockID == currentPtr->id){
            printf("Duplicate ID...");
            free(newBlockPtr);
            return;
        }
    currentPtr =currentPtr->link;
    }
    currentPtr = blockPtr;
    while (currentPtr != NULL){
    
    holeStart = currentPtr->end;
        if (currentPtr->link != NULL){
            holeEnd = currentPtr->start;
        } else { 
            holeEnd = sizePM;
        }
        holeSize = holeEnd - holeStart;

        if (blockSize <= holeSize) {
            newBlockPtr->start = holeStart;
            newBlockPtr->end = holeStart + blockSize;
            newBlockPtr->link = currentPtr->link;
            currentPtr->link = newBlockPtr;
            remaining -= blockSize;
            return;
        }
        currentPtr = currentPtr->link;
    }
    printf("Non Fitting Hole");
    return;
}

void bestFit() {
    int blockID,blockSize;
    blockType* currentPtr = blockPtr;
    blockType* newBlockPtr;
    blockType* bestBlockPtr;
    int holeStart, holeEnd, holeSize;
    int oneMinimum = 0;
    int bestCurr;
    bestCurr = sizePM;
    int bestStart;

    printf("Enter block id: ");
    scanf("%d", &blockID);
    printf("Enter block size: ");
    scanf("%d",&blockSize);

    if (blockSize > remaining){
        printf("Not enough memory...");
        return;
    }

    newBlockPtr = (blockType *)malloc(sizeof(blockType));
    newBlockPtr->id = blockID;

    if(blockPtr->link == NULL) {
        newBlockPtr->start = blockPtr->end;
        newBlockPtr->end = newBlockPtr->start + blockSize;
        newBlockPtr->link = NULL;
        blockPtr->link = newBlockPtr;
        remaining -= blockSize;
    return;
    }

    while (currentPtr != NULL){
        if (blockID == currentPtr->id){
            printf("Duplicate ID...");
            free(newBlockPtr);
            return;
        }
        currentPtr =currentPtr->link;
    }

    currentPtr = blockPtr;
    while (currentPtr != NULL){
        holeStart = currentPtr->end;
        if (currentPtr->link!= NULL){
            holeEnd = currentPtr->link->start;
        } else {
            holeEnd = sizePM;
        }
        holeSize = holeEnd - holeStart;
        if (blockSize <= holeSize) {
            oneMinimum = 1;
            if(holeSize < bestCurr) {
                bestCurr = holeSize;
                bestStart = holeStart;
                bestBlockPtr = currentPtr;
            }
        }
        currentPtr = currentPtr->link;
    }
    if(oneMinimum == 0){
        printf("Non Fitting Hole");
        free(newBlockPtr);
        free(bestBlockPtr);
        return;
    }

    newBlockPtr->start = bestStart;
    newBlockPtr->end = newBlockPtr->start + blockSize;
    newBlockPtr->link = bestBlockPtr->link;
    bestBlockPtr->link = newBlockPtr;
    remaining -= blockSize;
    return;
}

void deAllocate() {
    blockType* currentPtr = blockPtr;
    blockType* prevPtr;
    int blockSize,blockID;
    
    printf("Enter block id: ");
    scanf("%d",&blockID);
    while((currentPtr != NULL) && (blockID != currentPtr->id)){
        
        prevPtr = currentPtr;
        currentPtr = currentPtr->link;
    }
    
    if(currentPtr == NULL){
        printf("ID not found...");
        return;
    }
    prevPtr->link = currentPtr->link;
    blockSize = currentPtr->end - currentPtr->start;
    remaining += blockSize;
    free(currentPtr);
return;
}



void deFrag() {
    blockType* currentPtr = blockPtr;
    int blockSize;
    int prevBlockEnd = blockPtr->end;

    while(currentPtr != NULL){
        blockSize = currentPtr->end - currentPtr->start;
        currentPtr->start = prevBlockEnd;
        currentPtr->end = currentPtr->start + blockSize;
        prevBlockEnd = currentPtr->end;
        currentPtr=currentPtr->link;
    }

return;
}

void quitFunc() {
blockType* blockPtr;

    if(blockPtr == NULL){
        return;
    }else{
        quitFunc(blockPtr->link);
    }
    free(blockPtr);
return;
}

int main() {
    //Ctrl + Shift + L
    int inp;
    //sample 1
    //1 1024 1 2 0 128 2 1 320 2 2 224 2 3 288 3 2 2 4 128 3 1 2 2 224 2 5 64 4
    
    //sample 2
    //1 1024 0 2 0 128 2 1 320 2 2 224 2 3 288 3 2 2 4 128 3 1 2 2 224 2 5 64 4

    while (inp != 5){
        printf("\n Memory Allocation ");
        printf("\n--------------------");
        printf("\n 1) Enter parameter ");
        printf("\n 2) Allocate memory for block using Best-fit ");
        printf("\n 3) DeAllocate memory");
        printf("\n 4) Defragment memory for block ");
        printf("\n 5) Quit ");        

        printf("\n\n Enter selection : ");
        scanf("%d",&inp);

        if (inp == 1){
            Params();
        } else if (inp == 2){
            if (fitType == 0){
                firstFit();//First Fit
            } else if (fitType == 1){
                bestFit();//Best Fit
            } else {
                printf("Error. Fit Algorithm Type Undetermined. Restart Program and Choose either 0 or 1 during parameter function.");
            }
            displayTable();
        } else if (inp == 3){
            deAllocate();
            displayTable();
        } else if (inp == 4){
            deFrag();
            displayTable();
        } else if (inp == 5){
            quitFunc();
            inp = 5;
        } else {
            printf("\nEnter a valid number.");
            main();
        }
    }
return 1;
}// end of procedure