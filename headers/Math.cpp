#include "Math.hpp"


class _AddExpn final:public Expression{
	_WrappedExpn first;
	_WrappedExpn second;
public:
	_AddExpn(_WrappedExpn l,_WrappedExpn r):first(l),second(r){}
  
	_WrappedExpn derivativeOf(){
    return d(first)+d(second);
  }
	bool isConstant(){
   return first->isConstant()&&second->isConstant(); 
  }
	double eval(double val){
    return first->eval(val)+second->eval(val);
  }
};

class _SubExpn final:public Expression{
	_WrappedExpn first;
	_WrappedExpn second;
public:
	_SubExpn(_WrappedExpn l,_WrappedExpn r):first(l),second(r){}
	_WrappedExpn derivativeOf(){
   return d(first)-d(second); 
  }
	bool isConstant(){
   return first->isConstant()&&second->isConstant(); 
  }
	double eval(double val){
   return first->eval(val)-second->eval(val); 
  }
};

class _MulExpn final:public Expression{
	_WrappedExpn first;
	_WrappedExpn second;
public:
	_MulExpn(_WrappedExpn l,_WrappedExpn r):first(l),second(r){}
	_WrappedExpn derivativeOf(){
   return second*d(first)+first*d(second); 
  }
	bool isConstant(){
   return first->isConstant()&&second->isConstant(); 
  }
	double eval(double val){
    return first->eval(val)*second->eval(val);
  }
};

class _DivExpn final:public Expression{
	_WrappedExpn first;
	_WrappedExpn second;
public:
	_DivExpn(_WrappedExpn l,_WrappedExpn r):first(l),second(r){}
	_WrappedExpn derivativeOf(){
   return (second*d(first)-first*d(second))/(second^2); 
  }
	bool isConstant(){
    return first->isConstant()&&second->isConstant(); 
  }
	double eval(double val){
   return first->eval(val)/second->eval(val); 
  }
};


class _ExpExpn final:public Expression{
	_WrappedExpn base;
	_WrappedExpn power;
public:
	_ExpExpn(_WrappedExpn l,_WrappedExpn r):base(l),power(r){}
	_WrappedExpn derivativeOf(){
		return (base^power)*(power/base+ln(base));	
	}
	bool isConstant(){
		return base->isConstant()&&power->isConstant();	
	}
	double eval(double val){
		return pow(base->eval(val),power->eval(val));
	}
};

class ChainedExpression final:public Expression{
	_WrappedExpn outer;
	_WrappedExpn inner;
public:
	ChainedExpression(_WrappedExpn l,_WrappedExpn r):outer(l),inner(r){}
	_WrappedExpn derivativeOf(){
		return d(outer)->callWith(inner)*d(inner);
	}
	bool isConstant(){
		return outer->isConstant();	
	}
	double eval(double val){
		return outer->eval(inner->eval(val));	
	}
};
