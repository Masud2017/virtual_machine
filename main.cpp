#include <iostream>
#include <stdbool.h>

// #define sp (registers[SP])
// #define ip (registers[IP])

using namespace std;

/**
 * assembly instructions
*/
typedef enum {
    PSH,
    ADD,
    POP,
    SET,
    HLT
} InstructionSet;

typedef enum {
    A,B,C,D,E,F,PC,SP,NUM_OF_REGISTERS
} Registeres;

int registers[NUM_OF_REGISTERS];

bool running = true;

/**
 * Program instructions 
*/
int ip = 0; // Instruction pointer register
int sp = -1; // Stack pointer register
int stack[256]; // Stack

    const int program[] = {
        PSH, 5,
        PSH, 6,
        ADD,
        POP,
        HLT
    };

int fetch() {
    return program[ip];
}

void eval(int instr) {
    switch(instr) {
        case HLT: {
            running = false;
            break;
        }
        case PSH: {
            sp++;
            stack[sp] = program[++ip];
            printf("Value of register a %d\n", registers[A]); // prints the value at the register A

            break;
        }
        case POP : {
            // store the value at hte stack in val_opped then decrement the stack ptr
            int val_popped = stack[sp--];
            // print it out 
            printf("pooped %d\n",val_popped);
            break;
        }
        case ADD: {
            // first we pop hte stack and store it as 'a'
            int a = stack[sp--];

            // then we pop the top of the stack and store it as 'b'
            int b = stack[sp--];

            // we hten add the result and push it to the stack
            int result = b + a;
            sp++; // increment stack pointer **before**
            stack[sp] = result; // set the value to hte top of the stack
            // all done!
            break;
        }
    }
}

int main() {
    

    while (running) {
        int x= fetch();
        eval(fetch());
        ip++;
    }

    return 0;
}