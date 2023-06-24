#include<stdio.h>
#include<stdlib.h>

// STUDENT NAME: BARIÞ GÝRAY AKMAN


typedef struct LinkedList{
	
	int data;
	struct LinkedList *next;
}LinkedList;




// This function prints the numbers constructed by the program.
// Moreover, this function prints values achieved onto the file.
void printNum(LinkedList* temp, FILE *fPtr){
	while(temp!=NULL){
		printf("%d", temp->data);
		fprintf(fPtr, "%d", temp->data);
		temp = temp->next;
	}
	fprintf(fPtr, "\n");
	
}

// This function deletes zeros exist in front of numbers.
LinkedList* delete_zeros(LinkedList* head){
	
	LinkedList* previous;
	// Loop goes on until our data attribute is not equal to zero.
	// Each node which includes 0 as a data attribute will be deleted in the list.
	while(head->data ==0){
		previous = head;
		head= head->next;
		free(previous);
	}
		
	return head;
}


// This function converts the number to inverse position.
LinkedList* inverse_number(LinkedList* temp){
	LinkedList* tail=(LinkedList*)malloc(sizeof(LinkedList));
	tail->next=NULL;
	LinkedList* temp2;
	int length = 0;
	while(temp!=NULL){
		temp2=(LinkedList*)malloc(sizeof(LinkedList));
		tail->data = temp->data;
		temp2->next=tail;
		tail= temp2;
		temp = temp->next;
		length++;
	}
	
	tail= tail->next;
	return tail;
	
}
// This function constructs linked list in a size wished in parameter section.
LinkedList* constructLinkedList(int length){
	LinkedList* head =  (LinkedList*)malloc(sizeof(LinkedList));
	LinkedList* temp = head;
	int i;
	for(i=0;i<length;i++){
		
		temp->data = 0;
		if(i==length-1)
			temp->next=NULL;
		
		else  temp->next = (LinkedList*)malloc(sizeof(LinkedList));

		temp = temp->next;
			
	}
	return head;
	
}

// This function convert number in any base to base 10.
LinkedList* convert_to_ten_base(LinkedList* head, int base, int length){
	
	LinkedList* result = constructLinkedList(length);
	result->data = 0;
	
	int carry = 0;
	while(head){
		
		LinkedList* temp = result;
		
		carry = 0;
		while(temp){
			temp->data = (temp->data *base + carry);
			carry = temp->data /10; 
			temp->data = temp->data %10;
			
		
			temp = temp->next;
		}
		temp = result; 
		temp->data = (temp->data + head->data);
		
		carry = temp->data / 10; 
		temp->data = temp->data % 10;
		temp = temp->next;
		while(temp && carry !=0){
			temp->data = (temp->data + carry);
			carry = temp->data/ 10;
			temp->data = temp->data % 10;
			temp = temp->next;
		}
		head = head->next;
	}
	
	return result;
}

// This function multiplies two numbers entered as parameter in base entered as a paarameter.
LinkedList* multiply(LinkedList* head1, LinkedList* head2, int length, int base){
	
	int i;
	int carry = 0;
	int carry2 = 0;
	LinkedList* temp = head1;
	LinkedList* temp2 = head2;
	LinkedList* result = constructLinkedList(length);
	LinkedList* result2 = result;
	LinkedList* temp3 = result;
	int holder = 0;
	
	
	while(head2){
		temp3 = result2;
		temp = head1;
		carry = 0;
		carry2 = 0;
		while(temp){
			
			// Modulo of the process below will be our current digit. Carry will be added to the next node.
			// That process will go until the end iteratively.
			
			// Two carry is used in that code. One of them is achieved during the multiplication. 
			// Second carry is used for summing the results achieved by multiplication of all digits of second number distinctively with all digits of the first number.
			temp3->data = (temp3->data+(temp->data*head2->data+carry )% base+ carry2);
			
			
			carry2 = temp3->data / base;
			temp3->data = temp3->data % base;
			
			carry = (temp->data*head2->data+carry) / base;
			

			temp3 = temp3->next;
			
			if(temp->next==NULL){

				temp3->data = (temp3->data +carry+carry2);
				carry2 = temp3->data /base;
				temp3->data = temp3->data % base;
				if(carry2 !=0)
					temp3->next->data = carry2;
			}  
			    
				

			temp= temp->next;
			
		}
		head2 = head2->next;
		result2 = result2->next;
	}
	return result;
	
}

