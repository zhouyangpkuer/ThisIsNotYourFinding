#ifndef _EXEC_H
#define _EXEC_H
#include "params.h"
#include <cmath>//here
#include "float.h"

// #define DEBUG
using namespace std;

void print_type(const char *str)
{
	printf("%s:\n", str);
}
void print_reg(uint num)
{
	printf("REG%u: %lld,", num, reg[num]);
}
void print_pc()
{
	printf("PC: %X,", PC);
}

bool LUI(uint rd, uint imm)
{
	reg[rd] = signExtend(imm, 20);
	PC += 4;
	return true;
}

bool AUIPC(uint rd, uint imm)
{
	reg[rd] = PC + signExtend(imm, 20);
	PC += 4;
	return true;
}

bool JAL(uint rd, uint imm)
{	
	if(rd != 0)
	{
		reg[rd] = PC + 4;
	}
	//[20,1]
	PC += signExtend(imm, 21);
	return true;
}
bool JALR(uint rd, uint rs1, uint imm)
{

	ulint temp = PC;
	//[11,0]
	PC = ((reg[rs1] + signExtend(imm, 12)) >> 1) << 1;
	if(rd != 0)
	{
		reg[rd] = temp + 4;
	}
	return true;
}




bool BEQ(uint rs1, uint rs2, uint imm)
{
	if(reg[rs1] == reg[rs2])
		PC += signExtend(imm, 13);
	else
		PC += 4;
	return true;
}
bool BNE(uint rs1, uint rs2, uint imm)
{
	if(reg[rs1] != reg[rs2])
		PC += signExtend(imm, 13);
	else
		PC += 4;
	return true;
}
bool BLT(uint rs1, uint rs2, uint imm)
{
	if((lint)reg[rs1] < (lint)reg[rs2])
		PC += signExtend(imm, 13);
	else
		PC += 4;
	return true;
}
bool BGE(uint rs1, uint rs2, uint imm)
{
	if((lint)reg[rs1] >= (lint)reg[rs2])
		PC += signExtend(imm, 13);
	else
		PC += 4;
	return true;
}
bool BLTU(uint rs1, uint rs2, uint imm)
{
	if(reg[rs1] < reg[rs2])
		PC += signExtend(imm, 13);
	else
		PC += 4;
	
	return true;
}
bool BGEU(uint rs1, uint rs2, uint imm)
{
	if(reg[rs1] >= reg[rs2])
		PC += signExtend(imm, 13);
	else
		PC += 4;
	return true;
}




bool LB(uint rs1, uint rd, uint imm)
{
	ulint target_addr = (lint)reg[rs1] + signExtend(imm, 12);
	printf("%x 1\n", target_addr);
	reg[rd] = signExtend64(readMem(target_addr, 1), 8);
	PC += 4;
	return true;
}

bool LBU(uint rs1, uint rd, uint imm)
{
	ulint target_addr = (lint)reg[rs1] + signExtend(imm, 12);
	printf("%x 2\n", target_addr);
	
	reg[rd] = readMem(target_addr, 1);
	PC += 4;
	return true;
}
//first size, next sign
bool LH(uint rs1, uint rd, uint imm)
{
	ulint target_addr = (lint)reg[rs1] + signExtend(imm, 12);
	printf("%x 3\n", target_addr);
	reg[rd] = signExtend64(readMem(target_addr, 2), 16) ;
	PC += 4;
	return true;
}
bool LHU(uint rs1, uint rd, uint imm)
{
	ulint target_addr = (lint)reg[rs1] + signExtend(imm, 12);
	printf("%x 4\n", target_addr);
	reg[rd] = readMem(target_addr, 2);
	PC += 4;
	return true;
}
bool LW(uint rs1, uint rd, uint imm)
{
	ulint target_addr = (lint)reg[rs1] + signExtend(imm, 12);
	printf("%x 5\n", target_addr);
	reg[rd] = signExtend64(readMem(target_addr, 4), 32) ;
	PC += 4;
	return true;
}
bool LWU(uint rs1, uint rd, uint imm)
{
	ulint target_addr = (lint)reg[rs1] + signExtend(imm, 12);
	printf("%x 6\n", target_addr);
	reg[rd] = readMem(target_addr, 4);
	PC += 4;
	return true;		
}
bool LD(uint rs1, uint rd, uint imm)
{
	ulint target_addr = (lint)reg[rs1] + signExtend(imm, 12);
	printf("%x 7\n", target_addr);
	reg[rd] = signExtend64(readMem(target_addr, 8), 64);
	PC += 4;
	return true;
}



