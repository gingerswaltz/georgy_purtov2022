#pragma once
#include <iostream>
#include <string>
#include <list>
#include <random>
#include "Rule.h"

using namespace std;

/// ����� ����������� ����� � ������������ ����������� � ��������� �� ������������
class FormalLanguage
{
private:
	/// ������� �����
	list <Rule> _rules;
	/// ����������� ���������� ����������
	int MaxRepetitionsCount;

	/// ��������� ������� �� ������������
	/// "input" - ������, � ������� ����������� �������
	/// "rule" - ������� �����
	/// "count" - ���������� ���������� ����������

	bool CheckLoop(string input, Rule rule, int count = 5) {
		for (int i = 0; i < count; i++) {
			string key = rule.getKey();
			string value = rule.getValue();

			size_t pos = input.find(key);

			if (pos != -1) // ������ -1 = npos
			{
				input = input.erase(pos, key.length());
				input = input.insert(pos, value);
			}
			else
			{
				return false;
			}
		}
		return true;
	}

	void RefreshRules() {
		for (Rule& rule : _rules) {
			rule.setIsLooped(false);
		}
	}
public:
	/// �����������
	FormalLanguage(list<Rule> rules, int count = 10000)
	{
		_rules = rules;
		MaxRepetitionsCount = count;
	}

	/// ������
	void setRules(list <Rule> rule)
	{
		_rules = rule;
	}

	/// ������
	list<Rule> getRules() const
	{
		return _rules;
	}

	/// ������
	void setMaxRepetitionsCount(int repeat)
	{
		MaxRepetitionsCount = repeat;
	}

	/// ������
	int getMaxRepetitionsCount()
	{
		return MaxRepetitionsCount;
	}

	/// ������������ �����.
	/// ������, ����������� �� ������ ������ �����.
	string OutputLeft()
	{
		string result = "S";
		int count = 0;
		while (count < MaxRepetitionsCount)
		{
			size_t pos = -1;

			// ������ ������� ����� �������������� ������ � �������
			for (const Rule& rule : _rules)
			{
				string key = rule.getKey();
				size_t findPos = result.find(key);
				if ((pos > findPos || pos == -1) && findPos != -1)
				{
					pos = findPos;
					break;
				}

			}

			// ���� �� ������� �������� ����������� ������� - �������
			if (pos == -1)
			{
				break;
			}

			// ������ ��� ������ ���������� ��� �������� ������ ��������������� �������
			list<Rule> rules = {};
			for (const Rule& rule : _rules)
			{
				string key = rule.getKey();
				if (pos == result.find(key))
				{
					rules.push_back(rule);
				}
			}

			// �������� ������� �������
			random_device random;
			mt19937 gen(random());
			uniform_int_distribution<int> dist(0, rules.size() - 1);
			int index = dist(gen);
			auto it = rules.begin();
			advance(it, index);
			Rule r = *it;

			size_t p = result.find(r.getKey());
			result = result.erase(p, r.getKey().length());
			result = result.insert(p, r.getValue());
			cout << result << endl;

			count++;
		}

		return result;
	}


	string OutputLeft(vector<string>& transformations)
	{
		transformations.clear();
		string result = "S";
		int count = 0;

		while (count < MaxRepetitionsCount)
		{
			size_t pos = string::npos;

			// ������ ������� ����� �������������� ������ � �������
			for (const Rule& rule : _rules)
			{
				string key = rule.getKey();
				size_t findPos = result.find(key);
				if ((pos > findPos || pos == string::npos) && findPos != string::npos)
				{
					pos = findPos;
					break;
				}
			}
			// ���� �� ������� �������� ����������� ������� - �������
			if (pos == string::npos)
			{
				break;
			}
			// ��� �������
			// ������ ��� ������� ���������� ��� �������� ������ ��������������� �������
			std::vector<Rule> rules_;
			for (const Rule& rule : _rules) {
				std::string key = rule.getKey();
				if (pos == result.find(key)) {
					rules_.push_back(rule);
				}
			}

			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(0, rules_.size() - 1);
			int index = dis(gen);
			Rule r = rules_[index];

			size_t p = result.find(r.getKey());
			result.replace(p, r.getKey().length(), r.getValue());
			//cout << result << endl;
			transformations.push_back(/*"( " + r.getKey() + " --> " + r.getValue() + " ): "*/ /*+*/ result);
			count++;
		}
		return result;
	}

	string Transformations(string chain_) {
		string buf;
		string result;
		vector<string> transformations;
		bool found = false;
		int counter = 0;
		while (!found) {
			buf = this->OutputLeft(transformations);
			counter++;
			if (counter == 10000000) return "������� �� ���������. ���������� ��� ���\n";
			if (buf == chain_) found = true;
		}

		for (int i = 0; i < transformations.size(); i++)
		{
			result += transformations[i] + "\n";
		}
		result.insert(0, "��������� ������: S\n");

		return result;
	}


	/// ��������� ������ �� ���������� ����
	/// "text" - ������ ��� ��������
	string Translate(string text)
	{
		int count = 0;
		bool isEnd = false;	// true - ���� �� ���� �� ������ �����������
		while (count < MaxRepetitionsCount)
		{
			if (isEnd) break;

			count++;
			isEnd = true;
			// ��������� �� ������� ������ ������� ����� � ������
			for (Rule& rule : _rules)
			{
				if (!rule.getIsLooped())		// ���� ������� �����������
				{
					string key = rule.getKey();
					string value = rule.getValue();

					int pos = text.find(key);

					if (pos != -1)	// ���� ���� ������
					{
						// ���� ������� ����������� ������� - ���������� ���
						if (CheckLoop(text, rule)) rule.setIsLooped(true);
						else
						{
							cout << text << endl;
							text = text.erase(pos, key.length());
							text = text.insert(pos, value);
							isEnd = false;
							break;
						}
					}
				}
				else rule.setIsLooped(!rule.getIsLooped());
			}
		}

		RefreshRules();
		return text;
	}
};