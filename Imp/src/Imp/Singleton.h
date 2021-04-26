#pragma once
namespace Imp
{
	template<class T>
	class Singleton
	{
	public:
		static T* GetInstance()
		{
			if (mpInstance == nullptr)
				mpInstance = new T();

			return mpInstance;
		}

		static void Destory()
		{
			if (mpInstance != nullptr)
				delete mpInstance;
		}

	private:
		static T* mpInstance;
	};

	template<class T>
	T* Singleton<T>::mpInstance = nullptr;
}