bool SB(uint rs1, uint rs2, uint imm)
{
	ulint target_addr = (lint)reg[rs1] + signExtend(imm, 12);
	printf("%x 8\n", target_addr);
	writeMem(target_addr, reg[rs2] & 0xff, 1); 
	PC += 4;
	return true;
}
bool SH(uint rs1, uint rs2, uint imm)
{
	ulint target_addr = (lint)reg[rs1] + signExtend(imm, 12);
	printf("%x 9\n", target_addr);
	writeMem(target_addr, reg[rs2] & 0xffff, 2); 
	PC += 4;
	return true;
}
bool SW(uint rs1, uint rs2, uint imm)
{
	ulint target_addr = (lint)reg[rs1] + signExtend(imm, 12);
	printf("%x a\n", target_addr);
	writeMem(target_addr, reg[rs2] & 0xffffffff, 4); 
	PC += 4;
	return true;
}
bool SD(uint rs1, uint rs2, uint imm)
{
	ulint target_addr = (lint)reg[rs1] + signExtend(imm, 12);
	printf("%x b\n", target_addr);
	writeMem(target_addr, reg[rs2] & 0xffffffffffffffff, 8); 
	PC += 4;
	return true;
}



bool ADDI(uint rs1, uint rd, uint imm)
{
	printf("%lld\n", reg[rd]);
	reg[rd] = reg[rs1] + signExtend(imm, 12);
	printf("%lld\n", reg[rd]);

	PC += 4;	
	return true;
}
bool ADDIW(uint rs1, uint rd, uint imm)
{
	int temp = (int)reg[rs1] + (int)signExtend(imm, 12);
	reg[rd] = (lint)temp;
	PC += 4;
	return true;
}

bool SLTI(uint rs1, uint rd, uint imm)
{
	if((lint)reg[rs1] < signExtend(imm, 12))
		reg[rd] = 1;
	else
		reg[rd] = 0;
	PC += 4;	
	return true;
}
bool SLTIU(uint rs1, uint rd, uint imm)
{
	if(reg[rs1] < (ulint)signExtend(imm, 12))
		reg[rd] = 1;
	else
		reg[rd] = 0;
	PC += 4;	
	return true;
}




bool XORI(uint rs1, uint rd, uint imm)
{
	reg[rd] = reg[rs1] ^ signExtend(imm, 12);
	PC += 4;	
	return true;
}
bool ORI(uint rs1, uint rd, uint imm)
{
	reg[rd] = reg[rs1] | signExtend(imm, 12);
	PC += 4;	
	return true;
}
bool ANDI(uint rs1, uint rd, uint imm)
{
	reg[rd] = reg[rs1] & signExtend(imm, 12);
	PC += 4;	
	return true;
}




bool SLLI(uint rs1, uint rd, uint shamt)
{
	reg[rd] = reg[rs1] << shamt;
	PC += 4;
	return true;
}
bool SLLIW(uint rs1, uint rd, uint shamt)
{
	int temp = (uint)reg[rs1] << shamt;
	reg[rd] = (lint)temp;
	PC += 4;
	return true;
}
bool SRLI(uint rs1, uint rd, uint shamt)
{
	reg[rd] = reg[rs1] >> shamt;
	PC += 4;
	return true;
}
bool SRLIW(uint rs1, uint rd, uint shamt)
{
	uint temp = (uint)reg[rs1] >> shamt;
	reg[rd] = (lint)(int)temp;
	PC += 4;
	return true;
}
bool SRAI(uint rs1, uint rd, uint shamt)
{
	reg[rd] = (lint)reg[rs1] >> shamt;
	PC += 4;
	return true;
}
bool SRAIW(uint rs1, uint rd, uint shamt)
{
	int temp = (int)reg[rs1] >> shamt;
	reg[rd] = (lint)temp;
	PC += 4;
	return true;
}





