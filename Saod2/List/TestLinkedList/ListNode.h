/// @author gingerswaltz
#pragma once

/// ��������� ����� ���� ������������ ������
template <class T>
class ListNode
{
private:
	T data;			   /// ������ ����
	ListNode<T>* prev; /// ��������� �� ���������� ����
	ListNode<T>* next; /// ��������� �� ��������� ����
public:
	/// ����������� ��� ����������
	ListNode() : next(nullptr), prev(nullptr) {}

	/// ����������� � ���������� "������"
	ListNode(const T& data_) : data(data_), next(nullptr), prev(nullptr) {}

	/// ���������� Next
	void SetNext(ListNode<T>* newNext) {
		next = newNext;
	}
	/// ���������� Prev
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