#ifndef GIL_CORE_UNIT_TEST_HPP
#define GIL_CORE_UNIT_TEST_HPP

#include <functional>
#include <iostream>

#include <boost/gil/algorithm.hpp>
#include <boost/gil/typedefs.hpp>

#include "core.hpp"
#include "gil_show_view.hpp"

/*
 * test the algorithms in core.hpp with 3 views
 *
 * @param :
 * tri_func : functor with 3 arguments which accept three images
 * message  : the message you want to show when the function start
 * value_one : the value fill into the first view
 * value_two : the value fill into the second view
 */
template<typename Image, typename Func>
void gil_core_tri_func(Func tri_func, char const *message, double value_one = 8.0, double value_two = 4.0)
{
    std::cout<<message<<std::endl;

    using namespace boost::gil;

    Image src1(2, 2);
    fill_pixels(view(src1), value_one);

    Image src2(2, 2);
    fill_pixels(view(src2), value_two);

    Image src3(2, 2);

    tri_func(const_view(src1), const_view(src2), view(src3) );
    show_view(const_view(src1));
    show_view(const_view(src2));
    show_view(const_view(src3));
}

/*
 * test the function [adsdiff] of "core.hpp"
 * dst_view = first_view - second_view
 */
template<typename Image>
inline void test_gil_absdiff()
{
    namespace ph = std::placeholders;
    typedef typename Image::view_t view;
    typedef typename Image::const_view_t view_c;
    gil_core_tri_func<Image>(std::bind(absdiff<view_c, view_c, view>, ph::_1, ph::_2, ph::_3),
                             "test absdiff()");
}

/*
 * test the function [add] of "core.hpp"
 * dst_view = first_view + second_view
 */
template<typename Image>
inline void test_gil_add()
{
    namespace ph = std::placeholders;
    typedef typename Image::view_t view;
    typedef typename Image::const_view_t view_c;
    gil_core_tri_func<Image>(std::bind(add<view_c, view_c, view>, ph::_1, ph::_2, ph::_3),
                             "test add()");
}

#endif // GIL_CORE_TEST_HPP
