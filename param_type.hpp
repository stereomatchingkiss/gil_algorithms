#ifndef PARAM_TYPE_HPP
#define PARAM_TYPE_HPP

#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/or.hpp>

/*
 * optimize the value pass into the function
 * this trait come from the chapter 4 of C++ template
 * metaprogramming
 */
template<typename T>
struct param_type
: boost::mpl::eval_if<
    typename boost::mpl::or_<boost::is_scalar<T>, boost::is_reference<T> >,
    typename boost::mpl::identity<T>,
    typename boost::add_reference<T const>
  >
{};


#endif // GIL_TRAITS_HPP
