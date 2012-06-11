#ifndef GIL_RESAMPLE_UNIT_TEST_HPP
#define GIL_RESAMPLE_UNIT_TEST_HPP

#include <cmath>
#include <iostream>

#include <boost/gil/gil_all.hpp>
#include <boost/gil/typedefs.hpp>

#include <boost/gil/extension/numeric/resample.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>

#include <QtGui/QImage>

#include "gil_show_view.hpp"
#include "iview_factory.hpp"
#include "resample.hpp"

template<typename View>
void fill_value(View const &view, float initial_value = 0)
{
    typedef typename boost::gil::channel_type<View>::type channel_type;
    typedef typename boost::gil::channel_traits<channel_type> type;
    typedef typename type::value_type value_type;
    value_type value = value_type(initial_value);
    for(int i = 0; i != view.height(); ++i)
    {
        auto x_it = view.row_begin(i);
        for(int j = 0; j != view.width(); ++j)
        {
            //std::cout<<value<<std::endl;
            for(int k = 0; k != boost::gil::num_channels<View>::value; ++k)
                x_it[j][k] = value;
            ++value;
        }

    }
}

template<typename Image = boost::gil::gray32f_image_t>
inline void test_bilinear_resample(double src_size = 2, double scale = 2)
{
  using namespace boost::gil;

  Image src(src_size, src_size);
  double dst_size = src_size * scale;
  Image dst(dst_size, dst_size);

  fill_value(view(src), 0);
  std::cout<<"original view"<<std::endl;
  show_view(const_view(src));

  //resize_view(const_view(src), view(dst), bilinear_sampler());
  resizeBilinearGray(const_view(src), view(dst));
  std::cout<<"view after interpolation"<<std::endl;
  show_view(const_view(dst));
}

inline void test_bilinear(double scale = 2)
{
  using namespace boost::gil;

  QImage src("../GIL_with_Qt/images_00/lena/lena.jpg");
  QImage dst(src.width() * scale, src.height() * scale, src.format() );
  std::cout<<src.format()<<std::endl;

  typedef boost::gil::bgra8_view_t View;
  auto const src_view = qt::create_qt_iview<View>(src);
  auto const dst_view = qt::create_qt_iview<View>(dst);

  std::cout<<"koko"<<std::endl;
  //resizeBilinear(src_view, dst_view);
  resize_view(src_view, dst_view, bilinear_sampler());
  std::cout<<"keke"<<std::endl;
  dst.save("E:/acg/lena2.bmp");
  std::cout<<"haha"<<std::endl;

}

#endif // GIL_RESAMPLE_UNIT_TEST_HPP
