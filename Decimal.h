#pragma once
#include <iostream>
class Decimal
{
private:
	int _mantissa;
	int _exponent;
public: 
	Decimal(int exponent)
		:_mantissa(0), _exponent(exponent)
	{
		std::cout << "Decimal::Decimal create " << _mantissa << ":" << _exponent << std::endl;
	}
	
	Decimal(const Decimal& other)
		:_mantissa(other._mantissa), _exponent(other._exponent)
	{
		std::cout << "Decimal::Decimal copy " << _mantissa << ":" << _exponent << std::endl;
	}

	Decimal(Decimal && other)
		:_mantissa(std::move(other._mantissa)), _exponent(std::move(other._exponent))
	{
		std::cout << "Decimal::Decimal move " << _mantissa << ":" << _exponent << std::endl;
	}

	~Decimal()
	{
		std::cout << "Decimal::Decimal destructor " << _mantissa << ":" << _exponent << std::endl;
	}

	void setMantissa(int mantissa)
	{
		_mantissa = mantissa;
	}
};

