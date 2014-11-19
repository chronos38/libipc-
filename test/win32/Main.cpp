#include "gtest/gtest.h"
#include "Globals.h"

int main(int argc, char** argv)
{
    std::remove(LOGFILE);
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}
