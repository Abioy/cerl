/*
@encoding utf8
@ns cerl
@*/

// =========================================================================
// class FastTimer

/** typedef FastTimeMutex
@*/
typedef NS_STDEXT::Mutex FastTimerMutex;

/** ��ʱ����Ҫʵ�ֵĽӿ��ࡣ
@remark
	�ڶ�ʱ�����ʱ����Զ�ִ�� onTimer ������
@see cerl::FastTimerQueue	
@*/
class FastTimer 
{
	/**	���ʼ����
	@*/
	FastTimer();

	/**	��� Timer �Ƿ�ֹͣ��
	@return ���� bool ֵ��
		@val true 
			��ʾֹͣ��
		@val false 
			��ʾ��ֹͣ��
	@*/
	bool cerl_call stopped() const;

	/** �� Timer ֹͣ��
	@*/
	void cerl_call stop();

	/** Timer ����ʱִ�еĺ�����ʵ�ʶ�ʱ������ͨ������ʵ�֡�
	@*/
	void cerl_call onTimer(void* caller);
};

// =========================================================================
// class FastTimerQueue

/** ��ʱ�����С�
@remark
	��ʱ����ʵ�ֶ��У�ʹ�ñ���ʱ�����ȰѲ�ͬ�Ķ�ʱ�� (timer) �󶨵������У�
	ÿ�� precision ��ʱ��֮������һ�ζ��е� tick() ����������ڵĶ�ʱ����
@example
	[[code type="c++"]]
		class MyTimer: public FastTimer{
			void cerl_call onTimer(void* caller)
			{
				...
			}
		};
		FastTimer* myTimer = new MyTimer;
		FastTimeQueue* timerQueue;
		timerQueue->start(myTimer, timeout);
		FastTimeQueue::duration_type precision = timerQueue->getPrecision();
		for(;;)
		{
			timerQueue->tick();
			Sleep(precision);
		}
	[[/code]]
	���� timeout ΪҪ��ʱ��ʱ����
@*/
class FastTimerQueue
{
	/**	��ʼ�����С�
	@arg [in] precision��
		���ȣ�ÿ�� precision ʱ�����ڻ���һ�� tick() ��ִ�С�
	@arg [in] slot_count
		������ slot ��Ŀ��
	@*/
	explicit FastTimerQueue(duration_type precision = 500, size_type slot_count = 31);

	/** ����������
	@*/
	~FastTimerQueue();

	/** ���ؾ���ֵ��
	@return
		���ؾ���ֵ��
	@*/
	duration_type cerl_call getPrecision() const;

	/** ��һ����ʱ��(timer)���붨ʱ�����С�
	@arg timer
		Ҫ����� FastTimer ����
	@arg timeout
		timeout ��ʱ�䡣
	@*/
	void cerl_call start(FastTimer* timer, duration_type timeout);

	/** ���¿�ʼ��ʱ��
	@arg timer
		Ҫ���¿�ʼ�� FastTimer ����
	@arg timeout
		timeout ��ʱ�䡣
	@*/
	void cerl_call restart(FastTimer* timer, duration_type timeout);
	
	/** ÿ�� precision ִ��һ�Ρ�
	@remark
		�����ʱ�ʹ��� slot �� timer �� onTimer ����
	@*/
	void cerl_call tick();
	
};
