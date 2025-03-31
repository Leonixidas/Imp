#pragma once
namespace Imp
{
	template<class T>
	class Singleton
	{
		Singleton() = default;

	public:
		static T* GetInstance()
		{
			if (m_pInstance == nullptr)
				m_pInstance = new T();

			return m_pInstance;
		}

		static void Destroy()
		{
			if (m_pInstance != nullptr)
				delete m_pInstance;
		}

	private:
		static T* m_pInstance;
	friend T;
	};

	template<class T>
	T* Singleton<T>::m_pInstance = nullptr;
}