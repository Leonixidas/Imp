#pragma once
namespace Imp
{
	template<class T>
	class Singleton
	{
	public:
		static T* GetInstance()
		{
			if (m_pInstance == nullptr)
				m_pInstance = new T();

			return m_pInstance;
		}

		static void Destory()
		{
			if (m_pInstance != nullptr)
				delete m_pInstance;
		}

	private:
		static T* m_pInstance;
	};

	template<class T>
	T* Singleton<T>::m_pInstance = nullptr;
}