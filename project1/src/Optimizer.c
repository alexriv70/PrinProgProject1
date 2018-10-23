#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InstrUtils.h"
#include "Utils.h"

int main()
{
	Instruction *top;
	Instruction *head;
	Instruction *body;
	Instruction *tail;
	int reg1;
	int reg2;
	head = ReadInstructionList(stdin);
	top=head;//top of the list
	if (!head) {
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}
	/* YOUR CODE GOES HERE */
	if (head) {
		LOOP1: while (head!=lastinstruction(head)){
			if(head->opcode == LOAD){
				body = head->next;
				reg1 = head.field1;
				LOOP2: while (body!=lastinstruction(head))
				{
					if(body.opcode == LOAD){
						tail = body->next;
						reg2 = body.field1;
							if(tail==lastinstruction(head)){
								switch(tail.opcode){
									case'ADD':
										head.opcode = LOADI;
										head.field1 = reg2+reg1; 
										DestroyInstructionList(body);
										DestroyInstructionList(tail);		
										head=head->next;
										goto LOOP1;
									case 'SUBTRACT':
										head.opcode = LOADI;
										head.field1 = reg2-reg1;
										DestroyInstructionList(body);
										DestroyInstructionList(tail);		
										head=head->next;
										goto LOOP1;
									case 'MUL':
										head.opcode = LOADI
										head.field = reg2*reg1;
										DestroyInstructionList(body);
										DestroyInstructionList(tail);		
										head=head->next;
										goto LOOP1;
									default:
										body = body->next;
										goto LOOP2;
								}
							}
							else {
								while(tail != lastinstruction(head)){
									switch(tail.opcode){
									case'ADD':
										head.opcode = LOADI;
										head.field1 = reg2+reg1; 
										DestroyInstructionList(body);
										DestroyInstructionList(tail);		
										head=head->next;
										goto LOOP1;
									case 'SUBTRACT':
										head.opcode = LOADI;
										head.field1 = reg2-reg1;
										DestroyInstructionList(body);
										DestroyInstructionList(tail);		
										head=head->next;
										goto LOOP1;
									case 'MUL':
										head.opcode = LOADI
										numload = reg2*reg1;
										DestroyInstructionList(body);
										DestroyInstructionList(tail);		
										head=head->next;
										goto LOOP1;
									default:
										tail = tail->next;
										goto LOOP2;
									}

								}

							}
					}	
				}
				goto END;
			}
			else{
				head = head->next;
				goto LOOP1;
			}
		}
		}
	END:
	PrintInstructionList(stdout, top);
	return EXIT_SUCCESS;
}
