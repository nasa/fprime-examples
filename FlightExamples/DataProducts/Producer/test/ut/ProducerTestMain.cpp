// ======================================================================
// \title  ProducerTestMain.cpp
// \author mstarch
// \brief  cpp file for Producer component test main function
// ======================================================================

#include "ProducerTester.hpp"

TEST(Nominal, Generation) {
    DataProducts::ProducerTester tester;
    tester.test_data_product_generation();
}

TEST(OffNominal, AllocationFailure) {
    DataProducts::ProducerTester tester;
    tester.test_data_failed_allocate();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
