#include "gtest/gtest.h"

#include "LibraryFile.h"

class LibTest : public testing::Test {
protected:
    // void SetUp() override {}

    // void TearDown() override {}

    Library lib;
};

TEST_F(LibTest, Test1) {
    lib.set_name("test");
    EXPECT_EQ(lib.get_name() == "TEST", true);
}