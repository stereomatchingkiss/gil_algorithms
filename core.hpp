#ifndef GIL_CORE_HPP
#define GIL_CORE_HPP

#include <cmath>
#include <iostream>
#include <type_traits>

#include <boost/gil/algorithm.hpp>
#include <boost/gil/typedefs.hpp>

#include <boost/gil/extension/dynamic_image/any_image_view.hpp>
#include <boost/gil/extension/dynamic_image/apply_operation.hpp>

#include "core_functor.hpp"

/* calculate the absolute different between two views
 * This function would transform the value type(int, char and so on)
 * of sources into the the value type of the destination type.The range
 * of the sources would be scale to the range of destination type too,
 * it would not transform or scaling if the source and destination are
 * the same type.
 *
 * @parame
 * src_1 : first view
 * src_2 : second view
 * dst   : destination view
 *
 * exception : depend on the template parameter
 */
template<typename SrcView1, typename SrcView2, typename DstView>
void absdiff(SrcView1 const &src1, SrcView2 const &src2, DstView const &dst)
{           
    auto scale_src1 = boost::gil::color_converted_view<typename DstView::value_type>(src1);
    auto scale_src2 = boost::gil::color_converted_view<typename DstView::value_type>(src2);
    if(src1.width() == src2.width() && src1.height() == src2.height())
    {
        for (int y = 0; y != src1.height(); ++y) {
            auto src1_it = scale_src1.row_begin(y);
            auto src2_it = scale_src2.row_begin(y);
            auto dst_it = dst.row_begin(y);

            for (int x = 0; x != src1.width(); ++x)
                boost::gil::static_transform(src1_it[x], src2_it[x], dst_it[x], abs_func());
        }
    }
}

/*
 * dynamic version of adsdiff
 */
template<typename SrcView, typename DstView>
inline void absdiff(boost::gil::any_image_view<SrcView> const &src1, boost::gil::any_image_view<SrcView> const &src2, DstView const &dst)
{
    apply_operation(src1, src2, absdiff_func<DstView>(dst) );
}

/* designed for pixel type of gil
 *
 * parameter
 * X : first number
 * Y : second number
 *
 * return value : absolute different between X and Y(|X - Y|)
 *
 * exception : depend on the template parameter
 */
template<typename T>
inline typename boost::gil::channel_type<T>::type absdiff_pixel(T const &x, T const &y)
{    
    return x > y ? x - y : y - x;
}


/* designed for unsigned primitive type
 *
 * parameter
 * X : first number
 * Y : second number
 *
 * return value : absolute different between X and Y(|X - Y|)
 *
 * exception : strong exception guarantee, nothrow guarantee
 */
template<typename T>
inline typename std::enable_if<std::is_unsigned<T>::value, T>::type
absdiff_pixel(T x, T y)
{    
    return x > y ? x - y : y - x;
}

/* designed for signed primitive type
 *
 * parameter
 * X : first number
 * Y : second number
 *
 * return value : absolute different between X and Y(|X - Y|)
 *
 * exception : strong exception guarantee, nothrow guarantee
 */
template<typename T>
inline typename std::enable_if<std::is_signed<T>::value, T>::type
absdiff_pixel(T x, T y)
{    
    return std::abs(x - y);
}

/* add the pixels(saturate) of the sources and copy them to the destination
 * This function would transform the value type(int, char and so on)
 * of sources into the the value type of the destination type.The range
 * of the sources would be scale to the range of destination type too,
 * it would not transform or scaling if the source and destination are
 * the same type.
 *
 * dst[i][c] = saturate(src1[i][c] + src2[i][c]) and so on
 *
 * @parame
 * src_1 : first views
 * src_2 : second views
 * dst   : destination views
 *
 * exception : depend on the template parameter
 */
template<typename SrcView1, typename SrcView2, typename DstView>
void add(SrcView1 const &src1, SrcView2 const &src2, DstView const &dst)
{
    typedef typename boost::gil::channel_type<DstView>::type dst_ch_type;
    typedef typename boost::gil::channel_traits<dst_ch_type> type;
    typedef typename type::value_type value_type;
    typedef typename DstView::value_type dst_pix_type;

    auto scale_src1 = boost::gil::color_converted_view<dst_pix_type>(src1);
    auto scale_src2 = boost::gil::color_converted_view<dst_pix_type>(src2);
    for(int i = 0; i != src1.height(); ++i)
    {       
        //typename SrcView::x_iterator src1_it = src1.row_begin(i);
        //typename SrcView::x_iterator src2_it = src2.row_begin(i);
        //typename Dstview::x_iterator dst_it = dst.row_begin(i);
        auto src1_it = scale_src1.row_begin(i);
        auto src2_it = scale_src2.row_begin(i);
        auto dst_it = dst.row_begin(i);

        for(int j = 0; j != src1.width(); ++j)
            boost::gil::static_transform(src1_it[j], src2_it[j], dst_it[j],
                                         saturation_add<value_type>(type::min_value(), type::max_value()));
    }
}

#endif // GIL_CORE_HPP
