#ifndef RESAMPLE_HPP
#define RESAMPLE_HPP

#include <iostream>

#include <boost/gil/algorithm.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>

//a practice, numeric already implement this algorithm
template<typename SrcView, typename DstView>
void resizeBilinear(SrcView const &src, DstView const &dst)
{
    typedef typename DstView::value_type dst_pix_type;
    auto scale_src = boost::gil::color_converted_view<dst_pix_type>(src);

    typedef float type;
    float x_ratio = ((type)(src.width() - 1)) / dst.width();
    float y_ratio = ((type)(src.height() - 1)) / dst.height();
    auto src_loc = scale_src.xy_at(0, 0);
    for (int i = 0; i != dst.height(); ++i)
    {
        auto dst_it = dst.row_begin(i);
        for (int j = 0; j != dst.width(); ++j)
        {
            int y = (int)(y_ratio * i);
            int x = (int)(x_ratio * j);
            type y_diff = (y_ratio * i) - y;
            type x_diff = (x_ratio * j) - x;

            namespace gil = boost::gil;
            namespace detail = gil::detail;
            gil::pixel<type, gil::devicen_layout_t<gil::num_channels<SrcView>::value> > dst_pix(0);
            gil::static_for_each(src_loc(x, y) , dst_pix, detail::add_dst_mul_src_channel<type>((1 - x_diff) * (1 - y_diff)));
            gil::static_for_each(src_loc(x + 1, y) , dst_pix, detail::add_dst_mul_src_channel<type>((x_diff) * (1 - y_diff)) );
            gil::static_for_each(src_loc(x, y + 1) , dst_pix, detail::add_dst_mul_src_channel<type>((y_diff) * (1 - x_diff)) );
            gil::static_for_each(src_loc(x + 1, y + 1) , dst_pix, detail::add_dst_mul_src_channel<type>(x_diff * y_diff) );

            dst_it[j] = dst_pix;
        }
    }
}

#endif // RESAMPLE_HPP
