#pragma
#ifndef THREAD_MANAGE_H
#define THREAD_MANAGE_H
//container
#include<vector>
#include<map>
#include<set>
//multi-threading
#include<thread>
#include<mutex>
#include<future>
#include<atomic>
//io
#include<sstream>
#include<fstream>
//other
#include<memory>
#include<string>
using std::string;
using std::vector;
using std::map;
using std::set;
using std::thread;
using std::mutex;
using std::future;
using std::promise;
using std::stringstream;
using std::atomic;
using std::shared_ptr;

using std::enable_if;
using std::enable_if_t;
using std::declval;
using std::is_same;

#ifdef _DEBUG
#define PAUSE system("pause");
#define _trace trace
#else
#define PAUSE 
#define _trace(args) 
#endif

//tState value-mean
enum class TM{
	rawInitial=-1,		//��ʼֵ
	insideShell=-2,		//�߳�����������ѿ�ʼִ�У��������Ѿ���ʼִ��������
	leavingShell=-3		//�߳���������Ǽ����뿪�����������˳�
};
template<typename ...args>
inline void trace(string loc,args...) {};
template<typename a0,typename ...args>
inline void trace(string loc, a0 &&a00,args...argss) {
	std::fstream fout("fout.txt", std::ofstream::app);
	fout << loc << ":" << a00 << std::endl;
	fout.close();
	trace(loc,argss...);
};
/// <summary>
/// �߳�����ʱ��Ҫ���̳߳��е�atomic_intֵΪ0
/// </summary>
template<typename Tmain, typename retType, typename ...args>
class threadMain :public thread {
public:
	using base = std::thread;
	threadMain() = delete;

	template<typename ... ags>
	explicit threadMain(atomic<int>* msgEnt,
		typename	Tmain tmain, ags...as) :base([&](atomic<int>*msgEnt) {
			_ASSERT(msgEnt->load() == int(TM::rawInitial));
			msgEnt->store(int(TM::insideShell));
			_trace(__func__,as...);
			tmain( _STD forward<ags...>(as)...);
			msgEnt->store(int(TM::leavingShell));
			},msgEnt) {
//debug need it,i dont konw why
#ifdef _DEBUG
		_trace(__func__, as...);
#endif
	};
};

class threadManage {
public:
	friend class CG2018112559G;
	friend class CCG2018112559GView;
	using key = std::string;
	using value =  std::thread;
	//�߳�״̬
	using tStateElem = std::atomic<int>;
	using tState = std::shared_ptr<tStateElem>;
protected:
	//keyֵ��Ӧ���߳�
	map<key, value> childThread;
	//keyֵ��Ӧ���̵߳�״̬  
	map<key, tState> childThreadStateRecord;

	mutex mu_childStateAcess;
public:
	threadManage() = default;

	~threadManage() {
		for (auto& c : childThread)
			c.second.join();
		is_same<int, int>::value; 
	}
/*
 * 
*/
	void JoinAllThreads() {
		mu_childStateAcess.lock();
		for (auto& p : childThread)
			p.second.join();
		childThread.clear();
		childThreadStateRecord.clear();
		mu_childStateAcess.unlock();
	}
/*
 *  �鿴keyֵ��Ӧ���߳� 
*/
	int countExist(const key& k) {
		checkTerminated();
		mu_childStateAcess.lock();
		int cnt=childThread.count(k);
		mu_childStateAcess.unlock();
		return cnt;
	}
	/// <summary>
	/// �����̵߳���������߳�δ����
	/// </summary>
	/// <param name="th">���ܼ�const���ԣ���Ŀ</param>
	/// <returns>�߳��Ƿ񴴽�</returns>
	template<typename Tmain,typename retType, typename ...args>
	enable_if_t<is_same<decltype(declval<Tmain>()(declval<args...>())),retType>::value,bool>  
		addThread(const key& key,Tmain&tmain, args&&... ags) {
		checkTerminated();
		_trace(__func__, ags...);//still right
		if (countExist(key) == 0)
		{
			mu_childStateAcess.lock();
			//only emplace work
			auto it = childThreadStateRecord.emplace(key, tState());
			
			ASSERT(it.second == true);
			tState& ts = it.first->second;
			ts.reset(new tStateElem(int(TM::rawInitial)));
			thread& th = threadMain<Tmain, retType, args...>(ts.get(), tmain, _STD forward<args...>(ags)...);
			childThread.insert(decltype(childThread)::value_type(key, move(th)));
			mu_childStateAcess.unlock();
			return true;
		}
		else
			return false;
	}
/*
 *  ����join
 */
	int join(key k) {
		mu_childStateAcess.lock();
		if (childThread.count(k) != 0)
		{
			childThread[k].join();
			childThread.erase(k);
			childThreadStateRecord.erase(k);
		} 
		mu_childStateAcess.unlock();
		return 0;
	}
/*
 *	����Ƿ��߳����������˳�
 *	if so,join it��and clean the record
 */
	int checkTerminated() {
		int cnt = 0;
		mu_childStateAcess.lock();
		vector<key> awaitingToErase;
		for(auto &p:childThreadStateRecord)
			if (p.second.get()->load() == int(TM::leavingShell))
			{
				key k = p.first;
				auto it = childThread.find(k);
				ASSERT(it != childThread.end());
				it->second.join();
				childThread.erase(it);
				awaitingToErase.push_back(k);
				cnt++;
			}
		for (auto &k : awaitingToErase)
			childThreadStateRecord.erase(k);
		mu_childStateAcess.unlock();
		return cnt;
	}
	static int getThreadId() {
		std::stringstream ss;
		ss << std::this_thread::get_id();
		return std::stoi(ss.str());
	}
};

#endif