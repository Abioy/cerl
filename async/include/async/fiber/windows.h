/* -------------------------------------------------------------------------
// CERL2: C++ Erlang Server Model 2.0
// 
// Module: async/fiber/windows.h
// Creator: xushiwei
// Email: xushiweizh@gmail.com
// Date: 2009-3-26 19:41:58
// 
// $Id: windows.h 2705 2010-04-28 09:18:07Z xushiwei $
// -----------------------------------------------------------------------*/
#ifndef ASYNC_FIBER_WINDOWS_H
#define ASYNC_FIBER_WINDOWS_H

#ifndef ASYNC_MEMORY_H
#include "../Memory.h"
#endif

#ifndef ASYNC_FIBER_CURRENT_H
#include "current.h"
#endif

NS_CERL_BEGIN

// -------------------------------------------------------------------------
// class Fibers

class Fibers
{
private:
	WINX_THREAD_CALLER_CHECK();

public:
	explicit Fibers(Pools& poolsArg)
	{
	}

	Fiber cerl_call create(
		LPFIBER_START_ROUTINE lpStartAddress,
		LPVOID lpParameter = NULL, size_t dwStackSize = 0)
	{
		WINX_CHECK_THREAD();

		/*
		Q: ���ʹ��windows��fiberʵ����ϷAI����������ʼ����fiber�ص�ʱ�򴴽���2035��fiber��ʱ��CreateFiber����NULL��
		   ��������8,�洢�ռ䲻�㣬�޷���������fiber��ջ������С��4096������msdn��˵��fiber�Ĵ�������Ӧ�����ڴ棬
		   ������Ҳ����������صĴ�����������֪��������û�������о���fiber��ϣ����̽�ֽ��������
		A: �����Ѿ�����ˣ���createfiber�˳�ջ�ı�����С��1M,���Ե�2000�����ҵ�ʱ��Ͳ��ܴ����ˡ�
		   ��CreateFiberEx�������ѱ���ջ����Сһ������ˡ�(by huangweilook@21cn.com)
		*/
		if (dwStackSize == 0)
			dwStackSize = CERL_FIBER_STKSIZE;
		return (Fiber)CreateFiberEx(dwStackSize, dwStackSize, 0, lpStartAddress, lpParameter);
	}

	void cerl_call destroy(Fiber lpFiber)
	{
		WINX_CHECK_THREAD();

		DeleteFiber(lpFiber);
	}
};

// -------------------------------------------------------------------------
// function switchToFiber

__forceinline void cerl_call switchToFiber(Fiber self, Fiber switchTo)
{
	CERL_FIBER_ASSERT_SELF(self);
	CERL_VLOG("Fiber", ("SWITCH: %p - Thread: %.8X\n", switchTo, GetCurrentThreadId()));
	SwitchToFiber(switchTo);
}

__forceinline void cerl_call switchToFiber(Fiber switchTo)
{
	CERL_VLOG("Fiber", ("SWITCH: %p - Thread: %.8X\n", switchTo, GetCurrentThreadId()));
	SwitchToFiber(switchTo);
}

// -------------------------------------------------------------------------
// class ThreadToFiber

class ThreadToFiber
{
public:
	Fiber cerl_call convert(LPVOID lpParameter = NULL)
	{
		return (Fiber)ConvertThreadToFiber(lpParameter);
	}

	void cerl_call unconvert()
	{
		ConvertFiberToThread();
	}
};

#if defined(CERL_DISABLE_FIBER_API)

#undef ConvertThreadToFiber
#undef ConvertThreadToFiberEx
#undef ConvertFiberToThread

#define ConvertThreadToFiber	__unsupport_function__
#define ConvertThreadToFiberEx	__unsupport_function__
#define ConvertFiberToThread	__unsupport_function__

#endif

// -------------------------------------------------------------------------
// class FiberInit

typedef CurrentFiberInit FiberInit;

// -------------------------------------------------------------------------

NS_CERL_END

#endif /* ASYNC_FIBER_WINDOWS_H */
