
#include"split.hpp"
#include <assert.h>

void test_copy_constructor_empty_sequence() {
    Sequence<int, std::string> original;
    Sequence<int, std::string> copy(original);

    assert(copy.size() == 0);
    assert(copy.is_empty() == true);
}

void test_copy_constructor_multiple_elements() {
    Sequence<int, std::string> original;
    original.push_back(1, "one");
    original.push_back(2, "two");
    original.push_back(3, "three");

    Sequence<int, std::string> copy(original);

    assert(copy.size() == 3);
    std::string info;
    assert(copy.getInfo(info, 1) && info == "one");
    assert(copy.getInfo(info, 2) && info == "two");
    assert(copy.getInfo(info, 3) && info == "three");
}

void test_copy_constructor_modify_original() {
    Sequence<int, std::string> original;
    original.push_back(1, "one");
    Sequence<int, std::string> copy(original);

    original.push_back(2, "two");

    assert(copy.size() == 1);
    std::string info;
    assert(copy.getInfo(info, 1) && info == "one");
    assert(!copy.getInfo(info, 2));
}

void test_copy_construcor() {
    test_copy_constructor_empty_sequence();
    test_copy_constructor_multiple_elements();
    test_copy_constructor_modify_original();
}

void test_add_node_after_existing_node() {
    Sequence<int, std::string> sequence;
    sequence.push_back(1, "one");
    sequence.push_back(3, "three");

    bool added = sequence.add_node_after(2, "two", 1, 1);

    assert(added);
    assert(sequence.size() == 3);

    std::string info;
    sequence.getInfo(info, 2, 1);
    assert(info == "two");
}

void test_add_node_after_non_existent_node() {
    Sequence<int, std::string> sequence;
    sequence.push_back(1, "one");
    sequence.push_back(3, "three");

    bool added = sequence.add_node_after(2, "two", 4, 1);

    assert(!added);
    assert(sequence.size() == 2);
}

void test_add_node_after_multiple_occurrences() {
    Sequence<int, std::string> sequence;
    sequence.push_back(1, "one");
    sequence.push_back(1, "one again");
    sequence.push_back(3, "three");

    bool added = sequence.add_node_after(2, "two", 1, 2);

    assert(added);
    assert(sequence.size() == 4);

    std::string info;
    sequence.getInfo(info, 2, 1); // Get info of 'two'
    assert(info == "two");
}

void test_add_node(){
    test_add_node_after_existing_node();
    test_add_node_after_non_existent_node();
    test_add_node_after_multiple_occurrences();
}

void test_assignment_operator_empty_sequence() {
    Sequence<int, std::string> original;
    Sequence<int, std::string> copy;
    copy = original;

    assert(copy.size() == 0);
    assert(copy.is_empty() == true);
}

void test_assignment_operator_multiple_elements() {
    Sequence<int, std::string> original;
    original.push_back(1, "one");
    original.push_back(2, "two");
    original.push_back(3, "three");

    Sequence<int, std::string> copy;
    copy = original;

    assert(copy.size() == 3);
    std::string info;
    assert(copy.getInfo(info, 1) && info == "one");
    assert(copy.getInfo(info, 2) && info == "two");
    assert(copy.getInfo(info, 3) && info == "three");
}

void test_assignment_operator_self_assignment() {
    Sequence<int, std::string> sequence;
    sequence.push_back(1, "one");
    sequence.push_back(2, "two");

    sequence = sequence;

    assert(sequence.size() == 2);
    std::string info;
    assert(sequence.getInfo(info, 1) && info == "one");
    assert(sequence.getInfo(info, 2) && info == "two");
}

void test_assignment_operator(){
    test_assignment_operator_empty_sequence();
    test_assignment_operator_multiple_elements();
    test_assignment_operator_self_assignment();
}

void test_size_empty_sequence() {
    Sequence<int, std::string> sequence;

    assert(sequence.size() == 0);
}

void test_size_after_adding_elements() {
    Sequence<int, std::string> sequence;
    sequence.push_back(1, "one");
    sequence.push_back(2, "two");

    assert(sequence.size() == 2);
}

void test_size_after_removing_elements() {
    Sequence<int, std::string> sequence;
    sequence.push_back(1, "one");
    sequence.push_back(2, "two");
    sequence.push_back(3, "three");

    sequence.pop_back();

    assert(sequence.size() == 2);
}

