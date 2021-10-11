#include <stdlib.h>
#include <stdio.h>


typedef struct stateMachine {
	char name;
	int stateNum, del, low, high;
	struct stateMachine *zero;
	struct stateMachine *one;
} fsm;

fsm states[8];
int numStates = 8;
int garbage[8];
int garVal;
char d2;

void assignStates(void) {
	states[0].name = 'A';
	states[0].zero = &states[0];
	states[0].one = &states[3];
	states[0].stateNum = 0;
	states[0].del = '\0';
	states[0].low = 0;
	states[0].high = 1;

	states[1].name = 'B';
	states[1].zero = &states[2];
	states[1].one = &states[0];
	states[1].stateNum = 1;
	states[1].del = '\0';
	states[1].low = 0;
	states[1].high = 1;

	states[2].name = 'C';
	states[2].zero = &states[1];
	states[2].one = &states[4];
	states[2].stateNum = 2;
	states[2].del = '\0';
	states[2].low = 0;
	states[2].high = 1;

	states[3].name = 'D'; 
	states[3].zero = &states[5];
	states[3].one = &states[7];
	states[3].stateNum = 3;
	states[3].del = '\0';
	states[3].low = 0;
	states[3].high = 1;

	states[4].name = 'E';
	states[4].zero = &states[0];
	states[4].one = &states[6];
	states[4].stateNum = 4;
	states[4].del = '\0';
	states[4].low = 0;
	states[4].high = 1;

	states[5].name = 'F';
	states[5].zero = &states[4];
	states[5].one = &states[6];
	states[5].stateNum = 5;	
	states[5].del = '\0';
	states[5].low = 0;
	states[5].high = 1;

	states[6].name = 'G';
	states[6].zero = &states[7];
	states[6].one = &states[2];
	states[6].stateNum = 6;
	states[6].del = '\0';
	states[6].low = 0;
	states[6].high = 1;

	states[7].name = 'H';
	states[7].zero = &states[5];
	states[7].one = &states[1];
	states[7].stateNum = 7;
	states[7].del = '\0';
	states[7].low = 0;
	states[7].high = 1;
}

void print() {
	int i;
	for(i=0; i<numStates; i++){
		if(states[i].del != 1){
			fprintf(stdout, "%c %c %c\n", states[i].name, states[i].zero->name, states[i].one->name);
		}
	}
}

void findGarbage(){
	int w, x, y, z;
	char s;
	
	y=0;
	
	for (w=0; w<numStates; w++){
		garbage[w]='\0';
	}	

	for(w=0; w<numStates; w++){
		if(states[w].del != 1){
			s = states[w].name;
			z = 1;
			garVal = 1;
			for (x=0; x<numStates; x++){
				if(states[x].del != 1){
					if(states[x].zero->name == s || states[x].one->name == s){
						if(states[x].name != s){
							z=0;
							garVal = 0;
						}
					}
				}
			}
		}
		if(z == 1) {
			garbage[y] = s;
			y++;
		}
	}
	if(garbage[0] == '\0'){
		fprintf(stdout, "No garbage\n");
	} else {
		fprintf(stdout, "Garbage: ");
		for(w=0; w<numStates; w++){
			if(garbage[w] != '\0'){
				fprintf(stdout, "%c ", garbage[w]);
			} else {}
		}
	}

	fprintf(stdout, "\n");
	
}

void delete(){
	int x, y;
	
	if(garbage[0] != '\0'){
		fprintf(stdout, "\nDeleted: ");
		if(states[garVal].del != 1){
			for(x=0; x<numStates; x++){
				if(garbage[x] != '\0'){
					fprintf(stdout, "%c ", garbage[x]);
					for(y=0; y<numStates; y++){
						if (states[y].name == garbage[x]){
							states[y].del = 1;
						}
					}
				}
			}
			garbage[x] = '\0';
		}
	} else if (garbage[0] == '\0'){
		fprintf(stdout, "\nNo states deleted.\n");
	}
	
	fprintf(stdout, "\n");
}

