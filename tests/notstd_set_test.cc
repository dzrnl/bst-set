#include <lib/notstd/set.h>
#include <gtest/gtest.h>

using namespace notstd;

TEST(NotStdSetTestSuite, EmptyTest) {
    set<int> my_set;

    ASSERT_TRUE(my_set.empty());
}

TEST(NotStdSetTestSuite, NotEmptyTest) {
    set<int> my_set;

    my_set.insert(1);

    ASSERT_FALSE(my_set.empty());
}

TEST(NotStdSetTestSuite, EqualTest) {
    set<int> set1;
    set<int> set2;

    set1.insert(1);
    set1.insert(3);

    set2.insert(1);
    set2.insert(3);

    ASSERT_TRUE(set1 == set2);
}

TEST(NotStdSetTestSuite, NotEqualTest) {
    set<int> set1;
    set<int> set2;

    set1.insert(1);
    set1.insert(3);

    set2.insert(1);
    set2.insert(2);

    ASSERT_TRUE(set1 != set2);
}

TEST(NotStdSetTestSuite, InOrderIncrementIteratorTest) {
    set<int, bst_order::in_order_tag> my_set = {50, 30, 70, 23, 35, 80, 11, 25, 31, 42, 73, 85};

    std::stringstream ss;
    for (set<int, bst_order::in_order_tag>::iterator iter = my_set.begin(); iter != my_set.end(); ++iter) {
        ss << *iter << ' ';
    }

    ASSERT_EQ("11 23 25 30 31 35 42 50 70 73 80 85 ", ss.str());
}

TEST(NotStdSetTestSuite, InOrderDecrementIteratorTest) {
    set<int, bst_order::in_order_tag> my_set = {50, 30, 70, 23, 35, 80, 11, 25, 31, 42, 73, 85};

    std::stringstream ss;
    for (set<int, bst_order::in_order_tag>::iterator iter = my_set.end(); iter != my_set.begin();) {
        --iter;
        ss << *iter << ' ';
    }

    ASSERT_EQ("85 80 73 70 50 42 35 31 30 25 23 11 ", ss.str());
}

TEST(NotStdSetTestSuite, InOrderReverseIteratorTest) {
    set<int, bst_order::in_order_tag> my_set = {50, 30, 70, 23, 35, 80, 11, 25, 31, 42, 73, 85};

    std::stringstream ss;
    for (set<int, bst_order::in_order_tag>::reverse_iterator iter = my_set.rbegin(); iter != my_set.rend(); ++iter) {
        ss << *iter << ' ';
    }

    ASSERT_EQ("85 80 73 70 50 42 35 31 30 25 23 11 ", ss.str());
}

TEST(NotStdSetTestSuite, PreOrderIncrementIteratorTest) {
    set<int, bst_order::pre_order_tag> my_set = {50, 30, 70, 23, 35, 80, 11, 25, 31, 42, 73, 85};

    std::stringstream ss;
    for (set<int, bst_order::pre_order_tag>::iterator iter = my_set.begin(); iter != my_set.end(); ++iter) {
        ss << *iter << ' ';
    }

    ASSERT_EQ("50 30 23 11 25 35 31 42 70 80 73 85 ", ss.str());
}

TEST(NotStdSetTestSuite, PreOrderDecrementIteratorTest) {
    set<int, bst_order::pre_order_tag> my_set = {50, 30, 70, 23, 35, 80, 11, 25, 31, 42, 73, 85};

    std::stringstream ss;
    for (set<int, bst_order::pre_order_tag>::iterator iter = my_set.end(); iter != my_set.begin();) {
        --iter;
        ss << *iter << ' ';
    }

    ASSERT_EQ("85 73 80 70 42 31 35 25 11 23 30 50 ", ss.str());
}

TEST(NotStdSetTestSuite, PreOrderReverseIteratorTest) {
    set<int, bst_order::pre_order_tag> my_set = {50, 30, 70, 23, 35, 80, 11, 25, 31, 42, 73, 85};

    std::stringstream ss;
    for (set<int, bst_order::pre_order_tag>::reverse_iterator iter = my_set.rbegin(); iter != my_set.rend(); ++iter) {
        ss << *iter << ' ';
    }

    ASSERT_EQ("85 73 80 70 42 31 35 25 11 23 30 50 ", ss.str());
}

