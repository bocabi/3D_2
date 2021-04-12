#pragma once
#include <mutex>

template <typename T>
class singleton
{
private :
	inline static T* p;
	inline static std::mutex m;
public:
	singleton() {};
	~singleton() {};
	static T* GetInstance()
	{
		if (!p)
			p = new T;
		return p;
	}
	static void ReleaseIntacne()
	{
		if (p)
			delete p;
		p = nullptr;
	}
};