void delete2(){
	int x;

	for(x=0; x<numStates; x++){
		if(states[x].name == d2){
			if(states[x].del != 1){
				states[x].del = 1;
				fprintf(stdout, "Deleted. \n");
			} else {
				fprintf(stdout, "Not deleted. \n");
			}
		}
	}
	d2 = '\0';
	
}


int main(int argc, char * argv[])
{
	char input[5];
	int x;
	int y=1;

	assignStates();
	fsm currState = states[3];

	fprintf(stdout, "The current state is: %c\n", currState.name);
	fprintf(stdout, "Enter your command, enter x to exit.\n");

	while(y!=0){
		for(x=0; x<=4; x++){
			scanf("%c", &input[x]);
			if(input[x] == '\n'){
				break;			
			}
		}

		d2 = input[2];		

		if(input[0] == '0'){
			fprintf(stdout, "%c\n", currState.zero->name);
			currState = states[currState.zero->stateNum];
		} else if(input[0] == '1'){
			fprintf(stdout, "%c\n", currState.one->name);
			currState = states[currState.one->stateNum];
		} else if(input[0] == 'p'){
			print();
		} else if(input[0] == 'c' && input[2] == '0'){
			if(input[4] == 'A'){
				currState.zero = &states[0];
				states[currState.stateNum].zero = &states[0];
				states[currState.stateNum].low = 0;
			} else if(input[4] == 'B'){
				currState.zero = &states[1];
				states[currState.stateNum].zero = &states[1];
				states[currState.stateNum].low = 1;
			} else if(input[4] == 'C'){
				currState.zero = &states[2];
				states[currState.stateNum].zero = &states[2];
				states[currState.stateNum].low = 2;
			} else if(input[4] == 'D'){
				currState.zero = &states[3];
				states[currState.stateNum].zero = &states[3];
				states[currState.stateNum].low = 3;
			} else if(input[4] == 'E'){
				currState.zero = &states[4];
				states[currState.stateNum].zero = &states[4];
				states[currState.stateNum].low = 4;
			} else if(input[4] == 'F'){
				currState.zero = &states[5];
				states[currState.stateNum].zero = &states[5];
				states[currState.stateNum].low = 5;
			} else if(input[4] == 'G'){
				currState.zero = &states[6];
				states[currState.stateNum].zero = &states[6];
				states[currState.stateNum].low = 6;
			} else if(input[4] == 'H'){
				currState.zero = &states[7];
				states[currState.stateNum].zero = &states[7];
				states[currState.stateNum].low = 7;
			}
		} else if(input[0] == 'c' && input[2] == '1'){
			if(input[4] == 'A'){
				currState.one = &states[0];
				states[currState.stateNum].one = &states[0];
				states[currState.stateNum].high = 0;
			} else if(input[4] == 'B'){
				currState.one = &states[1];
				states[currState.stateNum].one = &states[1];
				states[currState.stateNum].high = 1;
			} else if(input[4] == 'C'){
				currState.one = &states[2];
				states[currState.stateNum].one = &states[2];
				states[currState.stateNum].high = 2;
			} else if(input[4] == 'D'){
				currState.one = &states[3];
				states[currState.stateNum].one = &states[3];
				states[currState.stateNum].high = 3;
			} else if(input[4] == 'E'){
				currState.one = &states[4];
				states[currState.stateNum].one = &states[4];
				states[currState.stateNum].high = 4;
			} else if(input[4] == 'F'){
				currState.one = &states[5];
				states[currState.stateNum].one = &states[5];
				states[currState.stateNum].high = 5;
			} else if(input[4] == 'G'){
				currState.one = &states[6];
				states[currState.stateNum].one = &states[6];
				states[currState.stateNum].high = 6;
			} else if(input[4] == 'H'){
				currState.one = &states[7];
				states[currState.stateNum].one = &states[7];
				states[currState.stateNum].high = 7;
			}
		} else if(input[0] == 'x'){
			y=0;
			break;
		} else if(input[0] == 'g'){
			findGarbage();
		} else if(input[0] == 'd'){
			if(d2 == 'A' || d2 == 'B' || d2 == 'C' || d2 == 'D' || d2 == 'E' || d2 == 'F' || d2 == 'G' || d2 == 'H'){
				delete2();
			} else {
				delete();
			}
		}
	}


   