TEST(NotStdSetTestSuite, PostOrderIncrementIteratorTest) {
    set<int, bst_order::post_order_tag> my_set = {50, 30, 70, 23, 35, 80, 11, 25, 31, 42, 73, 85};

    std::stringstream ss;
    for (set<int, bst_order::post_order_tag>::iterator iter = my_set.begin(); iter != my_set.end(); ++iter) {
        ss << *iter << ' ';
    }

    ASSERT_EQ("11 25 23 31 42 35 30 73 85 80 70 50 ", ss.str());
}

TEST(NotStdSetTestSuite, PostOrderDecrementIteratorTest) {
    set<int, bst_order::post_order_tag> my_set = {50, 30, 70, 23, 35, 80, 11, 25, 31, 42, 73, 85};

    std::stringstream ss;
    for (set<int, bst_order::post_order_tag>::iterator iter = my_set.end(); iter != my_set.begin();) {
        --iter;
        ss << *iter << ' ';
    }

    ASSERT_EQ("50 70 80 85 73 30 35 42 31 23 25 11 ", ss.str());
}

TEST(NotStdSetTestSuite, PostOrderReverseIteratorTest) {
    set<int, bst_order::post_order_tag> my_set = {50, 30, 70, 23, 35, 80, 11, 25, 31, 42, 73, 85};

    std::stringstream ss;
    for (set<int, bst_order::post_order_tag>::reverse_iterator iter = my_set.rbegin(); iter != my_set.rend(); ++iter) {
        ss << *iter << ' ';
    }

    ASSERT_EQ("50 70 80 85 73 30 35 42 31 23 25 11 ", ss.str());
}

TEST(NotStdSetTestSuite, CopyConstructorTest) {
    set<int> set1 = {1, 4, 5, 9};

    set<int> set2(set1);

    ASSERT_TRUE(set1 == set2);
}

TEST(NotStdSetTestSuite, CopyAssignmentOperatorTest) {
    set<int> set1 = {1, 4, 5, 9};

    set<int> set2 = {1, 2, 8};

    set2 = set1;

    ASSERT_TRUE(set1 == set2);
}

TEST(NotStdSetTestSuite, EqualIteratorTest) {
    set<int, bst_order::in_order_tag> my_set = {1, 3, 6, 9, 10, 11, 14, 15};

    set<int, bst_order::in_order_tag>::iterator iter1 = my_set.begin();
    ++iter1;

    set<int, bst_order::in_order_tag>::iterator iter2 = my_set.begin();
    ++iter2;
    ++iter2;
    --iter2;

    ASSERT_TRUE(iter1 == iter2);

    ASSERT_TRUE(--(++iter1) == iter1);
}

TEST(NotStdSetTestSuite, NotEqualIteratorTest) {
    set<int, bst_order::in_order_tag> my_set = {1, 3, 6, 9, 10, 11, 14, 15};

    set<int, bst_order::in_order_tag>::iterator iter1 = my_set.begin();
    ++iter1;

    set<int, bst_order::in_order_tag>::iterator iter2 = my_set.begin();
    ++iter2;
    ++iter2;

    ASSERT_TRUE(iter1 != iter2);
}

TEST(NotStdSetTestSuite, IteratorReferenceTest) {
    set<int, bst_order::in_order_tag> my_set = {1, 3, 6, 9, 10, 11, 14, 15};

    set<int, bst_order::in_order_tag>::iterator iter = my_set.begin();

    ASSERT_TRUE(*iter == 1);

    ++iter;

    ASSERT_TRUE(*iter == 3);

    ++iter;
    ++iter;

    ASSERT_TRUE(*iter == 9);

    --iter;

    ASSERT_TRUE(*iter == 6);
}

TEST(NotStdSetTestSuite, EmptySetIteratorTest) {
    set<int, bst_order::in_order_tag> my_set;

    ASSERT_TRUE(my_set.begin() == my_set.end());
}