void test_size(){
    test_size_empty_sequence();
    test_size_after_adding_elements();
    test_size_after_removing_elements();
}

void test_clear_empty_sequence() {
    Sequence<int, std::string> sequence;
    sequence.clear();
    assert(sequence.size() == 0);
    assert(sequence.is_empty());
}

void test_clear_non_empty_sequence() {
    Sequence<int, std::string> sequence;
    sequence.push_back(1, "one");
    sequence.push_back(2, "two");
    sequence.clear();
    assert(sequence.size() == 0);
    assert(sequence.is_empty());
}

void test_clear_and_add() {
    Sequence<int, std::string> sequence;
    sequence.push_back(1, "one");
    sequence.clear();
    sequence.push_back(2, "two");
    assert(sequence.size() == 1);
    std::string info;
    assert(sequence.getInfo(info, 2));
}

void test_clear(){
    test_clear_and_add();
    test_clear_empty_sequence();
    test_clear_non_empty_sequence();
}

void test_is_empty_on_empty_sequence() {
    Sequence<int, std::string> sequence;
    assert(sequence.is_empty());
}

void test_is_empty_on_non_empty_sequence() {
    Sequence<int, std::string> sequence;
    sequence.push_back(1, "one");
    assert(!sequence.is_empty());
}

void test_is_empty_after_clear() {
    Sequence<int, std::string> sequence;
    sequence.push_back(1, "one");
    sequence.clear();
    assert(sequence.is_empty());
}

void test_is_empty(){
    test_is_empty_after_clear();
    test_is_empty_on_empty_sequence();
    test_is_empty_on_non_empty_sequence();
}

void test_occurrences() {
    // Test 1: Occurrences in an Empty Sequence
    Sequence<int, std::string> sequence1;
    assert(sequence1.occurrences(1) == 0);

    // Test 2: Occurrences of a Non-Existent Key
    Sequence<int, std::string> sequence2;
    sequence2.push_back(1, "one");
    sequence2.push_back(2, "two");
    assert(sequence2.occurrences(3) == 0);

    // Test 3: Occurrences of an Existing Key
    Sequence<int, std::string> sequence3;
    sequence3.push_back(1, "one");
    sequence3.push_back(1, "another one");
    sequence3.push_back(2, "two");
    assert(sequence3.occurrences(1) == 2);
}

void test_pop_front_and_back() {
    Sequence<int, std::string> sequence;

    // Try empty sequence
    assert(!sequence.pop_front());
    assert(!sequence.pop_back());

    // Add elements to the sequence
    sequence.push_back(1, "one");
    sequence.push_back(2, "two");
    sequence.push_back(3, "three");

    // Pop front
    assert(sequence.pop_front()); // Should remove 'one'
    std::string info;
    // After popping 'one', the next element is 'two' with key 2
    assert(sequence.getInfo(info, 2) && info == "two");

    // Pop back
    assert(sequence.pop_back()); // Should pop 'three'
    assert(sequence.size() == 1); // One element will be left
    // Now only 'two' with key 2 is left in the sequence
    assert(sequence.getInfo(info, 2) && info == "two");

    // Clear and test on empty again
    sequence.clear();
    assert(!sequence.pop_front());
    assert(!sequence.pop_back());
}


void test_push_front_and_back() {
    Sequence<int, std::string> sequence;

    // Push back
    sequence.push_back(1, "one");
    sequence.push_back(3, "three");
    assert(sequence.size() == 2);

    // Push front
    sequence.push_front(0, "zero");
    assert(sequence.size() == 3);

    // Verify order and elements
    std::string info;
    assert(sequence.getInfo(info, 0) && info == "zero");
    assert(sequence.getInfo(info, 1) && info == "one");
    assert(sequence.getInfo(info, 3) && info == "three");

    // Push back another element
    sequence.push_back(4, "four");
    assert(sequence.size() == 4);
    assert(sequence.getInfo(info, 4) && info == "four");

    // Push front another element
    sequence.push_front(-1, "minus one");
    assert(sequence.size() == 5);
    assert(sequence.getInfo(info, -1) && info == "minus one");
}

