#include <stdio.h>
#include <stdlib.h>

struct node{
int id;
int start;
int end;
struct node* link;
}* block_ptr = NULL;

typedef struct node block_type;

int pm_size;
int remaining;


void option1() { // change function name
//prompt for size of physical memory
    printf("Enter the size of physical memory: ");
    scanf("%d", &pm_size); // error in this you forgot &
    remaining = pm_size;
//allocate memory for linked list of blocks
    block_ptr = (block_type *)malloc(sizeof(block_type));
//create "dummy" block with id: -1, starting/ending address of 0 and the link of NULL
    block_ptr->id = -1;
    block_ptr->start = 0;
    block_ptr->end = 0;
    block_ptr->link = NULL;
return;
}

void display() { // change function name
    block_type* current_ptr = block_ptr->link;
    printf("ID\tStart\tEnd");
    printf("\n------------------\n"); //error in this
    //print each block in list with while-loop, loop until end of list,
    //advancing "current block" pointer
    // printf("%d\t%d\t%d\n", block_ptr->id, block_ptr->start, block_ptr->end);
    while (current_ptr != NULL){
        printf("%d\t%d\t%d\n", current_ptr->id, current_ptr->start, current_ptr->end);
        current_ptr = current_ptr->link;
    }
return;
}

void option2() {
    int block_id,block_size; // error in this
    block_type* current_ptr = block_ptr;
    block_type* new_block_ptr;
    int hole_start, hole_end, hole_size;

    printf("Enter block id: ");
    scanf("%d", &block_id); // error in this you forgot &
    printf("Enter block size: ");
    scanf("%d", &block_size); // error in this you forgot &
// if block size is larger than remaining memory, print message, return
    if(block_size > remaining){
        printf("Not enough memory...");
        return;
    }
// allocate memory for new block, set block id
    new_block_ptr = (block_type *)malloc(sizeof(block_type));
    new_block_ptr->id = block_id;
// if block list is "empty",
    if(block_ptr->link == NULL) {
        //set fields for new block, link to block list, reduce remaining memory, return
        new_block_ptr->start = block_ptr->end;
        new_block_ptr->end = new_block_ptr->start + block_size;
        new_block_ptr->link = NULL;
        block_ptr->link = new_block_ptr;
        remaining -= block_size;
        // free(new_block_ptr); // main error is here
        return;
    }
// while not end of list, loop
    while (current_ptr != NULL){
    //if duplicate id, print message, return
        if (block_id == current_ptr->id){
            printf("Duplicate ID...");
            free(new_block_ptr);
            return;
        }
    current_ptr =current_ptr->link;
    }
    current_ptr = block_ptr;
    while (current_ptr != NULL){
    //set values for start and end of current hole
    hole_start = current_ptr->end;
        if (current_ptr->link != NULL){
            hole_end = current_ptr->start;
        } else { 
            hole_end = pm_size;
        }
        hole_size = hole_end - hole_start;
// if block fits in hole, set fields for new block, link to block list, reduce remaining memory, return
        if (block_size <= hole_size) {
            new_block_ptr->start = hole_start;
            new_block_ptr->end = hole_start + block_size;
            new_block_ptr->link = current_ptr->link;
            current_ptr->link = new_block_ptr;//......
            remaining -= block_size;
            // free(new_block_ptr); // main error is here
            return;
        }
        // advance "current block" pointer
        current_ptr = current_ptr->link;
    }
// if end of list reached, print message no fitting hole
    printf("hello");
    printf("There is no fitting hole");
    // free(new_block_ptr); // main error is here
    return;
}