int main(int argc,char* argv[]){
	
	
		FILE *fPtr;
		// Initially, file is read according to txt file name entered.
	 	if(argc==1)
        	printf("Error message!\n");
    
    	if(argc>=2){
	    	int num_length = 0;
			fPtr = fopen(argv[1], "r");
		}
		else fPtr = fopen("input.txt", "r");
		char c;
		int line_num = 1;
		int isHead = 0;
		LinkedList *head = (LinkedList*)malloc(sizeof(LinkedList));
		LinkedList *ptr1 = head;
		int base = 0;
		LinkedList *head2 = (LinkedList*)malloc(sizeof(LinkedList));
		LinkedList *ptr2 = head2;
		LinkedList *previous = NULL;
		int num_length =0;
		int base_digit_count = 0;
		
		// According to line_num variable, first and second numbers are constructed by two distinct linked list structures.
		// After the construction of each linked lists, line_num varaible will be increased by 1. This process will go through until the end of the file.
		
		while(c != EOF){
			c = fgetc(fPtr);
			
			// If character gotten by fgetc is not equal to \n, line number will be increased by 1. And previous node will be constructed.
			if(c =='\n'){
				previous->next=NULL;
				line_num++;
			}
				
			
			else{
				
				// According to line number, if structure will be executed. 
				// If line number is equal to 1, first linked list will be constructed. 
				// If line number is equal to 2, second linked list will be constructed.
				
				// If line number is equal to 3, base will be specified. 
				if(line_num == 3){
					if(base==0) base =(int)c -48;
					
					else base =10;
						
					base_digit_count++;
					
				}
					
				else if(line_num == 1){
	
					ptr1->data = (int)c -48;
					ptr1->next = (LinkedList*)malloc(sizeof(LinkedList));
					previous = ptr1;
					ptr1 = ptr1->next;
					ptr1->next = NULL;
					num_length++;
				
				}
				else if(line_num == 2){
					ptr2->data = (int)c -48;
					ptr2->next = (LinkedList*)malloc(sizeof(LinkedList));
					previous = ptr2;
					ptr2 = ptr2->next;
					ptr2->next = NULL;
					num_length++;
				
				}
			}
		}
		fPtr = fopen("output.txt", "w");
		// Values achieved are printed in that section.
		printf("         ");
		printNum(head, fPtr);
		printf("\n");
		printf("         ");
		printNum(head2, fPtr);
		printf("\n");
		printf("x");
		printf("_____________\n");
		printf("\n");
		
		// Multiplication process
		LinkedList* result = multiply(inverse_number(head), inverse_number(head2), ++num_length, base);
		
		// Zeros in front of number are deleted.
		result = delete_zeros(inverse_number(result));
		printf("\nResult in base %d: ", base);
		printNum(result, fPtr);
		printf("\n");
		// Converting and displaying results on the console
		head = convert_to_ten_base(head, base, ++num_length);
		head2 = convert_to_ten_base(head2, base, ++num_length);
		head = inverse_number(head);
		head2 = inverse_number(head2);
		head = delete_zeros(head);
		head2 = delete_zeros(head2);
		printf("\n\nMultiplier in decimal: ");
		printNum(head, fPtr);
		printf("\n\nMultiplicant in decimal:");
		printNum(head2, fPtr);
		// From any base to decimal conversion process
		result = convert_to_ten_base(result, base, ++num_length);
		printf("\n");
		printf("\nResult in decimal: ");
		printNum(delete_zeros(inverse_number(result)), fPtr);
		printf("\n");
		int i;
		fclose(fPtr);
		
		return 0;	
	
}