void test_remove_and_remove_all() {
    Sequence<int, std::string> sequence;

    sequence.push_back(1, "one");
    sequence.push_back(2, "two");
    sequence.push_back(1, "another one");
    sequence.push_back(3, "three");

    // Remove specific occurrence
    assert(sequence.remove(1, 1));
    assert(sequence.size() == 3);

    std::string info;
    assert(sequence.getInfo(info, 1) && info == "one");
    assert(!sequence.getInfo(info, 1, 2));

    // Remove all of a specific key
    assert(sequence.remove_all(1)); // Remove all 'one's
    assert(sequence.size() == 2);
    assert(!sequence.getInfo(info, 1)); // No 'one' should exist now

    // Remove non-existent element
    assert(!sequence.remove(4, 1)); // '4' doesnt exist

    // Remove all of a non-existent key
    assert(!sequence.remove_all(4)); // '4' doesnt exist
}

void test_insert_after() {
    Sequence<int, std::string> sequence;

    sequence.push_back(1, "one");
    sequence.push_back(2, "two");
    sequence.push_back(3, "three");

    // Test insertion after a specific key and occurrence
    sequence.insert_after(4, "four", 2, 1); // Insert 'four' after first occurrence of '2'
    assert(sequence.size() == 4); // Check size

    std::string info;
    assert(sequence.getInfo(info, 4) && info == "four"); // Check if 'four' is correctly inserted

    // Test insertion after a non-existent key
    sequence.insert_after(5, "five", 6, 1); // Insert 'five' after non-existent key '6'
    assert(sequence.size() == 4); // Size should remain unchanged

}


void test_equality_and_inequality_operators() {
    Sequence<int, std::string> sequence1;
    sequence1.push_back(1, "one");
    sequence1.push_back(2, "two");

    Sequence<int, std::string> sequence2;
    sequence2.push_back(1, "one");
    sequence2.push_back(2, "two");

    Sequence<int, std::string> sequence3;
    sequence3.push_back(3, "three");

    // Test equality
    assert(sequence1 == sequence2); // same elements
    assert(!(sequence1 == sequence3)); // Different elements

    // Test inequality
    assert(sequence1 != sequence3); // different elements
    assert(!(sequence1 != sequence2)); // same elements

    // Modify one sequence and test again
    sequence2.push_back(3, "three");
    assert(sequence1 != sequence2); // different elements
}

void test_find_node() {
    // Test with an empty sequence
    Sequence<int, std::string> sequence;
    assert(!sequence.find_node(1, 1)); // Should return false for an empty sequence.

    sequence.push_back(1, "one");
    sequence.push_back(1, "one");
    sequence.push_back(2, "two");
    sequence.push_back(3, "three");
    sequence.push_back(2, "two");

    assert(sequence.find_node(1, 1)); // Should return true for the first occurrence of key 1.
    bool a = sequence.find_node(1, 2); // Should return true for the second occurrence of key 1.
    assert(sequence.find_node(2, 1)); // Should return true for the first occurrence of key 2.
    assert(sequence.find_node(2, 2)); // Should return true for the second occurrence of key 2.
    assert(!sequence.find_node(2, 3)); // Should return false because there is no third occurrence of key 2.
    assert(!sequence.find_node(4, 1)); // Should return false because key 4 does not exist in the sequence.
}


void test_getInfo() {
    Sequence<int, std::string> sequence;

    // Initial setup
    sequence.push_back(1, "one");
    sequence.push_back(2, "two");
    sequence.push_back(3, "three");

    std::string info;

    // Just get info of some random node
    bool found = sequence.getInfo(info, 2);
    assert(found && info == "two");

    // Test non-existing element
    found = sequence.getInfo(info, 4);
    assert(!found);

    // Test after modifying the sequence
    sequence.pop_back(); // Remove 'three'
    found = sequence.getInfo(info, 3);
    assert(!found); // Should no longer find 'three'

    sequence.pop_front(); // Remove 'one'
    found = sequence.getInfo(info, 1);
    assert(!found); // Should no longer find 'one'
}


