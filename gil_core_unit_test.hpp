#ifndef GIL_CORE_UNIT_TEST_HPP
#define GIL_CORE_UNIT_TEST_HPP

#include <functional>
#include <iostream>

#include <boost/gil/algorithm.hpp>
#include <boost/gil/typedefs.hpp>

#include "core.hpp"

/*
 * Show the value of the view
 *
 * @param :
 *  view : the view you want to show
 */
template<typename T>
void show_view(T const &view)
{
    for(int i = 0; i != view.height(); ++i)
    {
        auto src_it = view.row_begin(i);
        for(int j = 0; j != view.width(); ++j)
        {           
            for(int c = 0; c != boost::gil::num_channels<T>::value; ++c)
            std::cout<<"channel "<< c << " : ("<<i<<", "<<j<<") = "<<(int)src_it[j][c]<<", ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

/*
 * test the algorithms in core.hpp with 3 view
 *
 * @param :
 * tri_func : functor with 3 arguments which accept three images
 * message  : the message you want to show when the function start
 */
template<typename Image, typename Func>
void gil_core_tri_func(Func tri_func, char const *message)
{
    std::cout<<message<<std::endl;

    using namespace boost::gil;

    Image src1(2, 2);
    fill_pixels(view(src1), 8);

    Image src2(2, 2);
    fill_pixels(view(src2), 4);

    Image src3(2, 2);

    tri_func(const_view(src1), const_view(src2), view(src3) );
    show_view(const_view(src1));
    show_view(const_view(src2));
    show_view(const_view(src3));
}

/*
 * test the function [adsdiff] of "core.hpp"
 */
inline void test_gil_absdiff()
{
    namespace ph = std::placeholders;
    typedef boost::gil::gray8_image_t image;
    typedef image::view_t view;
    typedef image::const_view_t view_c;
    gil_core_tri_func<image>(std::bind(absdiff<view_c, view_c, view>, ph::_1, ph::_2, ph::_3),
                             "test absdiff()");
}

/*
 * test the function [add] of "core.hpp"
 */
inline void test_gil_add()
{
    namespace ph = std::placeholders;
    typedef boost::gil::gray8_image_t image;
    typedef image::view_t view;
    typedef image::const_view_t view_c;
    gil_core_tri_func<image>(std::bind(add<view_c, view_c, view>, ph::_1, ph::_2, ph::_3),
                             "test add()");
}

#endif // GIL_CORE_TEST_HPP
