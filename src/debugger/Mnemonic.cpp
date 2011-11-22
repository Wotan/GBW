#include "Debugger.hpp"

typedef struct s_mnemonic
{
  const char *desc;
  const char *mnemonic;
} Mnemonic;


Mnemonic MnemonicsTab[] =
{
  {"No Operation", "NOP"},
  {"Load 16-bit immediate into BC", "LD BC,nn"},
  {"Save A to address pointed by BC", "LD (BC),A"},
  {"Increment 16-bit BC", "INC BC"},
  {"Increment B", "INC B"},
  {"Decrement B", "DEC B"},
  {"Load 8-bit immediate into B", "LD B,n"},
  {"Rotate A left with carry", "RLC A"},
  {"Save SP to given address", "LD (nn),SP"},
  {"Add 16-bit BC to HL", "ADD HL,BC"},
  {"Load A from address pointed to by BC", "LD A,(BC)"},
  {"Decrement 16-bit BC", "DEC BC"},
  {"Increment C", "INC C"},
  {"Decrement C", "DEC C"},
  {"Load 8-bit immediate into C", "LD C,n"},
  {"Rotate A right with carry", "RRC A"},
  {"Stop processor", "STOP"},
  {"Load 16-bit immediate into DE", "LD DE,nn"},
  {"Save A to address pointed by DE", "LD (DE),A"},
  {"Increment 16-bit DE", "INC DE"},
  {"Increment D", "INC D"},
  {"Decrement D", "DEC D"},
  {"Load 8-bit immediate into D", "LD D,n"},
  {"Rotate A left", "RL A"},
  {"Relative jump by signed immediate", "JR n"},
  {"Add 16-bit DE to HL", "ADD HL,DE"},
  {"Load A from address pointed to by DE", "LD A,(DE)"},
  {"Decrement 16-bit DE", "DEC DE"},
  {"Increment E", "INC E"},
  {"Decrement E", "DEC E"},
  {"Load 8-bit immediate into E", "LD E,n"},
  {"Rotate A right", "RR A"},
  {"Relative jump by signed immediate if last result was not zero", "JR NZ,n"},
  {"Load 16-bit immediate into HL", "LD HL,nn"},
  {"Save A to address pointed by HL, and increment HL", "LDI (HL),A"},
  {"Increment 16-bit HL", "INC HL"},
  {"Increment H", "INC H"},
  {"Decrement H", "DEC H"},
  {"Load 8-bit immediate into H", "LD H,n"},
  {"Adjust A for BCD addition", "DAA"},
  {"Relative jump by signed immediate if last result was zero", "JR Z,n"},
  {"Add 16-bit HL to HL", "ADD HL,HL"},
  {"Load A from address pointed to by HL, and increment HL", "LDI A,(HL)"},
  {"Decrement 16-bit HL", "DEC HL"},
  {"Increment L", "INC L"},
  {"Decrement L", "DEC L"},
  {"Load 8-bit immediate into L", "LD L,n"},
  {"Complement (logical NOT) on A", "CPL"},
  {"Relative jump by signed immediate if last result caused no carry", "JR NC,n"},
  {"Load 16-bit immediate into SP", "LD SP,nn"},
  {"Save A to address pointed by HL, and decrement HL", "LDD (HL),A"},
  {"Increment 16-bit HL", "INC SP"},
  {"Increment value pointed by HL", "INC (HL)"},
  {"Decrement value pointed by HL", "DEC (HL)"},
  {"Load 8-bit immediate into address pointed by HL", "LD (HL),n"},
  {"Set carry flag", "SCF"},
  {"Relative jump by signed immediate if last result caused carry", "JR C,n"},
  {"Add 16-bit SP to HL", "ADD HL,SP"},
  {"Load A from address pointed to by HL, and decrement HL", "LDD A,(HL)"},
  {"Decrement 16-bit SP", "DEC SP"},
  {"Increment A", "INC A"},
  {"Decrement A", "DEC A"},
  {"Load 8-bit immediate into A", "LD A,n"},
  {"Clear carry flag", "CCF"},
  {"Copy B to B", "LD B,B"},
  {"Copy C to B", "LD B,C"},
  {"Copy D to B", "LD B,D"},
  {"Copy E to B", "LD B,E"},
  {"Copy H to B", "LD B,H"},
  {"Copy L to B", "LD B,L"},
  {"Copy value pointed by HL to B", "LD B,(HL)"},
  {"Copy A to B", "LD B,A"},
  {"Copy B to C", "LD C,B"},
  {"Copy C to C", "LD C,C"},
  {"Copy D to C", "LD C,D"},
  {"Copy E to C", "LD C,E"},
  {"Copy H to C", "LD C,H"},
  {"Copy L to C", "LD C,L"},
  {"Copy value pointed by HL to C", "LD C,(HL)"},
  {"Copy A to C", "LD C,A"},
  {"Copy B to D", "LD D,B"},
  {"Copy C to D", "LD D,C"},
  {"Copy D to D", "LD D,D"},
  {"Copy E to D", "LD D,E"},
  {"Copy H to D", "LD D,H"},
  {"Copy L to D", "LD D,L"},
  {"Copy value pointed by HL to D", "LD D,(HL)"},
  {"Copy A to D", "LD D,A"},
  {"Copy B to E", "LD E,B"},
  {"Copy C to E", "LD E,C"},
  {"Copy D to E", "LD E,D"},
  {"Copy E to E", "LD E,E"},
  {"Copy H to E", "LD E,H"},
  {"Copy L to E", "LD E,L"},
  {"Copy value pointed by HL to E", "LD E,(HL)"},
  {"Copy A to E", "LD E,A"},
  {"Copy B to H", "LD H,B"},
  {"Copy C to H", "LD H,C"},
  {"Copy D to H", "LD H,D"},
  {"Copy E to H", "LD H,E"},
  {"Copy H to H", "LD H,H"},
  {"Copy L to H", "LD H,L"},
  {"Copy value pointed by HL to H", "LD H,(HL)"},
  {"Copy A to H", "LD H,A"},
  {"Copy B to L", "LD L,B"},
  {"Copy C to L", "LD L,C"},
  {"Copy D to L", "LD L,D"},
  {"Copy E to L", "LD L,E"},
  {"Copy H to L", "LD L,H"},
  {"Copy L to L", "LD L,L"},
  {"Copy value pointed by HL to L", "LD L,(HL)"},
  {"Copy A to L", "LD L,A"},
  {"Copy B to address pointed by HL", "LD (HL),B"},
  {"Copy C to address pointed by HL", "LD (HL),C"},
  {"Copy D to address pointed by HL", "LD (HL),D"},
  {"Copy E to address pointed by HL", "LD (HL),E"},
  {"Copy H to address pointed by HL", "LD (HL),H"},
  {"Copy L to address pointed by HL", "LD (HL),L"},
  {"Halt processor", "HALT"},
  {"Copy A to address pointed by HL", "LD (HL),A"},
  {"Copy B to A", "LD A,B"},
  {"Copy C to A", "LD A,C"},
  {"Copy D to A", "LD A,D"},
  {"Copy E to A", "LD A,E"},
  {"Copy H to A", "LD A,H"},
  {"Copy L to A", "LD A,L"},
  {"Copy value pointed by HL to A", "LD A,(HL)"},
  {"Copy A to A", "LD A,A"},
  {"Add B to A", "ADD A,B"},
  {"Add C to A", "ADD A,C"},
  {"Add D to A", "ADD A,D"},
  {"Add E to A", "ADD A,E"},
  {"Add H to A", "ADD A,H"},
  {"Add L to A", "ADD A,L"},
  {"Add value pointed by HL to A", "ADD A,(HL)"},
  {"Add A to A", "ADD A,A"},
  {"Add B and carry flag to A", "ADC A,B"},
  {"Add C and carry flag to A", "ADC A,C"},
  {"Add D and carry flag to A", "ADC A,D"},
  {"Add E and carry flag to A", "ADC A,E"},
  {"Add H and carry flag to A", "ADC A,H"},
  {"Add and carry flag L to A", "ADC A,L"},
  {"Add value pointed by HL and carry flag to A", "ADC A,(HL)"},
  {"Add A and carry flag to A", "ADC A,A"},
  {"Subtract B from A", "SUB A,B"},
  {"Subtract C from A", "SUB A,C"},
  {"Subtract D from A", "SUB A,D"},
  {"Subtract E from A", "SUB A,E"},
  {"Subtract H from A", "SUB A,H"},
  {"Subtract L from A", "SUB A,L"},
  {"Subtract value pointed by HL from A", "SUB A,(HL)"},
  {"Subtract A from A", "SUB A,A"},
  {"Subtract B and carry flag from A", "SBC A,B"},
  {"Subtract C and carry flag from A", "SBC A,C"},
  {"Subtract D and carry flag from A", "SBC A,D"},
  {"Subtract E and carry flag from A", "SBC A,E"},
  {"Subtract H and carry flag from A", "SBC A,H"},
  {"Subtract and carry flag L from A", "SBC A,L"},
  {"Subtract value pointed by HL and carry flag from A", "SBC A,(HL)"},
  {"Subtract A and carry flag from A", "SBC A,A"},
  {"Logical AND B against A", "AND B"},
  {"Logical AND C against A", "AND C"},
  {"Logical AND D against A", "AND D"},
  {"Logical AND E against A", "AND E"},
  {"Logical AND H against A", "AND H"},
  {"Logical AND L against A", "AND L"},
  {"Logical AND value pointed by HL against A", "AND (HL)"},
  {"Logical AND A against A", "AND A"},
  {"Logical XOR B against A", "XOR B"},
  {"Logical XOR C against A", "XOR C"},
  {"Logical XOR D against A", "XOR D"},
  {"Logical XOR E against A", "XOR E"},
  {"Logical XOR H against A", "XOR H"},
  {"Logical XOR L against A", "XOR L"},
  {"Logical XOR value pointed by HL against A", "XOR (HL)"},
  {"Logical XOR A against A", "XOR A"},
  {"Logical OR B against A", "OR B"},
  {"Logical OR C against A", "OR C"},
  {"Logical OR D against A", "OR D"},
  {"Logical OR E against A", "OR E"},
  {"Logical OR H against A", "OR H"},
  {"Logical OR L against A", "OR L"},
  {"Logical OR value pointed by HL against A", "OR (HL)"},
  {"Logical OR A against A", "OR A"},
  {"Compare B against A", "CP B"},
  {"Compare C against A", "CP C"},
  {"Compare D against A", "CP D"},
  {"Compare E against A", "CP E"},
  {"Compare H against A", "CP H"},
  {"Compare L against A", "CP L"},
  {"Compare value pointed by HL against A", "CP (HL)"},
  {"Compare A against A", "CP A"},
  {"Return if last result was not zero", "RET NZ"},
  {"Pop 16-bit value from stack into BC", "POP BC"},
  {"Absolute jump to 16-bit location if last result was not zero", "JP NZ,nn"},
  {"Absolute jump to 16-bit location", "JP nn"},
  {"Call routine at 16-bit location if last result was not zero", "CALL NZ,nn"},
  {"Push 16-bit BC onto stack", "PUSH BC"},
  {"Add 8-bit immediate to A", "ADD A,n"},
  {"Call routine at address 0000h", "RST 0"},
  {"Return if last result was zero", "RET Z"},
  {"Return to calling routine", "RET"},
  {"Absolute jump to 16-bit location if last result was zero", "JP Z,nn"},
  {"Extended operations (two-byte instruction code)", "Ext ops"},
  {"Call routine at 16-bit location if last result was zero", "CALL Z,nn"},
  {"Call routine at 16-bit location", "CALL nn"},
  {"Add 8-bit immediate and carry to A", "ADC A,n"},
  {"Call routine at address 0008h", "RST 8"},
  {"Return if last result caused no carry", "RET NC"},
  {"Pop 16-bit value from stack into DE", "POP DE"},
  {"Absolute jump to 16-bit location if last result caused no carry", "JP NC,nn"},
  {"Operation removed in this CPU", "XX"},
  {"Call routine at 16-bit location if last result caused no carry", "CALL NC,nn"},
  {"Push 16-bit DE onto stack", "PUSH DE"},
  {"Subtract 8-bit immediate from A", "SUB A,n"},
  {"Call routine at address 0010h", "RST 10"},
  {"Return if last result caused carry", "RET C"},
  {"Enable interrupts and return to calling routine", "RETI"},
  {"Absolute jump to 16-bit location if last result caused carry", "JP C,nn"},
  {"Operation removed in this CPU", "XX"},
  {"Call routine at 16-bit location if last result caused carry", "CALL C,nn"},
  {"Operation removed in this CPU", "XX"},
  {"Subtract 8-bit immediate and carry from A", "SBC A,n"},
  {"Call routine at address 0018h", "RST 18"},
  {"Save A at address pointed to by (FF00h + 8-bit immediate)", "LDH (n),A"},
  {"Pop 16-bit value from stack into HL", "POP HL"},
  {"Save A at address pointed to by (FF00h + C)", "LDH (C),A"},
  {"Operation removed in this CPU", "XX"},
  {"Operation removed in this CPU", "XX"},
  {"Push 16-bit HL onto stack", "PUSH HL"},
  {"Logical AND 8-bit immediate against A", "AND n"},
  {"Call routine at address 0020h", "RST 20"},
  {"Add signed 8-bit immediate to SP", "ADD SP,d"},
  {"Jump to 16-bit value pointed by HL", "JP (HL)"},
  {"Save A at given 16-bit address", "LD (nn),A"},
  {"Operation removed in this CPU", "XX"},
  {"Operation removed in this CPU", "XX"},
  {"Operation removed in this CPU", "XX"},
  {"Logical XOR 8-bit immediate against A", "XOR n"},
  {"Call routine at address 0028h", "RST 28"},
  {"Load A from address pointed to by (FF00h + 8-bit immediate)", "LDH A,(n)"},
  {"Pop 16-bit value from stack into AF", "POP AF"},
  {"Operation removed in this CPU", "XX"},
  {"DIsable interrupts", "DI"},
  {"Operation removed in this CPU", "XX"},
  {"Push 16-bit AF onto stack", "PUSH AF"},
  {"Logical OR 8-bit immediate against A", "OR n"},
  {"Call routine at address 0030h", "RST 30"},
  {"Add signed 8-bit immediate to SP and save result in HL", "LDHL SP,d"},
  {"Copy HL to SP", "LD SP,HL"},
  {"Load A from given 16-bit address", "LD A,(nn)"},
  {"Enable interrupts", "EI"},
  {"Operation removed in this CPU", "XX"},
  {"Operation removed in this CPU", "XX"},
  {"Compare 8-bit immediate against A", "CP n"},
  {"Call routine at address 0038h", "RST 38"}
};