void test_split_key() {
    //Basic Functionality
    {
        Sequence<int, std::string> seq, seq1, seq2;
        for (int i = 0; i < 10; ++i) {
            seq.push_back(i, std::to_string(i));
        }

        split_key(seq, 5, 1, 2, 3, 1, seq1, seq2);

        assert(seq.size() == 5);
        assert(seq1.size() == 2);
        assert(seq2.size() == 3);

        std::string info;
        assert(!seq.getInfo(info, 5, 1)); // "5" should not exist in seq anymore
        assert(seq1.getInfo(info, 5, 1) && info == "5");
        assert(seq2.getInfo(info, 7, 1) && info == "7");
    }

    // Handling Multiple Counts
    {
        Sequence<int, std::string> seq, seq1, seq2;
        for (int i = 0; i < 10; ++i) {
            seq.push_back(i, std::to_string(i));
        }

        split_key(seq, 3, 1, 1, 1, 3, seq1, seq2);

        assert(seq.size() == 4);
        assert(seq1.size() == 3);
        assert(seq2.size() == 3);
    }

    //Key Not Found
    {
        Sequence<int, std::string> seq, seq1, seq2;
        for (int i = 0; i < 5; ++i) {
            seq.push_back(i, std::to_string(i));
        }

        split_key(seq, 10, 1, 2, 2, 1, seq1, seq2);

        assert(seq.size() == 5); // Original sequence should remain unchanged
        assert(seq1.size() == 0);
        assert(seq2.size() == 0);
    }

}




void task_one_tests(){
    test_copy_construcor();
    test_add_node();
    test_assignment_operator();
    test_size();
    test_clear();
    test_is_empty();
    test_occurrences();
    test_pop_front_and_back();
    test_push_front_and_back();
    test_remove_and_remove_all();
    test_insert_after();
    test_equality_and_inequality_operators();
    test_find_node();
    test_getInfo();
    std::cout<<"Task 1 tests passed\n";


}

void test_split_pos() {
    Sequence<int, std::string> seq, seq1, seq2;
    for (int i = 0; i < 5; ++i) {
        seq.push_back(i, std::to_string(i));
    }

    // Split from the beginning
    split_pos(seq, 0, 2, 2, 1, seq1, seq2);
    // Expecting seq1: {0, 1}, seq2: {2, 3}, seq: {4}
    assert(seq.size() == 1);
    assert(seq1.size() == 2);
    assert(seq2.size() == 2);

    seq.clear();
    seq1.clear();
    seq2.clear();

    // Split with lengths larger than sequence
    for (int i = 0; i < 3; ++i) {
        seq.push_back(i, std::to_string(i));
    }
    split_pos(seq, 1, 5, 5, 1, seq1, seq2);
    // Expecting seq1: {1, 2}, seq2 is empty, seq: {0}
    assert(seq.size() == 1);
    assert(seq1.size() == 2);
    assert(seq2.size() == 0);
}

void test_merge() {
    // Basic Merging
    Sequence<int, std::string> seq1, seq2;
    seq1.push_back(1, "one");
    seq1.push_back(2, "two");
    seq1.push_back(3, "three");
    seq2.push_back(4, "four");
    Sequence<int, std::string> merged = merge(seq1, seq2);
    assert(merged.size() == 4); // Check size
    std::string info;
    assert(merged.getInfo(info, 4, 1) && info == "four"); // Check if 'four' is correctly inserted in the middle

    //Merging with Empty Sequences
    Sequence<int, std::string> emptySeq1, emptySeq2;
    Sequence<int, std::string> mergedEmpty = merge(emptySeq1, emptySeq2);
    assert(mergedEmpty.is_empty()); // Merging two empty sequences should result in an empty sequence
    mergedEmpty = merge(seq1, emptySeq2);
    assert(mergedEmpty.size() == 3); // Only elements from seq1
    mergedEmpty = merge(emptySeq1, seq2);
    assert(mergedEmpty.size() == 1); // Only elements from seq2

    //Merging and Verifying Element Order
    Sequence<int, std::string> mergedOrder = merge(seq1, seq2);
    assert(mergedOrder.getInfo(info, 1, 1) && info == "one"); // First element
    assert(mergedOrder.getInfo(info, 4, 1) && info == "four"); // Inserted element from seq2
    assert(mergedOrder.getInfo(info, 2, 1) && info == "two"); // Following element from seq1
    assert(mergedOrder.getInfo(info, 3, 1) && info == "three"); // Last element from seq1
}


void task_two_tests(){
    test_split_pos();
    test_split_key();
    test_merge();
    std::cout<<"Task 2 tests passed"<<std::endl;
}



int main() {
    task_one_tests();
    task_two_tests();
    return 0;
}
