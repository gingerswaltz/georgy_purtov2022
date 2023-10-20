/// @author gingerswaltz
#pragma once

/// шаблонный класс узел односв€зного списка
template <class T>
class ListNode
{
private:
	T data;			   /// данные узла
	ListNode<T>* prev; /// указатель на предыдущий узел
	ListNode<T>* next; /// указатель на следующий узел
public:
	///  онструктор без параметров
	ListNode() : next(nullptr), prev(nullptr) {}

	///  онструктор с параметром "данные"
	ListNode(const T& data_) : data(data_), next(nullptr), prev(nullptr) {}

	/// ”становить Next
	void SetNext(ListNode<T>* newNext) {
		next = newNext;
	}
	/// ”становить Prev
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