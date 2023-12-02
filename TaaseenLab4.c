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
int fitType;


void option1() {
    printf("Enter the size of physical memory: ");
    scanf("%d", &pm_size);
    remaining = pm_size;

    block_ptr = (block_type *)malloc(sizeof(block_type));
    block_ptr->id = -1;
    block_ptr->start = 0;
    block_ptr->end = 0;
    block_ptr->link = NULL;
    printf("Enter hole-fitting algorithm (0 = first fit, 1 = best fit): ");
    scanf("%d", &fitType);
return;
}

void display() {
    block_type* current_ptr = block_ptr->link;
    printf("ID\tStart\tEnd");
    printf("\n------------------\n");
    while (current_ptr != NULL){
        printf("%d\t%d\t%d\n", current_ptr->id, current_ptr->start, current_ptr->end);
        current_ptr = current_ptr->link;
    }
return;
}

void option2() {
    int block_id,block_size; 
    block_type* current_ptr = block_ptr;
    block_type* new_block_ptr;
    int hole_start, hole_end, hole_size;

    printf("Enter block id: ");
    scanf("%d", &block_id); 
    printf("Enter block size: ");
    scanf("%d", &block_size); 

    if(block_size > remaining){
        printf("Not enough memory...");
        return;
    }

    new_block_ptr = (block_type *)malloc(sizeof(block_type));
    new_block_ptr->id = block_id;

    if(block_ptr->link == NULL) {
        new_block_ptr->start = block_ptr->end;
        new_block_ptr->end = new_block_ptr->start + block_size;
        new_block_ptr->link = NULL;
        block_ptr->link = new_block_ptr;
        remaining -= block_size;
        return;
    }

    while (current_ptr != NULL){
    
        if (block_id == current_ptr->id){
            printf("Duplicate ID...");
            free(new_block_ptr);
            return;
        }
    current_ptr =current_ptr->link;
    }
    current_ptr = block_ptr;
    while (current_ptr != NULL){
    
    hole_start = current_ptr->end;
        if (current_ptr->link != NULL){
            hole_end = current_ptr->start;
        } else { 
            hole_end = pm_size;
        }
        hole_size = hole_end - hole_start;

        if (block_size <= hole_size) {
            new_block_ptr->start = hole_start;
            new_block_ptr->end = hole_start + block_size;
            new_block_ptr->link = current_ptr->link;
            current_ptr->link = new_block_ptr;
            remaining -= block_size;
            return;
        }
        current_ptr = current_ptr->link;
    }
    printf("There is no fitting hole");
    return;
}

void option3() {
    int block_id,block_size;
    block_type* current_ptr = block_ptr;
    block_type* new_block_ptr;
    block_type* best_block_ptr;
    int hole_start, hole_end, hole_size;
    int at_least_one = 0;
    int best_so_far;
    best_so_far = pm_size;
    int best_start;

    printf("Enter block id: ");
    scanf("%d", &block_id);
    printf("Enter block size: ");
    scanf("%d",&block_size);

    if (block_size > remaining){
        printf("Not enough memory...");
        return;
    }

    new_block_ptr = (block_type *)malloc(sizeof(block_type));
    new_block_ptr->id = block_id;

    if(block_ptr->link == NULL) {
        new_block_ptr->start = block_ptr->end;
        new_block_ptr->end = new_block_ptr->start + block_size;
        new_block_ptr->link = NULL;
        block_ptr->link = new_block_ptr;
        remaining -= block_size;
    return;
    }

    while (current_ptr != NULL){
        if (block_id == current_ptr->id){
            printf("Duplicate ID...");
            free(new_block_ptr);
            return;
        }
        current_ptr =current_ptr->link;
    }

    current_ptr = block_ptr;
    while (current_ptr != NULL){
        hole_start = current_ptr->end;
        if (current_ptr->link!= NULL){
            hole_end = current_ptr->link->start;
        } else {
            hole_end = pm_size;
        }
        hole_size = hole_end - hole_start;
        if (block_size <= hole_size) {
            at_least_one = 1;
            if(hole_size < best_so_far) {
                best_so_far = hole_size;
                best_start = hole_start;
                best_block_ptr = current_ptr;
            }
        }
        current_ptr = current_ptr->link;
    }
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

void option4() {
    block_type* current_ptr = block_ptr;
    block_type* previous_ptr;
    int block_size,block_id;
    
    printf("Enter block id: ");
    scanf("%d",&block_id);
    while((current_ptr != NULL) && (block_id != current_ptr->id)){
        
        previous_ptr = current_ptr;
        current_ptr = current_ptr->link;
    }
    
    if(current_ptr == NULL){
        printf("ID not found...");
        return;
    }
    previous_ptr->link = current_ptr->link;
    block_size = current_ptr->end - current_ptr->start;
    remaining += block_size;
    free(current_ptr);
return;
}



void option5() {
    block_type* current_ptr = block_ptr;
    int block_size;
    int prev_block_end = block_ptr->end;

    while(current_ptr != NULL){
        block_size = current_ptr->end - current_ptr->start;
        current_ptr->start = prev_block_end;
        current_ptr->end = current_ptr->start + block_size;
        prev_block_end = current_ptr->end;
        current_ptr=current_ptr->link;
    }

return;
}

void option6() {
block_type* block_ptr;

    if(block_ptr == NULL){
        return;
    }else{
        option6(block_ptr->link);
    }
    free(block_ptr);
return;
}

int main() {
    //Ctrl + Shift + L
    int inp;
    while (inp != 6){
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
            option1();
        } else if (inp == 2){
            if (fitType == 0){
                option2();//First Fit
            } else if (fitType == 1){
                option3();//Best Fit
            } else {
                printf("Error. Fit Algorithm Type Undetermined. Restart Program and Choose either 0 or 1 during parameter function.");
            }
            display();
        } else if (inp == 3){
            option4();
            display();
        } else if (inp == 4){
            option5();
            display();
        } else if (inp == 5){
            option6();
            inp = 6;
        } else {
            printf("\nEnter a valid number.");
            main();
        }
    }
return 1;
}// end of procedure