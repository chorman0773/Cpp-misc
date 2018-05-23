#ifndef __Golden_hpp_2018_05_23_08_17
#define __Golden_hpp_2018_05_23_08_17

#include <ratio>
#include <cstddef>

using one = std::ratio<1,1>;

template<size_t max,typename prev=std::ratio<1,1>> struct golden{
  using value = std::ratio_add<one,std::ratio_divide<one,prev>>;
  using next = golden<max-1,value>;
  constexpr static double φ = value::num/(double)value::denom;
};
template<typename prev> struct golden<0,prev>{
  using value = std::ratio_add<one,std::ratio_divide<one,prev>>;
  constexpr static double φ = value::num/(double)value::denom;
};




#endif
