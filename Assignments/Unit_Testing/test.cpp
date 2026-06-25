// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
//TEST_F(CollectionTest, AlwaysFail)
//{
//    FAIL();
//}

TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    // if empty, the size must be 0
    //Using Assert here because this test relies on this test not failing.
    ASSERT_EQ(collection->size(), 0);

    add_entries(1);

    // is the collection still empty?
    // if not empty, what must the size be?
    //Using Expect here, since it is the end of the test and no subsequent tests rely on this result.
    EXPECT_EQ(collection->size(), 1);
}

TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    add_entries(5);

    //Use Expect to ensure the collection size is equal to 5
    EXPECT_EQ(collection->size(), 5);
}

TEST_F(CollectionTest, MaxSizeGreater)
{
    //Test that the collection is empty first
    ASSERT_GE(collection->max_size(), collection->size());

    //Add one value and then test again
    add_entries(1);

    //Ensure that only one item is added to collection
    ASSERT_EQ(collection->size(), 1);

    //Test that the max size is greater than or equal to the current size
    ASSERT_GE(collection->max_size(), collection->size());

    //Add more entries to a size of 5 and then test again
    add_entries(4);

    //Ensure that collection has 5 items
    ASSERT_EQ(collection->size(), 5);

    //Test that the max size is greater than or equal to the current size
    ASSERT_GE(collection->max_size(), collection->size());

    //Add more entries to a size of 10 and then test again
    add_entries(5);

    //Ensure that collection has 10 items
    ASSERT_EQ(collection->size(), 10);

    //Test that the max size is greater than or equal to the current size
    EXPECT_GE(collection->max_size(), collection->size());
}

TEST_F(CollectionTest, CheckCapacityEqualToSize)
{
    //Test that the collection is empty first
    ASSERT_GE(collection->capacity(), collection->size());

    //Add one value and then test again
    add_entries(1);

    //Ensure that only one item is added to collection
    ASSERT_EQ(collection->size(), 1);

    //Test that the capacity is greater than or equal to the current size
    ASSERT_GE(collection->capacity(), collection->size());

    //Add more entries to a size of 5 and then test again
    add_entries(4);

    //Ensure that collection has 5 items
    ASSERT_EQ(collection->size(), 5);

    //Test that the capacity is greater than or equal to the current size
    ASSERT_GE(collection->capacity(), collection->size());

    //Add more entries to a size of 10 and then test again
    add_entries(5);

    //Ensure that collection has 10 items
    ASSERT_EQ(collection->size(), 10);

    //Test that the capacity is greater than or equal to the current size
    EXPECT_GE(collection->capacity(), collection->size());
}

TEST_F(CollectionTest, ResizingCollectionUp)
{
    //Ensure the collection is empty first before resizing
    ASSERT_EQ(collection->size(), 0);

    //Resize the collection to a value not affected by other tests.
    collection->resize(20);

    //Test that resizing increases the collection.
    EXPECT_EQ(collection->size(), 20);
}

TEST_F(CollectionTest, ResizingCollectionDown)
{
    //Resize the collection to a value not affected by other tests.
    collection->resize(20);

    //Test that the resizing took place
    ASSERT_EQ(collection->size(), 20);

    //Decrease the collection to a value lower than the current size
    collection->resize(17);

    //Test that resizing decreases the collection.
    EXPECT_EQ(collection->size(), 17);
}

TEST_F(CollectionTest, ResizingCollectionToZero)
{
    //Resize the collection to a value not affected by other tests.
    collection->resize(20);

    //Test that the resizing took place
    ASSERT_EQ(collection->size(), 20);

    //Decrease the collection to zero
    collection->resize(0);

    //Test that resizing decreases the collection.
    EXPECT_EQ(collection->size(), 0);
}

TEST_F(CollectionTest, VerifyClearCollection)
{
    //Resize the collection to a value not affected by other tests.
    collection->resize(20);

    //Test that the resizing took place
    ASSERT_EQ(collection->size(), 20);

    //Clear the collection using built-in function
    collection->clear();

    //Test that the collection is empty two ways
    EXPECT_EQ(collection->size(), 0);
    EXPECT_TRUE(collection->empty());
}

// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, VerifyEraseCollection)
{
    //Resize the collection to a value not affected by other tests.
    collection->resize(20);

    //Test that the resizing took place
    ASSERT_EQ(collection->size(), 20);

    //Begin the erasing procedure
    collection->erase(collection->begin(), collection->end());

    //Ensure that the collection is now empty, two ways
    EXPECT_EQ(collection->size(), 0);
    EXPECT_TRUE(collection->empty());
}

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, VerifyReserveIncrease)
{
    //Add entries to the collection so the collection is not empty
    add_entries(4);

    //Test that the collection size is 4
    ASSERT_EQ(collection->size(), 4);

    //Hold the old size before we verify reserve
    int old_size = collection->size();

    //Hold the old capacity before we verify reserve
    int old_capacity = collection->capacity();

    //Ensure that the old capacity and the old size are greater or equal to each other as they should
    ASSERT_GE(old_capacity, old_size);

    //Begin the reserve process
    collection->reserve(40);

    //Test that the size did not change
    EXPECT_EQ(collection->size(), old_size);

    EXPECT_GE(collection->capacity(), 40);
}

TEST_F(CollectionTest, VerifyOutOfRangeBounds)
{
    //Hold an integer to compare against an out of bounds
    int entriesToAdd = 4;

    //Add entries to collection using the previous int
    add_entries(entriesToAdd);

    //Test that the collection size is 4
    ASSERT_EQ(collection->size(), 4);

    //Test that the out of bounds will throw an exception if we go beyond the vector at()
    EXPECT_THROW((void)collection->at(entriesToAdd + 1), std::out_of_range);
}

TEST_F(CollectionTest, VerifyNegativeAdding)
{
    //Add entries to collection
    add_entries(8);

    //Test that the collection size is 8
    ASSERT_EQ(collection->size(), 8);

    //Test that a negative int adding to collection throws a death message
    EXPECT_DEATH(add_entries(-5), "");
}
TEST_F(CollectionTest, VerifyPopBack)
{
    //Add entries to collection
    add_entries(12);

    //Test that the collection size is 12
    ASSERT_EQ(collection->size(), 12);

    //Remove the last entry so collection size should be 11
    collection->pop_back();

    //Collection should be 11, with the final entry removed
    EXPECT_EQ(collection->size(), 11);
}