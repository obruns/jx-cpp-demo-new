#include "demo.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test) {
    Demo<int> d;
    BOOST_CHECK(d.m(1) == true);
    BOOST_CHECK(d.inserted() == false);
}
