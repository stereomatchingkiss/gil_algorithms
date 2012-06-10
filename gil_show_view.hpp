#ifndef GIL_SHOW_VIEW_HPP
#define GIL_SHOW_VIEW_HPP

#include <boost/gil/typedefs.hpp>

/*
 * Show the value of the view
 *
 * @param :
 *  view : the view you want to show
 */
template<typename View>
void show_view(View const &view)
{
    for(int i = 0; i != view.height(); ++i)
    {
        auto src_it = view.row_begin(i);
        for(int j = 0; j != view.width(); ++j)
        {
            for(int c = 0; c != boost::gil::num_channels<View>::value; ++c)
            std::cout<<"channel "<< c << " : ("<<i<<", "<<j<<") = "<<(int)src_it[j][c]<<", ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

#endif // GIL_SHOW_VIEW_HPP
