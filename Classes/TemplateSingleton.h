#pragma once
template < typename T >
class TemplateSingleton
{
protected:
	TemplateSingleton() {}
	virtual ~TemplateSingleton() {}

public:
	static T * get_instance()
	{
		if (instance == nullptr)
			instance = new T;
		return instance;
	};

	static void destroy_instance()
	{
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	};

private:
	static T * instance;
};
template <typename T> T * TemplateSingleton<T>::instance = 0;