bool ADD(uint rs1, uint rs2, uint rd)
{
	reg[rd] = (lint)reg[rs1] + (lint)reg[rs2];
	PC += 4;
	return true;
}

bool ADDW(uint rs1, uint rs2, uint rd)
{
	int temp = (int)reg[rs1] + (int)reg[rs2];
	reg[rd] = (lint)temp;
	PC += 4;
	return true;	
}

bool SUB(uint rs1, uint rs2, uint rd)
{
	reg[rd] = (lint)reg[rs1] - (lint)reg[rs2];
	PC += 4;
	return true;
}
bool SUBW(uint rs1, uint rs2, uint rd)
{
	int temp = (int)reg[rs1] - (int)reg[rs2];
	reg[rd] = (lint)temp;
	PC += 4;
	return true;	
}

bool SLL(uint rs1, uint rs2, uint rd)
{
	uint shamt = (uint)reg[rs2] & ((1 << 6) - 1);
	reg[rd] = (ulint)reg[rs1] << shamt;
	PC += 4;
	return true;
}
bool SLLW(uint rs1, uint rs2, uint rd)
{
	uint shamt = (uint)reg[rs2] & ((1 << 5) - 1);
	uint temp = (uint)reg[rs1] << shamt;
	reg[rd] = (lint)(int)temp;
	PC += 4;
	return true;
}

bool SLT(uint rs1, uint rs2, uint rd)
{
	if((lint)reg[rs1] < (lint)reg[rs2])
		reg[rd] = 1;
	else
		reg[rd] = 0;
	PC += 4;
	return true;
}
bool SLTU(uint rs1, uint rs2, uint rd)
{
	if((ulint)reg[rs1] < (ulint)reg[rs2])
		reg[rd] = 1;
	else
		reg[rd] = 0;
	PC += 4;
	return true;
}
bool XOR(uint rs1, uint rs2, uint rd)
{
	reg[rd] = reg[rs1] ^ reg[rs2];
	PC += 4;
	return true;
}
bool SRL(uint rs1, uint rs2, uint rd)
{
	uint shamt = (uint)reg[rs2] & ((1 << 6) - 1);
	reg[rd] = (ulint)reg[rs1] >> shamt;
	PC += 4;
	return true;
}
bool SRLW(uint rs1, uint rs2, uint rd)
{
	uint shamt = (uint)reg[rs2] & ((1 << 5) - 1);
	uint temp = (uint)reg[rs1] >> shamt;
	reg[rd] = (lint)(int)temp;
	PC += 4;
	return true;	
}

bool SRA(uint rs1, uint rs2, uint rd)
{
	uint shamt = (uint)reg[rs2] & ((1 << 6) - 1);
	reg[rd] = reg[rs1] >> shamt;
	PC += 4;
	return true;
}
bool SRAW(uint rs1, uint rs2, uint rd)
{
	uint shamt = (uint)reg[rs2] & ((1 << 5) - 1);
	int temp = (int)reg[rs1] >> shamt;
	reg[rd] = (lint)temp;
	PC += 4;
	return true;	
}

bool OR(uint rs1, uint rs2, uint rd)
{
	reg[rd] = reg[rs1] | reg[rs2];
	PC += 4;
	return true;
}
bool AND(uint rs1, uint rs2, uint rd)
{
	reg[rd] = reg[rs1] & reg[rs2];
	PC += 4;
	return true;
}


// bool MUL(uint rs1, uint rs2, uint rd)
// {
// 	lint temp = reg[rs1] * reg[rs2];
// 	reg[rd] = temp & (((ulint)1 << 32) - 1);
// 	PC += 4;
// 	return true;
// }
bool MUL(uint rs1, uint rs2, uint rd)
{
	//Here I replace your code, because mul just place the lower 64bit to the rd register 

	//lint temp = reg[rs1] * reg[rs2];
	//reg[rd] = temp & (((ulint)1 << 32) - 1);
	reg[rd] = (lint)reg[rs1] * (lint)reg[rs2];

	PC += 4;
	return true;
}
bool MULH(uint rs1, uint rs2, uint rd)
{
	lint temp = reg[rs1] * reg[rs2];
	reg[rd] = (temp >> 32) & (((ulint)1 << 32) - 1);
	PC += 4;
	return true;
}
bool MULHSU(uint rs1, uint rs2, uint rd)
{
	lint temp = (lint)reg[rs1] * reg[rs2];
	reg[rd] = (temp >> 32) & (((ulint)1 << 32) - 1);
	PC += 4;
	return true;
}
bool MULHU(uint rs1, uint rs2, uint rd)
{
	ulint temp = (ulint)reg[rs1] * (ulint)reg[rs2];
	reg[rd] = (temp >> 32) & (((ulint)1 << 32) - 1);
	PC += 4;
	return true;
}

