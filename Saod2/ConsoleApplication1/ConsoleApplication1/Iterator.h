#pragma once
template <typename T>
class Iterator {
public:
    // �������� ������������� ��� ��������� �������� ��������
    virtual T operator*() const = 0;

    // �������� ���������� ��� ����������� � ���������� ��������
    virtual Iterator<T>& operator++() = 0;

    // �������� ��������� �� ���������
    virtual bool operator==(const Iterator<T>& other) const = 0;

    // �������� ��������� �� �����������
    virtual bool operator!=(const Iterator<T>& other) const = 0;

    // ����������� ����������
    virtual ~Iterator() = default;
};
