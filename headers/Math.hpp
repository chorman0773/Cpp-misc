#ifndef __Math_hpp_2018_05_04_22_45
#define __Math_hpp_2018_05_04_22_45

class Expression;

class _WrappedExpn{
private:
	Expression* expn;
public:
	_WrappedExpn(Expression&);
	_WrappedExpn(const _WrappedExpn&);
	_WrappedExpn(_WrappedExpn&&);
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

class _AddExpn final:public Expression{
	_WrappedExpn first;
	_WrappedExpn second;
public:
	_AddExpn(Expression&,Expression&);
	_WrappedExpn derivativeOf();
	bool isConstant();
	double eval(double);
};

class _SubExpn final:public Expression{
	_WrappedExpn first;
	_WrappedExpn second;
public:
	_SubExpn(Expression&,Expression&);
	_WrappedExpn derivativeOf();
	bool isConstant();
	double eval(double);
};

class _MulExpn final:public Expression{
	_WrappedExpn first;
	_WrappedExpn second;
public:
	_MulExpn(Expression&,Expression&);
	_WrappedExpn derivativeOf();
	bool isConstant();
	double eval(double);
};

class _DivExpn final:public Expression{
	_WrappedExpn first;
	_WrappedExpn second;
public:
	_DivExpn(Expression&,Expression&);
	_WrappedExpn derivativeOf();
	bool isConstant();
	double eval(double);
};

class sqrt final:public Expression{
	_WrappedExpn inner;
public:
	sqrt(Expression&);
	_WrappedExpn derivativeOf();
	bool isConstant();
	double eval(double);
};

template<double d> class log final:public Expression{
	_WrappedExpn inner;
public:
	log(Expression&);
	_WrappedExpn derivativeOf();
	bool isConstant();
	double eval(double);
}

template<> class log<2.71828182845904523536028747135266249775724709369995>{
	_WrappedExpn inner;
public:
	log(Expression&);
	_WrappedExpn derivativeOf();
	bool isConstant();
	double eval(double);
};

class _ExpExpn final:public Expression{
	_WrappedExpn base;
	_WrappedExpn power;
public:
	_ExpExpn(Expression&,Expression&);
	_WrappedExpn derivativeOf();
	bool isConstant();
	double eval(double);
};

class ChainedExpression final:public Expression{
	_WrappedExpn outer;
	_WrappedExpn inner;
public:
	ChainedExpression(Expression&,Expression&);
	_WrappedExpn derivativeOf();
	bool isConstant();
	double eval(double);
};

class Function final:public Expression{
	_WrappedExpn expn;
public:
	Function();
	Function& operator=(Expression&);
	Function& operator()(Variable&);
	Function& operator()(Expression&);
	double operator()(double);
	_WrappedExpn derivativeOf();
	bool isConstant();
	double eval(double);
};


using ln = log<2.71828182845904523536028747135266249775724709369995>;

ConstantExpression e(2.71828182845904523536028747135266249775724709369995);
ConstantExpression π(3.14159265358979323846264338327950288419716939937510);
_WrappedExpn d(Expression&);

#endif
