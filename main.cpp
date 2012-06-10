#include "gil_core_unit_test.hpp"
//#include "gil_resample_unit_test.hpp"

int main(int argc, char *argv[])
{        
    test_gil_absdiff<boost::gil::gray8_image_t>();
    test_gil_add<boost::gil::gray8_image_t>();
    //test_bilinear();
    //test_bilinear_resample();

    return 0;
}
