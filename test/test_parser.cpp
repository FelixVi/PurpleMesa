#include "gtest/gtest.h"
#include "vhdl_parser_driver.h"

TEST(ParserTests, simple) {
    vhdl_driver driver;
    ASSERT_EQ(driver.parse ("../testinput/test.input"), 0);
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