bool DIV(uint rs1, uint rs2, uint rd)
{
	lint temp = (lint)reg[rs1] / (lint)reg[rs2];
	reg[rd] = temp;
	PC += 4;
	return true;
}
bool DIVU(uint rs1, uint rs2, uint rd)
{
	ulint temp = (ulint)reg[rs1] / (ulint)reg[rs2];
	reg[rd] = temp;
	PC += 4;
	return true;
}
bool REM(uint rs1, uint rs2, uint rd)
{
	lint temp = (lint)reg[rs1] % (lint)reg[rs2];
	reg[rd] = temp;
	PC += 4;
	return true;	
}
bool REMU(uint rs1, uint rs2, uint rd)
{
	ulint temp = (ulint)reg[rs1] % (ulint)reg[rs2];
	reg[rd] = temp;
	PC += 4;
	return true;
}

bool MULW(uint rs1, uint rs2, uint rd)
{
	int temp = (int)reg[rs1] * (int)reg[rs2];
	reg[rd] = (lint)temp;
	PC += 4;
	return true;
}
bool DIVW(uint rs1, uint rs2, uint rd)
{
	int temp = (int)reg[rs1] / (int)reg[rs2];
	reg[rd] = (lint)temp;
	PC += 4;
	return true;
}
bool DIVUW(uint rs1, uint rs2, uint rd)
{
	uint temp = (uint)reg[rs1] / (uint)reg[rs2];
	reg[rd] = (lint)(int)temp;
	PC += 4;
	return true;
}
bool REMW(uint rs1, uint rs2, uint rd)
{
	int temp = (int)reg[rs1] % (int)reg[rs2];
	reg[rd] = (lint)temp;
	PC += 4;
	return true;
}
bool REMUW(uint rs1, uint rs2, uint rd)
{
	uint temp = (uint)reg[rs1] % (uint)reg[rs2];
	reg[rd] = (lint)(int)temp;
	PC += 4;
	return true;
}

bool ECALL(bool &EXIT)
{

	lint a0 = reg[reg_a0];
	lint a1 = reg[reg_a1];
	lint a2 = reg[reg_a2];
	lint a3 = reg[reg_a3];
	lint a4 = reg[reg_a4];
	lint a5 = reg[reg_a5];
	int ret;
	static int cnt_brk = 0;
	switch(reg[reg_sys_num])
	{
		//SYS_close
		case 57:
			// int ret = syscall(SYS_close, (int)a0);
			ret = syscall(SYS_close, a0, a1, a2, a3, a4, a5);
			reg[reg_a0] = (lint)ret;
			// printf("SYS_close ret: %d\n", ret);
			break;
		//SYS_lseek
		case 62:
			ret = syscall(SYS_lseek, a0, a1, a2, a3, a4, a5);
			reg[reg_a0] = (lint)ret;
			// printf("SYS_lseek ret: %d\n", ret);
			break;
		//SYS_read
		case 63:
			ret = syscall(SYS_read, a0, vm + a1, a2, a3, a4, a5);
			// int ret = syscall(SYS_read, (int)a0, (void *)a1, (size_t)a2);
			reg[reg_a0] = (lint)ret;
			// printf("SYS_read ret: %d\n", ret);
			break;

		//SYS_write
		case 64:
			// printf("****%x****\n", PC);

			ret = syscall(SYS_write, a0, vm + a1, a2, a3, a4, a5);
			// for(int i = 0; i < a2; i++)
			// {
				// printf("%c", vm[a1 + i]);
			// printf("%d\n", a2);
			// int ret = syscall(SYS_write, (int)a0, (const void *)a1, (size_t)a2);
			reg[reg_a0] = (lint)ret;
			// printf("SYS_write ret: %d\n", ret);
			break;




		//SYS_fstat
		case 80:
			ret = syscall(SYS_fstat, a0, a1, a2, a3, a4, a5);
			// int ret = syscall(SYS_fstat, (int)a0, (void *)a1, (size_t)a2);
			reg[reg_a0] = (lint)ret;
			// reg[reg_a0] = 1;
			// printf("SYS_fstat ret: %d\n", ret);
			break;





		//SYS_exit
		case 93:
			// EXIT = true;
			// printf("Successfully exit!\n");
			//ret = syscall(SYS_exit, a0, a1, a2, a3, a4, a5);
			reg[reg_a0] = 1;
			EXIT = true;
			// printf("SYS_exit ret: %d\n", ret);
			break;

		//SYS_gettimeofday
		case 169:
			ret = syscall(SYS_gettimeofday, a0, a1, a2, a3, a4, a5);
			
			reg[reg_a0] = 0;

			// reg[reg_a0] = (lint)ret;
			
			// printf("SYS_gettimeofday ret: %d\n", ret);
			break;

		//SYS_brk
		case 214:
			// ret = syscall(SYS_brk, a0, a1, a2, a3, a4, a5);
			// reg[reg_a0] = (lint)ret;
			reg[reg_a0] = brk_addr - cnt_brk * brk_lim;
			cnt_brk ++; 
			// printf("SYS_brk ret: %d\n", reg[reg_a0]);
			break;

		default:
			printf("Other sys_call %lld, uncompleted!\n", reg[reg_sys_num]);
			break;
	};
	PC += 4;
	return true;
}








