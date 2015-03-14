/*
@encoding utf8
@ns cerl
@*/

// -----------------------------------------------------------------------
// class ServerSession

/** ���ඨ����һ����������Session��
	һ�� Session �������� Socket���ȴ����ӣ���������֮��Ĵ����Ͽ����ӡ�
@*/
class ServerSession
{
	/** ���� Session �ĺ�����
	@arg ServerT
		ʵ��Server����ģ�壬��������Ӻ����ݴ�����������ʵ�֡�
	@arg self
		��ǰ�˳̡�
	@arg server
		ServerT ����
	@arg sdAccept
		accept()���ص����Ӻõ� socket ����
	@*/
	template <class ServerT>
	void cerl_call main(Fiber self, ServerT* const server, SOCKET sdAccept);
};

// -----------------------------------------------------------------------
// class ServerRunner
/** �� ServerT �� SessionT �ķ�װ��
	ʹ�õ�ʱ��ֻ��Ҫ���� ServerT��Ȼ��ֱ�ӵ��� run() �Ϳ��ԡ�
@arg ServerT
	ģ���������������ʾ��������߼��� Server�������ṩһ��bool�� MultiThreads ��Ա����
	��ʾ�Ƿ�ʹ�ö��߳�ģʽ��
@arg SessionT
	ģ���������������ʾ Session ��ʵ�֣�ȱʡ���� ServerSession��
@see ServerSession��
@*/
template <class ServerT, class SessionT = ServerSession>
class ServerRunner
{
	typedef ServerT server_type;	
	
	/** �ṩ����һ�� Server �Ľӿڡ�
	@arg self
		��ǰ�˳̶���
	@arg server
		����ʵ��ҵ���߼��� server ����
	@arg socketListen
		���ڼ����� socket ����
	@*/
	HRESULT cerl_call run(Fiber self, server_type* server, SOCKET socketListen);
};

// -----------------------------------------------------------------------