void option3() { // change function name
    int block_id,block_size; //error in this
    block_type* current_ptr = block_ptr;
    block_type* new_block_ptr;
    block_type* best_block_ptr;
    int hole_start, hole_end, hole_size;
    int at_least_one = 0;
    int best_so_far;
    best_so_far = pm_size;
    int best_start;

    printf("Enter block id: ");
    scanf("%d", &block_id); // error in this you forgot &
    printf("Enter block size: ");
    scanf("%d",&block_size); // error in this you forgot &

// if block size is larger than remaining memory, print message, return

    if (block_size > remaining){
        printf("Not enough memory...");
        return;
    }

// allocate memory for new block, set block id

    new_block_ptr = (block_type *)malloc(sizeof(block_type));
    new_block_ptr->id = block_id;
// if block list is "empty",
    if(block_ptr->link == NULL) {
    //set fields for new block, link to block list, reduce remaining memory, return
        new_block_ptr->start = block_ptr->end;
        new_block_ptr->end = new_block_ptr->start + block_size;
        new_block_ptr->link = NULL;
        block_ptr->link = new_block_ptr;
        remaining -= block_size;
    // free(new_block_ptr);
    return;
    }

// while not end of list, loop

    while (current_ptr != NULL){
    //if duplicate id, print message, return
        if (block_id == current_ptr->id){
            printf("Duplicate ID...");
            free(new_block_ptr);
            return;
        }
        current_ptr =current_ptr->link;
    }

    current_ptr = block_ptr;
    while (current_ptr != NULL){
//set values for start and end of current hole
        hole_start = current_ptr->end;
        if (current_ptr->link!= NULL){
            hole_end = current_ptr->link->start;
        } else {
            hole_end = pm_size;
        }
        hole_size = hole_end - hole_start;
// if block fits in hole,
        if (block_size <= hole_size) {
    //set flag "at least one" fitting hole found
            at_least_one = 1;
    // if current hole is smaller than best so far
            if(hole_size < best_so_far) {

    // set new value for "best so far", "best start", copy "best block" to current block
                best_so_far = hole_size;
                best_start = hole_start;
                best_block_ptr = current_ptr;
            }
        }
        current_ptr = current_ptr->link;
    }
// if no hole was found large enough, print message, return
    if(at_least_one == 0){
        printf("There is no fitting hole");
        free(new_block_ptr);
        free(best_block_ptr);
        return;
    }

    new_block_ptr->start = best_start;
    new_block_ptr->end = new_block_ptr->start + block_size;
    new_block_ptr->link = best_block_ptr->link;
    best_block_ptr->link = new_block_ptr;
    remaining -= block_size;
    return;
}

void option4() { // change function name
    block_type* current_ptr = block_ptr;
    block_type* previous_ptr;
    int block_size,block_id; // error in this
    
    printf("Enter block id: ");
    scanf("%d",&block_id); // error in this you forgot &
    // while id not found and end of block list not reached
    while((current_ptr != NULL) && (block_id != current_ptr->id)){
        // advance "previous block" pointer and "current block" pointer
        previous_ptr = current_ptr;
        current_ptr = current_ptr->link;
    }
    // if "current block" is NULL, print message id not found
    if(current_ptr == NULL){
        printf("ID not found...");
        return;
    }
    previous_ptr->link = current_ptr->link;
    block_size = current_ptr->end - current_ptr->start;
    remaining += block_size;
    // else remove block, adjusting "previous block" pointer around it, increment remaining memory with block size, free block with matching id
    free(current_ptr);
return;
}



void option5() { // change function name
    block_type* current_ptr = block_ptr;
    int block_size;
    int prev_block_end = block_ptr->end;
    //block_type* current_ptr = block_ptr->link;.....................................................
    // while end of block list not reached

    while(current_ptr != NULL){
        block_size = current_ptr->end - current_ptr->start;
        current_ptr->start = prev_block_end;
        current_ptr->end = current_ptr->start + block_size;
        prev_block_end = current_ptr->end;
        current_ptr=current_ptr->link;
    }
// adjust start and end fields of each block, compacting together
return;
}

void option6() {
block_type* block_ptr;
// if node is NULL return
    if(block_ptr == NULL){
        return;
    }else{
        option6(block_ptr->link);
    }
    free(block_ptr); // error in this you forgot ;
    // else call self on link field of node, free node
return;
}

int main() {
    //Ctrl + Shift + L
    int inp;
    while (inp != 6){
        printf("\n Memory Allocation ");
        printf("\n--------------------");
        printf("\n 1) Enter parameter ");
        printf("\n 2) Allocate memory for block using First-fit ");
        printf("\n 3) Allocate memory for using Best-fit ");
        printf("\n 4) Deallocate memory for block ");
        printf("\n 5) Defragment memory ");
        printf("\n 6) Quit program ");

        printf("\n\n Enter selection : ");
        scanf("%d",&inp);

        if (inp == 1){
            option1();
        } else if (inp == 2){
            option2();
            display();
        } else if (inp == 3){
            option3();
            display();
        } else if (inp == 4){
            option4();
            display();
        } else if (inp == 5){
            option5();
            display();
        } else if (inp == 6){
            option6();
            inp = 6;
        } else {
            printf("\nEnter a valid number.");
        }
    }
/*
    int c;
    while(1){
    printf("\n Memory Allocation ");
    printf("\n--------------------");
    printf("\n 1) Enter parameter ");
    printf("\n 2) Allocate memory for block using First-fit ");
    printf("\n 3) Allocate memory for using Best-fit ");
    printf("\n 4) Deallocate memory for block ");
    printf("\n 5) Defragment memory ");
    printf("\n 6) Quit program ");

    a:
    printf("\n\n Enter selection : ");
    scanf("%d",&c);

switch(c){
case 1:
option1();
break;

case 2:
option2();
display();
break;

case 3:
option3();
display();
break;

case 4:
option4();
display();
break;

case 5:
option5();
display();
break;

case 6:
option6();
break;

default:
printf("\n\n Please enter the correct option ");
goto a;
break;
    }
}
*/

return 1; // indicates success
} // end of procedure