//F instruction below
// bool FLW(uint rs1, uint imm, uint rd)
// {
// 	ulint target_addr = reg[rs1] + (int)imm;
// 	float *p = (float *)(vm + target_addr);
// 	f_reg[rd].f[0] = (float)(*p);
// 	PC += 4;
// 	return true;
// }

// bool FSW(uint rs1, uint rs2, uint imm)
// {
// 	ulint target_addr = reg[rs1] + (int)imm;
// 	float *p = (float *)(vm + target_addr);
// 	*p = f_reg[rs2].f[0];
// 	PC += 4;
// 	return true;
// }
// bool FLW(uint rs1, uint imm, uint rd)
// {
// 	ulint target_addr = reg[rs1] + (((int)imm << 20) >> 20);
// 	float *p = (float *)(vm + target_addr);
// 	f_reg[rd].f[0] = (float)(*p);
// 	PC += 4;
// 	return true;
// }

// bool FSW(uint rs1, uint rs2, uint imm)
// {
// 	ulint target_addr = reg[rs1] + (((int)imm << 20) >> 20);
// 	float *p = (float *)(vm + target_addr);
// 	*p = f_reg[rs2].f[0];
// 	PC += 4;
// 	return true;
// }

// bool FMUL_S(uint rs1, uint rs2, uint rd)
// {
// 	float temp = f_reg[rs1].f[0] * f_reg[rs2].f[0];
// 	f_reg[rd].f[0] = temp;
// 	PC += 4;
// 	return true;
// }

// bool FDIV_S(uint rs1, uint rs2, uint rd)
// {
// 	float temp = f_reg[rs1].f[0] / f_reg[rs2].f[0];
// 	f_reg[rd].f[0] = temp;
// 	PC += 4;
// 	return true;
// }

// bool FCVT_S_W(uint rs1, uint rd)
// {
// 	// f_reg[rd].f[0] = float(reg[rs1]&0xffffffff);
// 	f_reg[rd].f[0] = (float)(int)reg[rs1];

// 	PC += 4;
// 	return true;
// }

// bool FCVT_S_L(uint rs1, uint rd)
// {
// 	f_reg[rd].f[0] = (float)(lint)reg[rs1];
// 	PC += 4;
// 	return true;
// }