TEST(NotStdSetTestSuite, SizeTest) {
    set<int, bst_order::in_order_tag> my_set = {1, 3, 6, 9, 10, 11, 14, 15};

    ASSERT_TRUE(my_set.size() == 8);

    my_set.insert(2);

    ASSERT_TRUE(my_set.size() == 9);
}

TEST(NotStdSetTestSuite, InsertBoolTest) {
    set<int> my_set = {1, 3, 6, 9, 10, 11, 14, 15};

    std::pair<set<int>::iterator, bool> result = my_set.insert(8);

    ASSERT_TRUE(result.second);

    result = my_set.insert(3);

    ASSERT_FALSE(result.second);
}

TEST(NotStdSetTestSuite, RangeInsertTest) {
    set<int> set1 = {1, 3, 6, 9, 10, 11, 14, 15};
    set<int> set2(set1.begin(), set1.end());

    ASSERT_TRUE(set1 == set2);
}

TEST(NotStdSetTestSuite, InitListInsertTest) {
    set<int> set1 = {1, 3, 6, 9, 10, 11, 14, 15};
    set<int> set2({1, 3, 6, 9, 10, 11, 14, 15});

    ASSERT_TRUE(set1 == set2);
}

TEST(NotStdSetTestSuite, FindTest) {
    set<int> my_set = {1, 3, 6, 9, 10, 11, 14, 15};

    ASSERT_TRUE(my_set.find(1) == my_set.begin());

    ASSERT_TRUE(my_set.find(8) == my_set.end());

    set<int>::iterator iter = my_set.begin();

    ++iter;
    ++iter;

    ASSERT_TRUE(my_set.find(6) == iter);
}

TEST(NotStdSetTestSuite, EraseTest) {
    set<int> my_set = {1, 3, 6, 9, 10, 11, 14, 15};

    size_t size = my_set.size();

    my_set.erase(3);

    ASSERT_TRUE(my_set.size() == size - 1);

    ASSERT_TRUE(my_set.find(3) == my_set.end());

    size = my_set.size();

    my_set.erase(2);

    ASSERT_TRUE(my_set.size() == size);
}

TEST(NotStdSetTestSuite, EraseBoolTest) {
    set<int> my_set = {1, 3, 6, 9, 10, 11, 14, 15};

    size_t size = my_set.size();

    size_t count = my_set.erase(3);

    ASSERT_TRUE(my_set.size() == size - 1);

    ASSERT_TRUE(my_set.find(3) == my_set.end());

    ASSERT_TRUE(count == 1);

    size = my_set.size();

    count = my_set.erase(2);

    ASSERT_TRUE(my_set.size() == size);

    ASSERT_TRUE(count == 0);
}

TEST(NotStdSetTestSuite, EraseIteratorTest) {
    set<int> my_set = {1, 3, 6, 9, 10, 11, 14, 15};

    size_t size = my_set.size();

    set<int>::iterator iter = my_set.erase(my_set.find(3));

    ASSERT_TRUE(my_set.size() == size - 1);

    ASSERT_TRUE(my_set.find(3) == my_set.end());

    ASSERT_TRUE(*iter == 6);

    ASSERT_TRUE(iter == my_set.find(6));

    size = my_set.size();

    iter = my_set.erase(my_set.find(2));

    ASSERT_TRUE(my_set.size() == size);

    ASSERT_TRUE(iter == my_set.end());

    size = my_set.size();

    iter = my_set.erase(my_set.find(15));

    ASSERT_TRUE(my_set.size() == size - 1);

    ASSERT_TRUE(iter == my_set.end());
}

