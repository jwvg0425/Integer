#ifndef _BIG_INT_H_
#define _BIG_INT_H_

#include <vector>
#include <string>

class Integer
{
public:
	Integer();
	~Integer();
	Integer(int n);
	explicit Integer(const std::string& n);
	Integer(const Integer& other);

	const Integer add(const Integer& other) const;
	//부호 변경
	const Integer signSwitch() const;

	const Integer operator -() const;
	const Integer operator +() const;
	const Integer operator -(const Integer& other) const;
	const Integer operator +(const Integer& other) const;
	Integer& operator =(const Integer& other);
	Integer& operator +=(const Integer& other);
	
	void print() const;

private:
	void stringToValue(const std::string& n);
	const std::string valueToString() const;

	std::vector<unsigned int>		m_Value;
	bool							m_Positive;
};
#endif