// bool sym = false;
// //here is double floating point function
// bool FSGNJ_D(uint rs1, uint rs2, uint rd)
// {
// 	double temp1 = f_reg[rs1].d;
// 	double temp2 = f_reg[rs2].d;
// 	if(temp2 < 0)
// 	{
// 		if(temp1 < 0)
// 			f_reg[rd].d = temp1;
// 		else
// 			f_reg[rd].d = -temp1;
// 	}
// 	else
// 	{
// 		if(temp1 < 0)
// 			f_reg[rd].d = -temp1;
// 		else
// 			f_reg[rd].d = temp1;
// 	}
// 	PC += 4;
// 	return true;
// }
// bool FSGNJN_D(uint rs1, uint rs2, uint rd)
// {
// 	double temp1 = f_reg[rs1].d;
// 	double temp2 = f_reg[rs2].d;
// 	if(temp2 < 0)
// 	{
// 		if(temp1 < 0)
// 			f_reg[rd].d = -temp1;
// 		else
// 			f_reg[rd].d = temp1;
// 	}
// 	else
// 	{
// 		if(temp1 < 0)
// 			f_reg[rd].d = temp1;
// 		else
// 			f_reg[rd].d = -temp1;
// 	}
// 	PC += 4;
// 	return true;
// }
// bool FSGNJX_D(uint rs1, uint rs2, uint rd)
// {
// 	double temp1 = f_reg[rs1].d;
// 	double temp2 = f_reg[rs2].d;
// 	if(temp2 < 0)
// 	{
// 		if(temp1 < 0)
// 			f_reg[rd].d = -temp1;
// 		else
// 			f_reg[rd].d = -temp1;
// 	}
// 	else
// 	{
// 		if(temp1 < 0)
// 			f_reg[rd].d = temp1;
// 		else
// 			f_reg[rd].d = temp1;
// 	}
// 	PC += 4;
// 	return true;
// }
// bool FMV_X_D(uint rs1, uint rd)
// {
// 	reg[rd] = (lint)f_reg[rs1].d;
// 	PC += 4;
// 	return true;
// }
// bool FMV_D_X(uint rs1, uint rd)
// {
// 	f_reg[rd].d = (double)reg[rs1];
// 	PC += 4;
// 	return true; 
// }

// // bool FLD(uint rs1, uint imm, uint rd)
// // {
// // 	ulint target_addr = f_reg[rs1].d + (int)imm;
// // 	double * p = (double *)(vm + target_addr);
// // 	f_reg[rd].d = (*p);
// // 	PC += 4;
// // 	return true;

// // }
// // bool FSD(uint rs1, uint imm, uint rs2)
// // {
// // 	ulint target_addr = f_reg[rs1].d + (int)imm;
// // 	double *p = (double *)(vm + target_addr);
// // 	*p = f_reg[rs2].d; 
// // 	PC += 4;
// // 	return true;
// // }

// union F64
// {
// 	double y;
// 	unsigned char t[8];
// };


// bool FLD(uint rs1, uint imm, uint rd)
// {
// 	ulint target_addr = reg[rs1] + (((int)imm << 20) >> 20);
// 	double * p = (double *)(vm + target_addr);
// 	f_reg[rd].d = (*p);
	
// 	// printf("FLD %lf\n", f_reg[rd].d);

// 	// for(int i = 0; i < 8; i++)
// 	// {
// 	// 	printf("%0x ", vm[target_addr + i]);
// 	// }
// 	// printf("\n");
	
// 	// F64 * p = (F64 *)(vm + target_addr);
	
// 	// F64 p;
// 	// for(int i = 0; i < 8; i++)
// 	// {
// 	// 	p.t[i] = vm[target_addr + i];
// 	// }
// 	// f_reg[rd].d = p.y;
	
// 	// printf("%lf\n", f_reg[rd].d);
// 	// for(int i = 0; i < 8; i++)
// 	// {
// 	// 	printf("%0x ", vm[target_addr + i]);
// 	// }
// 	// printf("\n");
	


// 	PC += 4;
// 	return true;


// 	// ulint target_addr = reg[rs1] + (((int)imm << 20) >> 20);
// 	// lint * p = (lint *)(vm + target_addr);
// 	// reg[rd] = (*p);
// 	// PC += 4;
// 	// return true;
// }
// bool FSD(uint rs1, uint imm, uint rs2)
// {
// 	ulint target_addr = reg[rs1] + (((int)imm << 20) >> 20);
// 	double *p = (double *)(vm + target_addr);
// 	*p = f_reg[rs2].d;
// 	// printf("FSD %lf\n", f_reg[rs2].d);
// 	PC += 4;

// 	sym = true;
	

