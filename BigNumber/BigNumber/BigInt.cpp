#include "BigInt.h"
#include <deque>
#include <iostream>

const Integer Integer::add(const Integer& other) const
{
	Integer result;
	std::vector<unsigned int> addValue;
	bool addPositive = true;

	if (other.m_Value.size() > m_Value.size())
	{
		result.m_Value = other.m_Value;
		result.m_Positive = other.m_Positive;
		addValue = m_Value;
		addPositive = m_Positive;
	}
	else
	{
		result.m_Value = m_Value;
		result.m_Positive = other.m_Positive;
		addValue = other.m_Value;
		addPositive = other.m_Positive;
	}

	while (addValue.size() != result.m_Value.size())
	{
		if (addPositive)
		{
			addValue.push_back(0);
		}
		else
		{
			addValue.push_back(0xffffffff);
		}
	}

	int carryBit = 0;

	for (int i = 0; i < result.m_Value.size(); i++)
	{
		unsigned int original = result.m_Value[i];

		if (i < addValue.size())
		{
			result.m_Value[i] += addValue[i];
		}
		result.m_Value[i] += carryBit;

		//overflow 발생
		if (original > result.m_Value[i])
		{
			carryBit = 1;
		}
		else
		{
			carryBit = 0;
		}
	}

	if (carryBit == 1 && result.m_Positive != addPositive)
	{
		result.m_Positive = true;
		result.m_Value.push_back(1);
	}

	return result;
}

Integer::Integer()
{
	m_Value.clear();
}

Integer::Integer(int n)
{
	m_Value.push_back(n);
	if (n < 0)
	{
		m_Positive = false;
	}
	else
	{
		m_Positive = true;
	}
}

Integer::Integer(const std::string& n)
{
	if (n[0] == '-')
	{
		std::string number(n.begin() + 1, n.end());
		stringToValue(number);
		*this = signSwitch();
	}
	else if (n[0] == '+')
	{
		std::string number(n.begin() + 1, n.end());
		stringToValue(number);
	}
	else
	{
		stringToValue(n);
	}
}

Integer::Integer(const Integer& other) 
: m_Value(other.m_Value), m_Positive(other.m_Positive)
{
}

Integer::~Integer()
{

}

void Integer::stringToValue(const std::string& n)
{
	std::deque<int> str;
	std::vector<int> binary;

	m_Value.clear();

	for (int i = 0; i < n.size(); i++)
	{
		str.push_back(n[i] - '0');
	}

	while (!str.empty())
	{
		int bit = str[str.size() - 1] % 2;
		binary.push_back(bit);

		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] % 2 != 0 && i != str.size() - 1)
			{
				str[i + 1] += 10;
			}
			str[i] /= 2;
		}

		while (!str.empty() && str[0] == 0)
		{
			str.pop_front();
		}
	}

	for (int i = 0; i < binary.size(); i += 32)
	{
		int digit = (i + 32 < binary.size()) ? i + 32 : binary.size();

		m_Value.push_back(0);
		for (int j = digit - 1; j >= i; j--)
		{
			int size = m_Value.size();

			m_Value[size - 1] = m_Value[size - 1] * 2 + binary[j];
		}
	}
}

const Integer Integer::signSwitch() const
{
	Integer result = *this;

	for (auto& digit : result.m_Value)
	{
		digit = ~digit;
	}

	result = result.add(1);
	result.m_Positive = !this->m_Positive;

	return result;
}

const std::string Integer::valueToString() const
{
	if (!m_Positive)
	{
		Integer negative = this->signSwitch();
		return "-" + negative.valueToString();
	}
	
	std::string str = "0";
	std::vector<int> binary;

	for (int i = 0; i < m_Value.size(); i++)
	{
		unsigned int value = m_Value[i];

		for (int j = 0; j < 32; j++)
		{
			binary.push_back(value % 2);
			value /= 2;
		}
	}

	for (int i = binary.size() - 1; i >= 0; i--)
	{
		int carry = binary[i];
		for (int j = str.size() - 1; j >= 0; j--)
		{
			int digit = (str[j] - '0') * 2 + carry;

			carry = digit / 10;
			str[j] = (digit % 10) + '0';
		}

		if (carry == 1)
		{
			str.insert(str.begin(), '1');
		}
	}

	return str;
}

void Integer::print() const
{
	std::cout << valueToString() << std::endl;
}

const Integer Integer::operator+(const Integer& other) const
{
	return add(other);
}

const Integer Integer::operator+() const
{
	return *this;
}

Integer& Integer::operator +=(const Integer& other)
{
	*this = add(other);

	return *this;
}

Integer& Integer::operator =(const Integer& other)
{
	m_Value = other.m_Value;
	m_Positive = other.m_Positive;

	return *this;
}

const Integer Integer::operator-() const
{
	return signSwitch();
}

const Integer Integer::operator-(const Integer& other) const
{
	return add(other.signSwitch());
}
