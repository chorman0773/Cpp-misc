#ifndef __Math_hpp_2018_05_04_22_45
#define __Math_hpp_2018_05_04_22_45

#include <utility>

class Expression;

class _WrappedExpn{
private:
	Expression* expn;
public:
	template<typename T> _WrappedExpn(const T& copy){
		expn = new T(copy);	
	}
	_WrappedExpn(const _WrappedExpn&);
	_WrappedExpn(_WrappedExpn&&);
	template<typename T,typename... Args> _WrappedExpn(Args... args){
		expn = new T(std::forward(args)...);
	}
	~_WrappedExpn();
	_WrappedExpn& operator=(const _WrappedExpn&);
	_WrappedExpn& operator=(_WrappedExpn&);
	_WrappedExpn& operator=(Expression&);
	operator Expression&();
	Expression* operator->();
	_WrappedExpn operator+(Expression&);
	_WrappedExpn operator+(double);
	_WrappedExpn operator-(Expression&);
	_WrappedExpn operator-(double);
	_WrappedExpn operator*(Expression&);
	_WrappedExpn operator*(double);
	_WrappedExpn operator/(Expression&);
	_WrappedExpn operator/(double);
	_WrappedExpn operator^(Expression&);
	_WrappedExpn operator^(double);
};


_WrappedExpn operator+(double,_WrappedExpn&);
_WrappedExpn operator-(double,_WrappedExpn&);
_WrappedExpn operator*(double,_WrappedExpn&);
_WrappedExpn operator/(double,_WrappedExpn&);
_WrappedExpn operator^(double,_WrappedExpn&);

_WrappedExpn operator+(double,_WrappedExpn&&);
_WrappedExpn operator-(double,_WrappedExpn&&);
_WrappedExpn operator*(double,_WrappedExpn&&);
_WrappedExpn operator/(double,_WrappedExpn&&);
_WrappedExpn operator^(double,_WrappedExpn&&);

class Expression{
public:
	virtual double eval(double)=0;
	virtual _WrappedExpn derivativeOf()=0;
	virtual bool isConstant()=0;
	virtual _WrappedExpn callWith(Expression&);
	_WrappedExpn operator+(Expression&);
	_WrappedExpn operator+(double);
	_WrappedExpn operator-(Expression&);
	_WrappedExpn operator-(double);
	_WrappedExpn operator*(Expression&);
	_WrappedExpn operator*(double);
	_WrappedExpn operator/(Expression&);
	_WrappedExpn operator/(double);
	_WrappedExpn operator^(Expression&);
	_WrappedExpn operator^(double);
	_WrappedExpn operator+(_WrappedExpn&);
	_WrappedExpn operator-(_WrappedExpn&);
	_WrappedExpn operator*(_WrappedExpn&);
	_WrappedExpn operator/(_WrappedExpn&);
	_WrappedExpn operator^(_WrappedExpn&);
	_WrappedExpn operator+(_WrappedExpn&&);
	_WrappedExpn operator-(_WrappedExpn&&);
	_WrappedExpn operator*(_WrappedExpn&&);
	_WrappedExpn operator/(_WrappedExpn&&);
	_WrappedExpn operator^(_WrappedExpn&&);
};

_WrappedExpn operator+(double,Expression&);
_WrappedExpn operator-(double,Expression&);
_WrappedExpn operator*(double,Expression&);
_WrappedExpn operator/(double,Expression&);
_WrappedExpn operator^(double,Expression&);

class ConstantExpression final:public Expression{
	double val;
public:
	ConstantExpression(double);
	double eval(double);
	_WrappedExpn derivativeOf();
	bool isConstant();
};

class Variable final:public Expression{
	double val;
public:
	Variable();
	Variable(double);
	Variable& operator=(double);
	_WrappedExpn derivativeOf();
	bool isConstant();
	double eval(double);
};

class Parameter final:public Expression{
public:
	_WrappedExpn derivativeOf();
	bool isConstant();
	double eval(double);
};

class sqrt final:public Expression{
	_WrappedExpn inner;
public:
	sqrt(_WrappedExpn);
	_WrappedExpn derivativeOf();
	bool isConstant();
	double eval(double);
};

template<double d> class log final:public Expression{
	_WrappedExpn inner;
public:
	log(_WrappedExpn);
	_WrappedExpn derivativeOf();
	bool isConstant();
	double eval(double);
}

template<> class log<2.71828182845904523536028747135266249775724709369995>:public Expression{
	_WrappedExpn inner;
public:
	log(_WrappedExpn);
	_WrappedExpn derivativeOf();
	bool isConstant();
	double eval(double);
};


class Function final:public Expression{
	_WrappedExpn expn;
public:
	Function();
	Function& operator=(_WrappedExpn);
	Function& operator()(Variable&);
	_WrappedExpn operator()(Function&);
	double operator()(double);
	_WrappedExpn derivativeOf();
	bool isConstant();
	double eval(double);
};


using ln = log<2.71828182845904523536028747135266249775724709369995>;

ConstantExpression e(2.71828182845904523536028747135266249775724709369995);
ConstantExpression π(3.14159265358979323846264338327950288419716939937510);
_WrappedExpn d(_WrappedExpn);

#endif
