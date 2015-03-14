/*
@encoding utf8
@ns cerl
@*/

// -----------------------------------------------------------------------
// class MultiIoService

/** MultiIoService �࣬��ʹ�ñ�����ʵ���� IoServicePool�����ڸ� Pool �н��ж��
	IoService�����Ҷ�� IoService ����һ�� Session��
@*/
class MultiIoService
{
	/** ��ʼ������ʼʱ�߳���Ϊ0��
	@*/
	MultiIoService();
	
	/** ���� Session��
	@remark
		���� IoServicePool �Ժ���ǰ startFiber ��ʱ������Ҫ�ĳ� startSession��
		�������Ϊһ�����������յ����������Ժ���ǰ�ǵ��� startFiber ȥ������
		������Ҫ�ĳ� startSession��
	@arg SessionT
		ģ���������ʾ Session �࣬����������� IoService::Task ��run(IoService*, DWORD) ��Ա������
	@arg self
		��ǰ����Ȩ�˳̡�
	@arg session
		һ��const SessionT& ���������� const SessionT& ԭ���ǣ�Session �����ǿ��̴߳��ݵģ�
		����һ���߳�ʱ���ö���ᱻ���ơ�
	@arg dwStackSize
		���� Fiber ʱ��ջ��С��ȱʡΪ0��
	@*/
	template <class SessionT>
	void cerl_call startSession(Fiber self, const SessionT& session, size_t dwStackSize = 0);
	
	/** ��������̣߳�ÿ���̶߳�Ӧһ�� IoService��
	@arg nThread
		�߳���Ŀ��
	@*/
	void cerl_call start(size_t nThread = 2);

	/** MultiIoService ���˳���
		�˳����� IoService��
	@*/
	void cerl_call quit();

	/** �˳������̵߳� IoService��
	@*/
	void cerl_call run();

	/** ��Ӧ�� IoService ��run(FiberCallback lpStartAddress, void* startParam = NULL, size_t dwStackSize = 0),
		�� IoService �Ĳ�ͬ���� IoService ����һ���߳��д����˳̲�ѭ���ȴ��˳���Ϣ��������Ϣ�����������ǰѴ���
		�˳̵������ӵ� start() �д������̶߳��ڵ� IoService �����С�
	@arg [in] lpStartAddress
		�˳̵Ļص�������ַ��
	@arg [in] startParam
		�˳�Я���Ĳ�����
	@arg [in] dwStackSize
		�����˳̵�ջ��С���������Ϊ0������Ĭ�ϴ�С��
	@*/
	void cerl_call run(FiberCallback lpStartAddress, void* startParam = NULL, size_t dwStackSize = 0);
};

// -------------------------------------------------------------------------
// class IoServicePool

typedef  IoServicePool;

// -------------------------------------------------------------------------
// class IoServicePoolInit

/** �� IoServicePool �ķ�װ��ֻ��Ҫ����һ�� IoServicePoolInit ������Զ�
	��ʼ��ȫ�ֵ� IoServicePool ����
@*/
class IoServicePoolInit
{
	/** ���캯����
	@arg threadCount
		��Ҫ�� IoServicePool �����������߳�����ÿ���߳�����һ�� IoService ʵ����
	@*/
	IoServicePoolInit(size_t threadCount = 2);
};

// -------------------------------------------------------------------------
