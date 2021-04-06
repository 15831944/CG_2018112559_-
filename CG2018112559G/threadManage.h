#include<thread>
#include<vector>
#include<string>
#include<map>
using std::vector;
using std::map;
using std::thread;
class threadManage {
public:
	using key = std::string;
	using value = std::thread;
	map<key,value> childThread;
	threadManage() = default;
	~threadManage(){
		for (auto& c : childThread)
			c.second.join();
	}
	void stopAllThreads() {
		for(auto &p:childThread)
			::PostThreadMessage(p.second.get_id(),WM_ACTIVATE)
	}
	/// <summary>
	/// �����̣߳�����߳�δ����
	/// </summary>
	/// <param name="key"></param>
	/// <param name="th"></param>
	/// <returns>�߳��Ƿ񴴽�</returns>
	bool active(const key &key, const thread& th) {
		if (childThread.find(key) == childThread.end())
		{
			childThread.emplace(key, th);
			return true;
		}
		else
			return false;
	}
	
};