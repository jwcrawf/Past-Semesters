/*
  sim.cpp

  Jon Crawford

  CDA3101 Fall 2018 - Assignment 3 MIPS Simulator

  Library: http://www.cplusplus.com/reference/clibrary/

  Mult visualization: http://chortle.ccsu.edu/assemblytutorial/Chapter-14/ass14_3.html

  Int usage: http://www.cplusplus.com/reference/cstdint/

  compile: g++ -g sim.cpp -std=c++11
*/

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cstdio>

#define MAXP 32768

void dump();

struct
{
  union
  {
    unsigned int x;
    struct
    {
      unsigned int func:6;
      unsigned int shift:5;
      unsigned int rd:5;
      unsigned int rt:5;
      unsigned int rs:5;
      unsigned int oper:6;
    } rFormat;
    struct
    {
      unsigned int target:26;
      unsigned int oper:6;
    } jFormat;
    struct
    {
      unsigned int target:26;
      unsigned int oper:6;
    } test;
    struct
    {
      unsigned int offset:16;
      unsigned int rt:5;
      unsigned int rs:5;
      unsigned int oper:6;
    } iFormat;
    struct {unsigned int data:32;} dFormat;
  } u;
} inst[MAXP] = {0}; 

char reg[32][6] = { "$zero", "$at", "$v0", "$v1", "$a0",
                          "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5",
                          "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6",
                          "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra" };

int regIndex [34] = {0}, dataIndex[MAXP] = {0};
int iCount(0), dCount(0);
FILE * outFile;

union
{
  int64_t b: 64;
  struct
  {
    int32_t lo: 32;
    int32_t hi: 32;
  } half;
} longBit;

