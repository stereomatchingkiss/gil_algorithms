#ifndef CORE_FUNCTOR_HPP
#define CORE_FUNCTOR_HPP

#include <iostream>
#include <functional>
#include <typeinfo>

#include <boost/type_traits.hpp>

#include "core.hpp"
#include "param_type.hpp"

/*
 * functor design for the dynamic version of absdiff
 */
template <typename DstView>
struct absdiff_func : public std::unary_function<DstView, void>
{    
  typedef void result_type;
  absdiff_func(DstView const &dst) : dst_(dst) {}

  template <typename SrcView1, typename SrcView2>
  result_type operator()(SrcView1 const &src1, SrcView2 const &src2) const { absdiff(src1, src2, dst_); }

  private :
    DstView const &dst_;
};

/*
 * calculate the adbsolute different(pixels) of in1 and in2
 */
struct abs_func
{      
    template <typename T>
    T operator()(T const &in1, T const &in2) const {

        return absdiff_pixel(in1, in2);
    }
};

/*
 * Calcuate the summation of two pixels, the result will
 * be return = saturate(in1 + in2).
 */
template<typename T>
class saturation_add : public std::binary_function<double, double, T>
{            
   public :
    saturation_add(double min, double max) : min_(min), max_(max) {}

    T operator()(typename param_type<T>::type in1, typename param_type<T>::type in2) const {

        double temp = (double)(in1 + in2);
        if(temp > max_) temp = max_;
        else if(temp < min_) temp = min_;

        return (T)temp;
    }

  private :
    double min_; //minimum value
    double max_; //maximum value
};

#endif // CORE_FUNCTOR_HPP
