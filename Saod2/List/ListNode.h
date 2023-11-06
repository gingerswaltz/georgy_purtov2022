/// @author gingerswaltz
#pragma once

/// шаблонный класс узел односвязного списка
template <class T>
class ListNode
{
private:
	T data;			   /// данные узла
	ListNode<T>* prev; /// указатель на предыдущий узел
	ListNode<T>* next; /// указатель на следующий узел
public:
	/// Конструктор без параметров
	ListNode() : next(nullptr), prev(nullptr) {}

	/// Конструктор с параметром "данные"
	ListNode(const T& data_) : data(data_), next(nullptr), prev(nullptr) {}

	/// Установить Next
	void SetNext(ListNode<T>* newNext) {
		next = newNext;
	}
	/// Установить Prev
	void SetPrev(ListNode<T>* newPrev) {
		prev = newPrev;
	}

	T Data() const {
		return data;
	}


	ListNode<T>* Next() {
		return next;
	}

	ListNode<T>* Prev() {
		return prev;
	}
};