TEST(NotStdSetTestSuite, EraseRangeTest) {
    set<int> my_set = {1, 3, 6, 9, 10, 11, 14, 15};

    size_t size = my_set.size();

    set<int>::iterator iter = my_set.erase(my_set.find(3), my_set.find(10));

    ASSERT_TRUE(my_set.size() == size - 3);

    ASSERT_TRUE(my_set.find(3) == my_set.end());
    ASSERT_TRUE(my_set.find(6) == my_set.end());
    ASSERT_TRUE(my_set.find(9) == my_set.end());

    ASSERT_TRUE(*iter == 10);

    ASSERT_TRUE(iter == my_set.find(10));

    size = my_set.size();

    iter = my_set.erase(my_set.find(20), my_set.find(25));

    ASSERT_TRUE(my_set.size() == size);

    ASSERT_TRUE(iter == my_set.end());

    size = my_set.size();

    iter = my_set.erase(my_set.find(15), my_set.find(20));

    ASSERT_TRUE(my_set.size() == size - 1);

    ASSERT_TRUE(my_set.find(15) == my_set.end());

    ASSERT_TRUE(iter == my_set.end());
}

TEST(NotStdSetTestSuite, ExtractValueTest) {
    set<int> my_set = {1, 3, 6, 9, 10, 11, 14, 15};

    bst_node<int> node = my_set.extract(6);

    ASSERT_TRUE(my_set.find(6) == my_set.end());

    ASSERT_TRUE(node.key == 6);

    node = my_set.extract(20);

    ASSERT_EQ(node.key, 0);
}

TEST(NotStdSetTestSuite, ExtractIteratorTest) {
    set<int> my_set = {1, 3, 6, 9, 10, 11, 14, 15};

    set<int>::iterator iter = my_set.find(6);

    bst_node<int> node = my_set.extract(iter);

    ASSERT_TRUE(my_set.find(6) == my_set.end());

    ASSERT_TRUE(node.key == 6);

    iter = my_set.find(20);

    node = my_set.extract(iter);

    ASSERT_EQ(node.key, 0);
}

TEST(NotStdSetTestSuite, ClearTest) {
    set<int> my_set = {1, 3, 6, 9, 10, 11, 14, 15};

    my_set.clear();

    ASSERT_TRUE(my_set.empty());
}

TEST(NotStdSetTestSuite, CountTest) {
    set<int> my_set = {1, 3, 6, 9, 10, 11, 14, 15};

    ASSERT_TRUE(my_set.count(6) == 1);

    ASSERT_TRUE(my_set.count(2) == 0);
}

TEST(NotStdSetTestSuite, ContainsTest) {
    set<int> my_set = {1, 3, 6, 9, 10, 11, 14, 15};

    ASSERT_TRUE(my_set.contains(6));

    ASSERT_FALSE(my_set.contains(2));
}

TEST(NotStdSetTestSuite, LowerBoundTest) {
    set<int> my_set = {1, 3, 6, 9, 10, 11, 14, 15};

    ASSERT_TRUE(*my_set.lower_bound(3) == 3);

    ASSERT_TRUE(*my_set.lower_bound(5) == 3);

    ASSERT_TRUE(*my_set.lower_bound(1) == 1);

    ASSERT_TRUE(*my_set.lower_bound(15) == 15);

    ASSERT_TRUE(my_set.lower_bound(0) == my_set.end());

    ASSERT_TRUE(*my_set.lower_bound(13) == 11);
}

TEST(NotStdSetTestSuite, UpperBoundTest) {
    set<int> my_set = {1, 3, 6, 9, 10, 11, 14, 15};

    ASSERT_TRUE(*my_set.upper_bound(3) == 3);

    ASSERT_TRUE(*my_set.upper_bound(5) == 6);

    ASSERT_TRUE(*my_set.upper_bound(1) == 1);

    ASSERT_TRUE(*my_set.upper_bound(15) == 15);

    ASSERT_TRUE(*my_set.upper_bound(0) == 1);

    ASSERT_TRUE(*my_set.upper_bound(13) == 14);

    ASSERT_TRUE(my_set.upper_bound(16) == my_set.end());
}

TEST(NotStdSetTestSuite, MergeTest) {
    set<int> my_set = {1, 3, 6, 9, 10, 11, 14, 15};

    set<int> set2 = {1, 3, 4, 5, 6, 10};

    size_t size = my_set.size();

    my_set.merge(set2);

    ASSERT_TRUE(my_set.size() - size == 2);

    ASSERT_TRUE(my_set.contains(4));
}
