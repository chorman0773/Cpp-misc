#ifndef __TypeController_hpp_2018_05_07_13_32
#define __TypeController_hpp_2018_05_07_13_32

#include <type_traits>

using std::true_type;
using std::false_type;


template<bool b,typename T,typename U> struct if_else{};

template<typename T,typename U> struct if_else<true,T,U>{
	typedef T type;
};
template<typename T,typename U> struct if_else<false,T,U>{
	typedef U type;
};

template<typename T> struct if_else<false,T,void>{};

template<typename T> struct if_else<true,void,T>{};

template<bool b,typename T> struct enable_if_not{};

template<typename T> struct enable_if_not<true,T>{};

template<typename T> struct enable_if_not<false,T>{
	typedef T type;
};

/*
	Provides an easy shortcut from any type to a concreate base-type by removing all attachments.
	For any type T:
	base_type<T> defines a single member typedef type, which is the base type of T.
	If T is defined as a pointer to (possibly cv-qualified) void, the the member typedef is defined as void*
	If T is defined as U* (for any type U), then the member typedef is defined as base_type<U>::type
	If T is defined as U& or U&& (for any type U), then the member typedef is defined as base_type<U>::type
	If T is defined as a cv-qualified version of U (for any type U), then the member typedef is defined as base_type<U>::type
	If T is defined as U[] or (for any size_t size) U[size] (for any type U), then the member typedef is defined as base_type<U>::tpye
	Otherwise, the member typedef is defined as T.
	
	Users can overload this struct to add additional functionality.
	In all cases, except for the default overload (and overloads for (possibly cv-qualified) void*),
	the member typedef should use recursion to the member typedef of some base_type template instantiation.
*/
template<typename T> struct base_type{
	typedef T type;
};

template<> struct base_type<void*>{
	typedef void* type;
};

template<> struct base_type<const void*>{
	typedef void* type;
};

template<> struct base_type<volatile void*>{
	typedef void* type;
};

template<> struct base_type<const volatile void*>{
	typedef void* type;
};


template<typename T> struct base_type<const T>{
	typedef base_type<T>::type type;
};

template<typename T> struct base_type<volatile T>{
	typedef base_type<T>::type type;
};

template<typename T> struct base_Type<const volatile T>{
	typedef base_type<T>::type type;
};

template<typename T> struct base_type<T[]>{
	typedef base_type<T>::type type;
};

template<typename T,size_t size> struct base_type<T[size]>{
	typedef base_type<T>::type type;
};

template<typename T> struct base_type<T*>{
	typedef base_type<T>::type type;
};



template<typename T> struct base_type<T&>{
	typedef base_type<T>::type type;
};

template<typename T> struct base_type<T&&>{
	typedef base_type<T>::type type;
};

/*
	Determines if a given type has an attachment.
	Has a single constexpr field value, that for any type T has the same value of !std::is_same<base_type<T>,T>::value
	This class inherits from std::true_type if at least one type attachment (cv-qualification, lvalue reference, rvalue reference,
	pointer, array) exists on T, false otherwise.
*/
template<typename T> struct has_attachment:public false_type{};

template<> struct has_attachment<void*>:public false_type{};

template<typename T> struct has_attachment<T*>:public true_type{};

template<typename T> struct has_attachment<T&>:public true_type{};

template<typename T> struct has_attachment<T&&>:public true_type{};

template<typename T> struct has_attachment<const T>:public true_type{};

template<typename T> struct has_attachment<volatile T>:public true_type{};

template<typename T> struct has_attachement<T[]>:public true_type{};

template<typename T,size_t size> struct has_attachment<T[size]>:public true_type{};

/*
	Counts the number of attachments on a type at any level.
	The type has a single constexpr static field value is 0 if has_attachment<T>::value is false,
	otherwise its some positive number.
	The struct will always inherit from some std::integral_constant<unsigned int,s>
*/
template<typename T> struct count_attachments:public std::integral_constant<unsigned int,0>{};

template<> struct count_attachments<void*>:public std::integral_constant<unsigned int,0>{};

template<> struct count_attachments<const void*>:public std::integral_constant<unsigned int,1>{};

template<> struct count_attachments<volatile void*>:public std::integral_constant<unsigned int,1>{};

template<> struct count_attachments<const volatile void*>:public std::integral_constant<unsigned int,2>{};

template<typename T> struct count_attachments<const T>:
	public std::integral_constant<unsigned int,count_attachments<T>::value+1>{};

template<typename T> struct count_attachments<volatile T>:
	public std::integral_constant<unsigned int,count_attachments<T>::value+1>{};
	
template<typename T> struct count_attachments<const volatile T>:
	public std::integral_constant<unsigned int,count_attachments<T>::value+2>{};
	
template<typename T> struct count_attachments<T*>:
	public std::integral_constant<unsigned int,count_attachments<T>::value+1>{};
	
template<typename T> struct count_attachments<T&>:
	public std::integral_constant<unsigned int,count_attachments<T>::value+1>{};

template<typename T> struct count_attachments<T&&>:
	public std::integral_constant<unsigned int,count_attachments<T>::value+1>{};
	
template<typename T> struct count_attachments<T[]>:
	public std::integral_constant<unsigned int,count_attachments<T>::value+1>{};

template<typename T,size_t size> struct count_attachments<T[size]>:
	public std::integral_constant<unsigned int,count_attachments<T>::value+1>{};
	




#endif
