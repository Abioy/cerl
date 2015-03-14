/* -------------------------------------------------------------------------
// CERL2: C++ Erlang Server Model 2.0
// 
// Module: async/fiber/wincoro/coro.h
// Creator: xushiwei
// Email: xushiweizh@gmail.com
// Date: 2010-2-10 10:41:58
// 
// $Id: coro.h 2419 2010-04-08 14:00:42Z scm $
// -----------------------------------------------------------------------*/
#ifndef ASYNC_FIBER_WINCORO_CORO_H
#define ASYNC_FIBER_WINCORO_CORO_H

// -------------------------------------------------------------------------
// type CoroContext

#pragma pack(1)

typedef struct CoroContext
{
	void* CsEbx;
	void* CsEdi;
	void* CsEsi;
	void* CsEbp;
	void* CsEsp;
	void* CsEip;
	void* ExceptionList;
	void* StackTop;
	void* StackBase;
}
CoroContext;

#pragma pack()

// -------------------------------------------------------------------------
// function coro_swapcontext

EXTERN_C void __fastcall coro_swapcontext(CoroContext* self, CoroContext* to);

// -------------------------------------------------------------------------
// function coro_newcontext

typedef void (WINAPI *CoroFunction)(void* param);

/*
 * __fastcall��
 *	 �������ڲ����� 4 �ֽ�(DWORD)�Ĳ������������ҷֱ𱣴��� ECX��EDX �Ĵ����ڣ�����û�н�����ѹ���ջ��
 *	 ��������ǰ���轫������ջ���������FASTCALL�����������������԰���������ѹ���ջ����������ʱ��Ҫ����Щ������ջ��
 */
__forceinline void __fastcall coro_newcontext(
	CoroContext* self, CoroFunction func, void* param, void* stk, size_t stksize)
{
	__asm
	{
		xor eax, eax;

		mov [ecx], eax;		// self->CsEbx = 0;
		mov [ecx+4], eax;	// self->CsEdi = 0;
		mov [ecx+8], eax;	// self->CsEsi = 0;
		mov [ecx+12], eax;	// self->CsEbp = 0;

		mov [ecx+24], -1;	// self->ExceptionList = -1;

		mov eax, stk;
		mov [ecx+32], eax;	// self->StackBase = stk;

		add eax, stksize;
		mov [ecx+28], eax;	// self->StackTop = stk + stksize;

		sub eax, 8;
		mov [ecx+16], eax;	// self->CsEsp = new-stack-esp;
		mov [ecx+20], edx;	// self->CsEip = func;

		mov ecx, param;
		mov [eax], edx;		// init new stack
		mov [eax+4], ecx;
	}
}

// -------------------------------------------------------------------------

#endif /* ASYNC_FIBER_WINCORO_CORO_H */