Mnemonic extendMnemonics[] =
  {
    {"Rotate B left with carry", "RLC B"},
    {"Rotate C left with carry", "RLC C"},
    {"Rotate D left with carry", "RLC D"},
    {"Rotate E left with carry", "RLC E"},
    {"Rotate H left with carry", "RLC H"},
    {"Rotate L left with carry", "RLC L"},
    {"Rotate value pointed by HL left with carry", "RLC (HL)"},
    {"Rotate A left with carry", "RLC A"},
    {"Rotate B right with carry", "RRC B"},
    {"Rotate C right with carry", "RRC C"},
    {"Rotate D right with carry", "RRC D"},
    {"Rotate E right with carry", "RRC E"},
    {"Rotate H right with carry", "RRC H"},
    {"Rotate L right with carry", "RRC L"},
    {"Rotate value pointed by HL right with carry", "RRC (HL)"},
    {"Rotate A right with carry", "RRC A"},
    {"Rotate B left", "RL B"},
    {"Rotate C left", "RL C"},
    {"Rotate D left", "RL D"},
    {"Rotate E left", "RL E"},
    {"Rotate H left", "RL H"},
    {"Rotate L left", "RL L"},
    {"Rotate value pointed by HL left", "RL (HL)"},
    {"Rotate A left", "RL A"},
    {"Rotate B right", "RR B"},
    {"Rotate C right", "RR C"},
    {"Rotate D right", "RR D"},
    {"Rotate E right", "RR E"},
    {"Rotate H right", "RR H"},
    {"Rotate L right", "RR L"},
    {"Rotate value pointed by HL right", "RR (HL)"},
    {"Rotate A right", "RR A"},
    {"Shift B left preserving sign", "SLA B"},
    {"Shift C left preserving sign", "SLA C"},
    {"Shift D left preserving sign", "SLA D"},
    {"Shift E left preserving sign", "SLA E"},
    {"Shift H left preserving sign", "SLA H"},
    {"Shift L left preserving sign", "SLA L"},
    {"Shift value pointed by HL left preserving sign", "SLA (HL)"},
    {"Shift A left preserving sign", "SLA A"},
    {"Shift B right preserving sign", "SRA B"},
    {"Shift C right preserving sign", "SRA C"},
    {"Shift D right preserving sign", "SRA D"},
    {"Shift E right preserving sign", "SRA E"},
    {"Shift H right preserving sign", "SRA H"},
    {"Shift L right preserving sign", "SRA L"},
    {"Shift value pointed by HL right preserving sign", "SRA (HL)"},
    {"Shift A right preserving sign", "SRA A"},
    {"Swap nybbles in B", "SWAP B"},
    {"Swap nybbles in C", "SWAP C"},
    {"Swap nybbles in D", "SWAP D"},
    {"Swap nybbles in E", "SWAP E"},
    {"Swap nybbles in H", "SWAP H"},
    {"Swap nybbles in L", "SWAP L"},
    {"Swap nybbles in value pointed by HL", "SWAP (HL)"},
    {"Swap nybbles in A", "SWAP A"},
    {"Shift B right", "SRL B"},
    {"Shift C right", "SRL C"},
    {"Shift D right", "SRL D"},
    {"Shift E right", "SRL E"},
    {"Shift H right", "SRL H"},
    {"Shift L right", "SRL L"},
    {"Shift value pointed by HL right", "SRL (HL)"},
    {"Shift A right", "SRL A"},
    {"Test bit 0 of B", "BIT 0,B"},
    {"Test bit 0 of C", "BIT 0,C"},
    {"Test bit 0 of D", "BIT 0,D"},
    {"Test bit 0 of E", "BIT 0,E"},
    {"Test bit 0 of H", "BIT 0,H"},
    {"Test bit 0 of L", "BIT 0,L"},
    {"Test bit 0 of value pointed by HL", "BIT 0,(HL)"},
    {"Test bit 0 of A", "BIT 0,A"},
    {"Test bit 1 of B", "BIT 1,B"},
    {"Test bit 1 of C", "BIT 1,C"},
    {"Test bit 1 of D", "BIT 1,D"},
    {"Test bit 1 of E", "BIT 1,E"},
    {"Test bit 1 of H", "BIT 1,H"},
    {"Test bit 1 of L", "BIT 1,L"},
    {"Test bit 1 of value pointed by HL", "BIT 1,(HL)"},
    {"Test bit 1 of A", "BIT 1,A"},
    {"Test bit 2 of B", "BIT 2,B"},
    {"Test bit 2 of C", "BIT 2,C"},
    {"Test bit 2 of D", "BIT 2,D"},
    {"Test bit 2 of E", "BIT 2,E"},
    {"Test bit 2 of H", "BIT 2,H"},
    {"Test bit 2 of L", "BIT 2,L"},
    {"Test bit 2 of value pointed by HL", "BIT 2,(HL)"},
    {"Test bit 2 of A", "BIT 2,A"},
    {"Test bit 3 of B", "BIT 3,B"},
    {"Test bit 3 of C", "BIT 3,C"},
    {"Test bit 3 of D", "BIT 3,D"},
    {"Test bit 3 of E", "BIT 3,E"},
    {"Test bit 3 of H", "BIT 3,H"},
    {"Test bit 3 of L", "BIT 3,L"},
    {"Test bit 3 of value pointed by HL", "BIT 3,(HL)"},
    {"Test bit 3 of A", "BIT 3,A"},
    {"Test bit 4 of B", "BIT 4,B"},
    {"Test bit 4 of C", "BIT 4,C"},
    {"Test bit 4 of D", "BIT 4,D"},
    {"Test bit 4 of E", "BIT 4,E"},
    {"Test bit 4 of H", "BIT 4,H"},
    {"Test bit 4 of L", "BIT 4,L"},
    {"Test bit 4 of value pointed by HL", "BIT 4,(HL)"},
    {"Test bit 4 of A", "BIT 4,A"},
    {"Test bit 5 of B", "BIT 5,B"},
    {"Test bit 5 of C", "BIT 5,C"},
    {"Test bit 5 of D", "BIT 5,D"},
    {"Test bit 5 of E", "BIT 5,E"},
    {"Test bit 5 of H", "BIT 5,H"},
    {"Test bit 5 of L", "BIT 5,L"},
    {"Test bit 5 of value pointed by HL", "BIT 5,(HL)"},
    {"Test bit 5 of A", "BIT 5,A"},
    {"Test bit 6 of B", "BIT 6,B"},
    {"Test bit 6 of C", "BIT 6,C"},
    {"Test bit 6 of D", "BIT 6,D"},
    {"Test bit 6 of E", "BIT 6,E"},
    {"Test bit 6 of H", "BIT 6,H"},
    {"Test bit 6 of L", "BIT 6,L"},
    {"Test bit 6 of value pointed by HL", "BIT 6,(HL)"},
    {"Test bit 6 of A", "BIT 6,A"},
    {"Test bit 7 of B", "BIT 7,B"},
    {"Test bit 7 of C", "BIT 7,C"},
    {"Test bit 7 of D", "BIT 7,D"},
    {"Test bit 7 of E", "BIT 7,E"},
    {"Test bit 7 of H", "BIT 7,H"},
    {"Test bit 7 of L", "BIT 7,L"},
    {"Test bit 7 of value pointed by HL", "BIT 7,(HL)"},
    {"Test bit 7 of A", "BIT 7,A"},
    {"Clear (reset) bit 0 of B", "RES 0,B"},
    {"Clear (reset) bit 0 of C", "RES 0,C"},
    {"Clear (reset) bit 0 of D", "RES 0,D"},
    {"Clear (reset) bit 0 of E", "RES 0,E"},
    {"Clear (reset) bit 0 of H", "RES 0,H"},
    {"Clear (reset) bit 0 of L", "RES 0,L"},
    {"Clear (reset) bit 0 of value pointed by HL", "RES 0,(HL)"},
    {"Clear (reset) bit 0 of A", "RES 0,A"},
    {"Clear (reset) bit 1 of B", "RES 1,B"},
    {"Clear (reset) bit 1 of C", "RES 1,C"},
    {"Clear (reset) bit 1 of D", "RES 1,D"},
    {"Clear (reset) bit 1 of E", "RES 1,E"},
    {"Clear (reset) bit 1 of H", "RES 1,H"},
    {"Clear (reset) bit 1 of L", "RES 1,L"},
    {"Clear (reset) bit 1 of value pointed by HL", "RES 1,(HL)"},
    {"Clear (reset) bit 1 of A", "RES 1,A"},
    {"Clear (reset) bit 2 of B", "RES 2,B"},
    {"Clear (reset) bit 2 of C", "RES 2,C"},
    {"Clear (reset) bit 2 of D", "RES 2,D"},
    {"Clear (reset) bit 2 of E", "RES 2,E"},
    {"Clear (reset) bit 2 of H", "RES 2,H"},
    {"Clear (reset) bit 2 of L", "RES 2,L"},
    {"Clear (reset) bit 2 of value pointed by HL", "RES 2,(HL)"},
    {"Clear (reset) bit 2 of A", "RES 2,A"},
    {"Clear (reset) bit 3 of B", "RES 3,B"},
    {"Clear (reset) bit 3 of C", "RES 3,C"},
    {"Clear (reset) bit 3 of D", "RES 3,D"},
    {"Clear (reset) bit 3 of E", "RES 3,E"},
    {"Clear (reset) bit 3 of H", "RES 3,H"},
    {"Clear (reset) bit 3 of L", "RES 3,L"},
    {"Clear (reset) bit 3 of value pointed by HL", "RES 3,(HL)"},
    {"Clear (reset) bit 3 of A", "RES 3,A"},
    {"Clear (reset) bit 4 of B", "RES 4,B"},
    {"Clear (reset) bit 4 of C", "RES 4,C"},
    {"Clear (reset) bit 4 of D", "RES 4,D"},
    {"Clear (reset) bit 4 of E", "RES 4,E"},
    {"Clear (reset) bit 4 of H", "RES 4,H"},
    {"Clear (reset) bit 4 of L", "RES 4,L"},
    {"Clear (reset) bit 4 of value pointed by HL", "RES 4,(HL)"},
    {"Clear (reset) bit 4 of A", "RES 4,A"},
    {"Clear (reset) bit 5 of B", "RES 5,B"},
    {"Clear (reset) bit 5 of C", "RES 5,C"},
    {"Clear (reset) bit 5 of D", "RES 5,D"},
    {"Clear (reset) bit 5 of E", "RES 5,E"},
    {"Clear (reset) bit 5 of H", "RES 5,H"},
    {"Clear (reset) bit 5 of L", "RES 5,L"},
    {"Clear (reset) bit 5 of value pointed by HL", "RES 5,(HL)"},
    {"Clear (reset) bit 5 of A", "RES 5,A"},
    {"Clear (reset) bit 6 of B", "RES 6,B"},
    {"Clear (reset) bit 6 of C", "RES 6,C"},
    {"Clear (reset) bit 6 of D", "RES 6,D"},
    {"Clear (reset) bit 6 of E", "RES 6,E"},
    {"Clear (reset) bit 6 of H", "RES 6,H"},
    {"Clear (reset) bit 6 of L", "RES 6,L"},
    {"Clear (reset) bit 6 of value pointed by HL", "RES 6,(HL)"},
    {"Clear (reset) bit 6 of A", "RES 6,A"},
    {"Clear (reset) bit 7 of B", "RES 7,B"},
    {"Clear (reset) bit 7 of C", "RES 7,C"},
    {"Clear (reset) bit 7 of D", "RES 7,D"},
    {"Clear (reset) bit 7 of E", "RES 7,E"},
    {"Clear (reset) bit 7 of H", "RES 7,H"},
    {"Clear (reset) bit 7 of L", "RES 7,L"},
    {"Clear (reset) bit 7 of value pointed by HL", "RES 7,(HL)"},
    {"Clear (reset) bit 7 of A", "RES 7,A"},
    {"Set bit 0 of B", "SET 0,B"},
    {"Set bit 0 of C", "SET 0,C"},
    {"Set bit 0 of D", "SET 0,D"},
    {"Set bit 0 of E", "SET 0,E"},
    {"Set bit 0 of H", "SET 0,H"},
    {"Set bit 0 of L", "SET 0,L"},
    {"Set bit 0 of value pointed by HL", "SET 0,(HL)"},
    {"Set bit 0 of A", "SET 0,A"},
    {"Set bit 1 of B", "SET 1,B"},
    {"Set bit 1 of C", "SET 1,C"},
    {"Set bit 1 of D", "SET 1,D"},
    {"Set bit 1 of E", "SET 1,E"},
    {"Set bit 1 of H", "SET 1,H"},
    {"Set bit 1 of L", "SET 1,L"},
    {"Set bit 1 of value pointed by HL", "SET 1,(HL)"},
    {"Set bit 1 of A", "SET 1,A"},
    {"Set bit 2 of B", "SET 2,B"},
    {"Set bit 2 of C", "SET 2,C"},
    {"Set bit 2 of D", "SET 2,D"},
    {"Set bit 2 of E", "SET 2,E"},
    {"Set bit 2 of H", "SET 2,H"},
    {"Set bit 2 of L", "SET 2,L"},
    {"Set bit 2 of value pointed by HL", "SET 2,(HL)"},
    {"Set bit 2 of A", "SET 2,A"},
    {"Set bit 3 of B", "SET 3,B"},
    {"Set bit 3 of C", "SET 3,C"},
    {"Set bit 3 of D", "SET 3,D"},
    {"Set bit 3 of E", "SET 3,E"},
    {"Set bit 3 of H", "SET 3,H"},
    {"Set bit 3 of L", "SET 3,L"},
    {"Set bit 3 of value pointed by HL", "SET 3,(HL)"},
    {"Set bit 3 of A", "SET 3,A"},
    {"Set bit 4 of B", "SET 4,B"},
    {"Set bit 4 of C", "SET 4,C"},
    {"Set bit 4 of D", "SET 4,D"},
    {"Set bit 4 of E", "SET 4,E"},
    {"Set bit 4 of H", "SET 4,H"},
    {"Set bit 4 of L", "SET 4,L"},
    {"Set bit 4 of value pointed by HL", "SET 4,(HL)"},
    {"Set bit 4 of A", "SET 4,A"},
    {"Set bit 5 of B", "SET 5,B"},
    {"Set bit 5 of C", "SET 5,C"},
    {"Set bit 5 of D", "SET 5,D"},
    {"Set bit 5 of E", "SET 5,E"},
    {"Set bit 5 of H", "SET 5,H"},
    {"Set bit 5 of L", "SET 5,L"},
    {"Set bit 5 of value pointed by HL", "SET 5,(HL)"},
    {"Set bit 5 of A", "SET 5,A"},
    {"Set bit 6 of B", "SET 6,B"},
    {"Set bit 6 of C", "SET 6,C"},
    {"Set bit 6 of D", "SET 6,D"},
    {"Set bit 6 of E", "SET 6,E"},
    {"Set bit 6 of H", "SET 6,H"},
    {"Set bit 6 of L", "SET 6,L"},
    {"Set bit 6 of value pointed by HL", "SET 6,(HL)"},
    {"Set bit 6 of A", "SET 6,A"},
    {"Set bit 7 of B", "SET 7,B"},
    {"Set bit 7 of C", "SET 7,C"},
    {"Set bit 7 of D", "SET 7,D"},
    {"Set bit 7 of E", "SET 7,E"},
    {"Set bit 7 of H", "SET 7,H"},
    {"Set bit 7 of L", "SET 7,L"},
    {"Set bit 7 of value pointed by HL", "SET 7,(HL)"},
    {"Set bit 7 of A", "SET 7,A"}
  };

const char *Debugger::GetOpMnemonic(Emulator *emu, int addr)
{
  BYTE	value;

  value = emu->ReadMem(addr);
  if (value != 0xCB)
    return MnemonicsTab[value].mnemonic;
  else
    {
      value = emu->ReadMem(addr + 1);
      return MnemonicsTab[value].mnemonic;
    }
  return 0;
}

const char *Debugger::GetOpDesc(Emulator *emu, int addr)
{
  BYTE	value;

  value = emu->ReadMem(addr);
  if (value != 0xCB)
    return MnemonicsTab[value].desc;
  else
    {
      value = emu->ReadMem(addr + 1);
      return MnemonicsTab[value].desc;
    }
  return 0;
}
