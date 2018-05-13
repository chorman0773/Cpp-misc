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