int main(int argc, char * argv[])
{
  if ( argc > 2 || argc < 2)
  {
    std::cout << "usage: " << argv[0] << " <name>.obj" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::ifstream inFile(argv[1], std::ios::in);
  inFile >> iCount >> dCount;
  for (int PC = 0; PC < (iCount+dCount); ++PC )
    inFile >> std::hex >> inst[PC].u.x;

  inFile.close();
  outFile = fopen("log.txt", "w");

  regIndex[28] = iCount, regIndex[0] = 0;

  fprintf(outFile, "insts:\n");
  for (int PC = 0; PC < iCount; ++PC)
  {
    switch(inst[PC].u.test.oper)
    {
      case 0:
      {
        switch (inst[PC].u.rFormat.func)
        {
          case 33:
            fprintf(outFile, "%4d: addu  %s,%s,%s\n", PC, reg[inst[PC].u.rFormat.rd], reg[inst[PC].u.rFormat.rs], reg[inst[PC].u.rFormat.rt]);
            break;
          case 16:
            fprintf(outFile, "%4d: mfhi  %s\n", PC, reg[inst[PC].u.rFormat.rd]);
            break;
          case 18:
            fprintf(outFile, "%4d: mflo  %s\n", PC, reg[inst[PC].u.rFormat.rd]);
            break;
          case 24:
            fprintf(outFile, "%4d: mult %s,%s\n", PC, reg[inst[PC].u.rFormat.rs], reg[inst[PC].u.rFormat.rt]);
            break;
          case 26:
            fprintf(outFile, "%4d: div %s,%s\n", PC, reg[inst[PC].u.rFormat.rs], reg[inst[PC].u.rFormat.rt]);
            break;
          case 35:
            fprintf(outFile, "%4d: subu %s,%s,%s\n", PC, reg[inst[PC].u.rFormat.rd], reg[inst[PC].u.rFormat.rs], reg[inst[PC].u.rFormat.rt]);
            break;
          case 36:
            fprintf(outFile, "%4d: and %s,%s,%s\n", PC, reg[inst[PC].u.rFormat.rd], reg[inst[PC].u.rFormat.rs], reg[inst[PC].u.rFormat.rt]);
            break;
          case 37:
            fprintf(outFile, "%4d: or %s,%s,%s\n", PC, reg[inst[PC].u.rFormat.rd], reg[inst[PC].u.rFormat.rs], reg[inst[PC].u.rFormat.rt]);
            break;
          case 42:
            fprintf(outFile, "%4d: slt %s,%s,%s\n", PC, reg[inst[PC].u.rFormat.rd], reg[inst[PC].u.rFormat.rs], reg[inst[PC].u.rFormat.rt]);
            break;
          case 12:
            fprintf(outFile, "%4d: syscall\n", PC);
            break;
          default:
            std::cout << "could not find inst with opcode 0 and funct " << inst[PC].u.rFormat.func << std::endl;
            fclose(outFile);
            exit(EXIT_FAILURE);
            break;
        } // end r-format funct switch
        break;
      } //end r-format instructions
      case 9:
        fprintf(outFile, "%4d: addiu %s,%s,%u\n", PC, reg[inst[PC].u.iFormat.rt], reg[inst[PC].u.iFormat.rs], (int16_t)inst[PC].u.iFormat.offset);
        break;
      case 4:
        fprintf(outFile, "%4d: beq %s,%s,%u\n", PC, reg[inst[PC].u.iFormat.rs], reg[inst[PC].u.iFormat.rt], (int16_t)inst[PC].u.iFormat.offset);
        break;
      case 5:
        fprintf(outFile, "%4d: bne %s,%s,%u\n", PC, reg[inst[PC].u.iFormat.rs], reg[inst[PC].u.iFormat.rt], (int16_t)inst[PC].u.iFormat.offset);
        break;
      case 35:
        fprintf(outFile, "%4d: lw  %s,%u(%s)\n", PC, reg[inst[PC].u.iFormat.rt], (int16_t)inst[PC].u.iFormat.offset, reg[inst[PC].u.iFormat.rs]);
        break;
      case 43:
        fprintf(outFile, "%4d: sw  %s,%u(%s)\n", PC, reg[inst[PC].u.iFormat.rt], (int16_t)inst[PC].u.iFormat.offset, reg[inst[PC].u.iFormat.rs]);
        break;
      case 2:
        fprintf(outFile, "%4d: j %u\n", PC, inst[PC].u.jFormat.target);
        break;
      default:
        std::cout << "could not find inst with opcode " << inst[PC].u.test.oper << std::endl;
        fclose(outFile);
        exit(EXIT_FAILURE);
        break;
    } // end op code switch
  } // end instructions print loop

  fprintf(outFile, "\ndata:\n");
  for (int PC = iCount; PC < (iCount + dCount); ++PC)
    fprintf(outFile, "%4d: %u\n", PC, inst[PC].u.dFormat.data);
  for (int PC = 0; PC < dCount; ++PC)
    dataIndex[PC] = inst[(PC + iCount)].u.dFormat.data;

  for (int PC = 0; PC < iCount; ++PC)
  {
    switch(inst[PC].u.test.oper)
    {
      case 0:
      {
        switch (inst[PC].u.rFormat.func)
        {
          case 33:
            fprintf(outFile,"\nPC: %d\n", PC);
            fprintf(outFile, "inst: addu  %s,%s,%s\n", reg[inst[PC].u.rFormat.rd], reg[inst[PC].u.rFormat.rs], reg[inst[PC].u.rFormat.rt]);
            regIndex[inst[PC].u.rFormat.rd] = regIndex[inst[PC].u.rFormat.rs] + regIndex[inst[PC].u.rFormat.rt];
            regIndex[0] = 0;
            dump();
            break;
          case 16:
            fprintf(outFile,"\nPC: %d\n", PC);
            fprintf(outFile, "inst: mfhi %s\n", reg[inst[PC].u.rFormat.rd]);
            regIndex[inst[PC].u.rFormat.rd] = regIndex[33];
            regIndex[0] = 0;
            dump();
            break;
          case 18:
            fprintf(outFile,"\nPC: %d\n", PC);
            fprintf(outFile, "inst: mflo %s\n", reg[inst[PC].u.rFormat.rd]);
            regIndex[inst[PC].u.rFormat.rd] = regIndex[32];
            regIndex[0] = 0;
            dump();
            break;
          case 24:
            fprintf(outFile,"\nPC: %d\n", PC);
            fprintf(outFile, "inst: mult %s,%s\n", reg[inst[PC].u.rFormat.rs], reg[inst[PC].u.rFormat.rt]);
            longBit.b = (int64_t)(regIndex[inst[PC].u.rFormat.rs] * regIndex[inst[PC].u.rFormat.rt]);
            regIndex[32] = longBit.half.lo;
            regIndex[33] = longBit.half.hi;
            dump();
            break;
          case 26:
            fprintf(outFile,"\nPC: %d\n", PC);
            fprintf(outFile, "inst: div %s,%s\n", reg[inst[PC].u.rFormat.rs], reg[inst[PC].u.rFormat.rt]);
            if (regIndex[inst[PC].u.rFormat.rt] == 0)
            {
              std::cout << "divide by zero for instruction at " << PC << std::endl;
              fclose(outFile);
              exit(EXIT_FAILURE);
            }
            regIndex[32] = regIndex[inst[PC].u.rFormat.rs] / regIndex[inst[PC].u.rFormat.rt];
            regIndex[33] = regIndex[inst[PC].u.rFormat.rs] % regIndex[inst[PC].u.rFormat.rt];
            dump();
            break;
          case 35:
            fprintf(outFile,"\nPC: %d\n", PC);
            fprintf(outFile, "inst: subu %s,%s,%s\n", reg[inst[PC].u.rFormat.rd], reg[inst[PC].u.rFormat.rs], reg[inst[PC].u.rFormat.rt]);
            regIndex[inst[PC].u.rFormat.rd] = regIndex[inst[PC].u.rFormat.rs] - regIndex[inst[PC].u.rFormat.rt];
            regIndex[0] = 0;
            dump();
            break;
          case 36:
            fprintf(outFile,"\nPC: %d\n", PC);
            fprintf(outFile, "inst: and %s,%s,%s\n", reg[inst[PC].u.rFormat.rd], reg[inst[PC].u.rFormat.rs], reg[inst[PC].u.rFormat.rt]);
            regIndex[inst[PC].u.rFormat.rd] = regIndex[inst[PC].u.rFormat.rs] & regIndex[inst[PC].u.rFormat.rt];
            regIndex[0] = 0;
            dump();
            break;
          case 37:
            fprintf(outFile,"\nPC: %d\n", PC);
            fprintf(outFile, "inst: or %s,%s,%s\n", reg[inst[PC].u.rFormat.rd], reg[inst[PC].u.rFormat.rs], reg[inst[PC].u.rFormat.rt]);
            regIndex[inst[PC].u.rFormat.rd] = regIndex[inst[PC].u.rFormat.rs] | regIndex[inst[PC].u.rFormat.rt];
            regIndex[0] = 0;
            dump();
            break;
          case 42:
            fprintf(outFile,"\nPC: %d\n", PC);
            fprintf(outFile, "inst: slt %s,%s,%s\n", reg[inst[PC].u.rFormat.rd], reg[inst[PC].u.rFormat.rs], reg[inst[PC].u.rFormat.rt]);
            regIndex[inst[PC].u.rFormat.rd] = (regIndex[inst[PC].u.rFormat.rs] < regIndex[inst[PC].u.rFormat.rt]);
            regIndex[0] = 0;
            dump();
            break;
          case 12:
          {
            fprintf(outFile,"\nPC: %d\n", PC);
            fprintf(outFile, "inst: syscall\n");
            switch (regIndex[2])
            {
              case 10:
                fprintf(outFile,"exiting simulator\n");
                fclose(outFile);
                exit(EXIT_FAILURE);
              case 5:
                std::cin >> regIndex[2];
                dump();
                break;
              case 1:
                std::cout << regIndex[4] << std::endl;
                dump();
                break;
              default:
                dump();
                break;
            } // end syscall switch
            break;
          }
          default:
            break;
        } // end r-format funct switch
        break;
      }// end r-format instructions
      break;
      case 2:
        fprintf(outFile,"\nPC: %d\n", PC);
        fprintf(outFile, "inst: j %u\n", inst[PC].u.jFormat.target);
        dump();
        PC = inst[PC].u.jFormat.target - 1;
        if (PC < 0 || PC > iCount-1)
        {
         std::cout << "PC is accessing illegal memory address " << PC + 1 << std::endl;
         fprintf(outFile,"\nPC: %d\n", PC + 1);
         fclose(outFile);
         exit(EXIT_FAILURE);
        }
        break;
      case 4:
        fprintf(outFile,"\nPC: %d\n", PC);
        fprintf(outFile, "inst: beq %s,%s,%u\n", reg[inst[PC].u.iFormat.rs], reg[inst[PC].u.iFormat.rt], (int16_t)inst[PC].u.iFormat.offset);
        dump();
        if (regIndex[inst[PC].u.iFormat.rs] == regIndex[inst[PC].u.iFormat.rt])
        {
          PC += inst[PC].u.iFormat.offset - 1;
          if (PC < 0 || PC > (iCount-1))
          {
            std::cout << "PC is accessing illegal memory address " << PC + 1 << std::endl;
            fprintf(outFile,"\nPC: %d\n", PC + 1);
            fclose(outFile);
            exit(EXIT_FAILURE);
          }
        }
        break;
      case 5:
        fprintf(outFile,"\nPC: %d\n", PC);
        fprintf(outFile, "inst: bne %s,%s,%u\n", reg[inst[PC].u.iFormat.rs], reg[inst[PC].u.iFormat.rt], (int16_t)inst[PC].u.iFormat.offset);
        dump();
        if (regIndex[inst[PC].u.iFormat.rs] != regIndex[inst[PC].u.iFormat.rt])
        {
          PC += inst[PC].u.iFormat.offset - 1;
          if (PC < 0 || PC > (iCount-1))
          {
            std::cout << "PC is accessing illegal memory address " << PC + 1 << std::endl;
            fprintf(outFile,"\nPC: %d\n", PC + 1);
            fclose(outFile);
            exit(EXIT_FAILURE);
          }
        }
        break;
      case 9:
        fprintf(outFile,"\nPC: %d\n", PC);
        fprintf(outFile, "inst: addiu %s,%s,%u\n", reg[inst[PC].u.iFormat.rt], reg[inst[PC].u.iFormat.rs], (int16_t)inst[PC].u.iFormat.offset);
        regIndex[inst[PC].u.iFormat.rt] = regIndex[inst[PC].u.iFormat.rs] + inst[PC].u.iFormat.offset;
        regIndex[0] = 0;
        dump();
        break;
      case 35:
        fprintf(outFile,"\nPC: %d\n", PC);
        fprintf(outFile, "inst: lw  %s,%u(%s)\n", reg[inst[PC].u.iFormat.rt], (int16_t)inst[PC].u.iFormat.offset, reg[inst[PC].u.iFormat.rs]);
        if (dCount - 1 < (int16_t)inst[PC].u.iFormat.offset)
        {
          std::cout << "load outside of data memory at address " << iCount + (int16_t)inst[PC].u.iFormat.offset << std::endl;
          fclose(outFile);
          exit(EXIT_FAILURE);
        }
        regIndex[inst[PC].u.iFormat.rt] = dataIndex[inst[PC].u.iFormat.offset];
        regIndex[0] = 0;
        dump();
        break;
      case 43:
        fprintf(outFile,"\nPC: %d\n", PC);
        fprintf(outFile, "inst: sw  %s,%u(%s)\n", reg[inst[PC].u.iFormat.rt], (int16_t)inst[PC].u.iFormat.offset, reg[inst[PC].u.iFormat.rs]);
        if (dCount - 1 < (int16_t)inst[PC].u.iFormat.offset)
        {
          std::cout << "store outside of data memory at address " << iCount + (int16_t)inst[PC].u.iFormat.offset << std::endl;
          fclose(outFile);
          exit(EXIT_FAILURE);
        }
        dataIndex[inst[PC].u.iFormat.offset] = regIndex[inst[PC].u.iFormat.rt];
        dump();
        break;
      default:
        break;
    } // end instructions op code switch
  } // end simulator for loop
  fclose(outFile);
  return 0;
} // end main

void dump()
{
  fprintf(outFile, "\nregs:\n");
  fprintf(outFile,"   $zero = %5d     $at = %5d     $v0 = %5d     $v1 = %5d\n",
          regIndex[0], regIndex[1], regIndex[2], regIndex[3]);
  fprintf(outFile,"     $a0 = %5d     $a1 = %5d     $a2 = %5d     $a3 = %5d\n",
          regIndex[4], regIndex[5], regIndex[6], regIndex[7]);
  fprintf(outFile,"     $t0 = %5d     $t1 = %5d     $t2 = %5d     $t3 = %5d\n",
          regIndex[8], regIndex[9], regIndex[10], regIndex[11]);
  fprintf(outFile,"     $t4 = %5d     $t5 = %5d     $t6 = %5d     $t7 = %5d\n",
          regIndex[12], regIndex[13], regIndex[14], regIndex[15]);
  fprintf(outFile,"     $s0 = %5d     $s1 = %5d     $s2 = %5d     $s3 = %5d\n",
          regIndex[16], regIndex[17], regIndex[18], regIndex[19]);
  fprintf(outFile,"     $s4 = %5d     $s5 = %5d     $s6 = %5d     $s7 = %5d\n",
          regIndex[20], regIndex[21], regIndex[22], regIndex[23]);
  fprintf(outFile,"     $t8 = %5d     $t9 = %5d     $k0 = %5d     $k1 = %5d\n",
          regIndex[24], regIndex[25], regIndex[26], regIndex[27]);
  fprintf(outFile,"     $gp = %5d     $sp = %5d     $fp = %5d     $ra = %5d\n",
          regIndex[28], regIndex[29], regIndex[30], regIndex[31]);
  fprintf(outFile,"     $lo = %5d     $hi = %5d\n", regIndex[32], regIndex[33]);
  fprintf(outFile, "\ndata memory:\n");
  for(int PC = 0; PC < dCount; ++PC)
  {
    if (PC > 1 && PC % 3 == 0)
      fprintf(outFile, "\n");
    fprintf(outFile, "   data[%3d] = %5d", PC, dataIndex[PC]);
  }
  if (dCount > 0)
    fprintf(outFile, "\n\n");
  else
    fprintf(outFile, "\n");
} // end dump registers function
