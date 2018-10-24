#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InstrUtils.h"
#include "Utils.h"

int main()
{
	Instruction *head;
    head = ReadInstructionList(stdin);
    Instruction *top;
	Instruction *body;
	Instruction *tail;
	int val1;
	int val2;
	top=head;//top of the list
	if (!head) {
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}
	/* YOUR CODE GOES HERE */
	while (top!=NULL){
		if(top->opcode == LOADI){
			val1 = top->field2;
            body = top->next;
                if(body->opcode == LOADI){
                    val2 =  body->field2;
                    tail =  body-> next;
                        if(  tail->opcode == ADD 
                          || tail->opcode == SUB
                          || tail->opcode == MUL){
                            
                            if(tail -> field2 == top->field1 && tail->field3 == body->field1){
                                if(tail->opcode == ADD){
                                        top->field2 = val1 + val2;
                                }
                                else if(tail->opcode == SUB){
                                        top->field2 = val1 - val2;
                                }
                                else if(tail->opcode == MUL){
                                        top->field2 = val1 * val2;
                                }
                                top -> opcode = LOADI;
                                top -> field1 = tail -> field1;
                                tail = tail -> next;
                                top -> next = tail;
                                tail -> prev = top;
                            }
                        }
		              }
        }
        top = top -> next;
	}
    if(head){
	PrintInstructionList(stdout, head);
    DestroyInstructionList(top);
    DestroyInstructionList(body);
    DestroyInstructionList(tail);
    DestroyInstructionList(head);
	return EXIT_SUCCESS;
    }
}