// 	return true;
// }
// bool FMADD_D(uint rs1, uint rs2, uint rs3, uint rd)
// {
// 	f_reg[rd].d = f_reg[rs1].d * f_reg[rs2].d + f_reg[rs3].d;
// 	PC += 4;
// 	return true;
// }
// bool FMSUB_D(uint rs1, uint rs2, uint rs3, uint rd)
// {
// 	f_reg[rd].d = f_reg[rs1].d * f_reg[rs2].d - f_reg[rs3].d;
// 	PC += 4;
// 	return true;
// }
// bool FNMSUB_D(uint rs1, uint rs2, uint rs3, uint rd)
// {
// 	f_reg[rd].d = -(f_reg[rs1].d * f_reg[rs2].d - f_reg[rs3].d);
// 	PC += 4;
// 	return true;
// }
// bool FNMADD_D(uint rs1, uint rs2, uint rs3, uint rd)
// {
// 	f_reg[rd].d = -(f_reg[rs1].d * f_reg[rs2].d + f_reg[rs3].d);
// 	PC += 4;
// 	return true;
// }
// bool FADD_D(uint rs1, uint rs2, uint rd)
// {
// 	f_reg[rd].d = f_reg[rs1].d + f_reg[rs2].d;
// 	PC += 4;
// 	return true;
// }
// bool FSUB_D(uint rs1, uint rs2, uint rd)
// {
// 	f_reg[rd].d = f_reg[rs1].d - f_reg[rs2].d;
// 	PC += 4;
// 	return true;
// }
// bool FMUL_D(uint rs1, uint rs2, uint rd)
// {
// 	f_reg[rd].d = f_reg[rs1].d * f_reg[rs2].d;
// 	PC += 4;
// 	return true;
// }
// bool FDIV_D(uint rs1, uint rs2, uint rd)
// {
// 	f_reg[rd].d = f_reg[rs1].d / f_reg[rs2].d;
// 	PC += 4;
// 	return true;
// }
// bool FSQRT_D(uint rs1, uint rd)
// {
// 	f_reg[rd].d = sqrt(f_reg[rs1].d);
// 	PC += 4;
// 	return true;
// }
// bool FCVT_S_D(uint rs1, uint rd)
// {

// 	f_reg[rd].f[0] = (float) f_reg[rs1].d;
// 	f_reg[rd].f[1] = 0;
// 	PC += 4;
// 	return true;
// }
// bool FCVT_D_S(uint rs1, uint rd)
// {

// 	f_reg[rd].d = (double) f_reg[rs1].f[0];
// 	PC += 4;
// 	return true;
// }
// bool FEQ_D(uint rs1, uint rs2, uint rd)
// {
// 	reg[rd] = (fabs(f_reg[rs1].d - f_reg[rs2].d)) < 1e-9? 1 : 0;
// 	PC += 4;
// 	return true;
// }
// bool FLT_D(uint rs1, uint rs2, uint rd)
// {
// 	reg[rd] = f_reg[rs1].d < f_reg[rs2].d? 1 : 0;
// 	PC += 4;
// 	return true;
// }
// bool FLE_D(uint rs1, uint rs2, uint rd)
// {
// 	if(f_reg[rs1].d < f_reg[rs2].d || (fabs(f_reg[rs1].d - f_reg[rs2].d) < 1e-10))
// 		reg[rd] = 1;
// 	else
// 		reg[rd] = 0;
// 	PC += 4;
// 	return true;
// }
// bool FCVT_W_D(uint rs1, uint rd)
// {
// 	reg[rd] = (int) f_reg[rs1].d;
// 	PC += 4;
// 	return true;
// }
// bool FCVT_WU_D(uint rs1, uint rd)
// {
// 	reg[rd] = (uint) f_reg[rs1].d;
// 	PC += 4;
// 	return true;
// }
// bool FCVT_D_W(uint rs1, uint rd)
// {
// 	f_reg[rd].d = (double) f_reg[rs1].d;
// 	PC += 4;
// 	return true;
// }
// bool FCVT_D_WU(uint rs1, uint rd)
// {
// 	f_reg[rd].d = (double) (ulint)f_reg[rs1].d;
// 	PC += 4;
// 	return true;
// }





#endif //_EXEC_H