#ifndef __LISTENER_LIST_H__
#define __LISTENER_LIST_H__

// C++
#include <algorithm>
#include <vector>

template<class T>
class ListenerList
{
public:
	void addListener(T listener);
	void removeListener(T listener);

protected:
	std::vector<T> _listenerList;
};

template<class T>
void ListenerList<T>::addListener( T listener )
{
	_listenerList.push_back(listener);
}

template<class T>
void ListenerList<T>::removeListener( T listener )
{
	if (_listenerList.empty())
	{
		return;
	}

	auto it = std::find(_listenerList.begin(), _listenerList.end(), listener);
	if (it != _listenerList.end())
	{
		_listenerList.erase(it);
	}
}
#endif // __LISTENER_LIST_H__