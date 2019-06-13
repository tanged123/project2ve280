//Edward Tang VE280 ID: 716370290043
#include <iostream>
#include <cstdlib>
#include "p2.h"

using namespace std;
//EFFECTS:
//Returns the number of elements in "list". 
//Returns zero if "list" is empty.
int size(list_t list){
    if(list_isEmpty(list)){
        return 0;
    }
    else{
        list_t rest = list_rest(list);
        return 1+size(rest);
    } 
}
//Returns true ifthe value "val" appears in "list".
//Returns false otherwise.
bool memberOf(list_t list, int val){
    if(list_isEmpty(list)){
        return false;
    }
    else{
        if(list_first(list) == val){
            return true;
        }
        else{
            list_t rest = list_rest(list);
            return memberOf(rest, val);
        }
    }
}
//REQUIRES: Both "v1" and "v2" are non-empty
//EFFECTS: Treats both lists as vectors. Returns the dot
//         product of the two vectors. If one list islonger
//         than the other, ignore the longer part of the vector.
int dot(list_t v1, list_t v2){
    if(list_isEmpty(v1)){
        return 0;
    }
    if(list_isEmpty(v2)){
        return 0;
    }
    list_t rest_v1 = list_rest(v1);
    list_t rest_v2 = list_rest(v2);
    return list_first(v1)*list_first(v2) + dot(rest_v1, rest_v2);
}
//EFFECTS: 
//Checks if the list of integers is increasing.
bool isIncreasing(list_t v){
    cout <<"i";
    if(list_isEmpty(v)){
        return true;
    }
    list_t rest = list_rest(v);
    if(list_isEmpty(rest)){
        return true;
    }
    if(list_first(v) < list_first(rest)){
        return isIncreasing(rest);
    }
    else{
        return false;
    }

}
//Helper function to reverse a list
static list_t reverse_helper(list_t original, list_t reverse){
    if(list_isEmpty(original)){
        return reverse;
    }
    else{
        reverse = list_make(list_first(original), reverse);
        original = list_rest(original);
        return reverse_helper(original, reverse);
    }
}
//EFFECTS: Reverses the list
list_t reverse(list_t list){
    list_t reverse = list_make();
    return reverse_helper(list, reverse);
}
//Helper for append function
static list_t append_helper(list_t first, list_t second){
    if(list_isEmpty(first)){
        return second;
    }
    else{
        second = list_make(list_first(first), second);
        first = list_rest(first);
        return append_helper(first, second);
    }
}
//EFFECTS: appends the first list to the second in the form (firstsecond)
list_t append(list_t first, list_t second){
    first = reverse(first);
    return append_helper(first, second);
}
//EFFECTS: Determins if the list is an arithmetic sequence
bool isArithmeticSequence(list_t v){
    if(list_isEmpty(v)){
        return true;
    }
    else if(list_isEmpty(list_rest(v))){
        return true;
    }
    else if(list_isEmpty(list_rest(list_rest(v)))){
        return true;
    }
    else{
        if(list_first(list_rest(v)) - list_first(v) == list_first(list_rest(list_rest(v)))- list_first(list_rest(v))){
            return isArithmeticSequence(list_rest(v));
        }
    }
}
//helper function for filter_odd
static list_t filter_odd_helper(list_t original, list_t filtered){
    if(list_isEmpty(original)){
        return filtered;
    }
    else{
        if(list_first(original)%2 == 1){
            filtered = list_make(list_first(original), filtered);
        }
        original = list_rest(original);
        return filter_odd_helper(original, filtered);
    }
}
//EFFECTS: filters odd numbers from a list
list_t filter_odd(list_t list){
    list = reverse(list);
    list_t filtered = list_make();
    return filter_odd_helper(list, filtered);
}
//helper function for filter
static list_t filter_helper(list_t original, list_t filtered, bool (*fn)(int)){
    if(list_isEmpty(original)){
        return filtered;
    }
    else{
        if(fn(list_first(original))){
            filtered = list_make(list_first(original), filtered);
        }
        original = list_rest(original);
        return filter_helper(original, filtered, fn);
    }
}
//filters out list depending on fn boolean
list_t filter(list_t list, bool (fn)(int)){
    list = reverse(list);
    list_t filtered = list_make();
    return filter_helper(list, filtered, fn);
}
//helper function for process unique
static list_t process_unique_helper(list_t original, list_t filtered ,int element){
    if(list_isEmpty(original)){
        return filtered;
    }
    else{
        if(list_first(original) != element){
            filtered = list_make(list_first(original), filtered);
        }
        original = list_rest(original);
        return process_unique_helper(original, filtered, element);
    }
}
//processes unique numbers and removes them from the list using filter
static list_t process_unique(list_t original,int element){
    list_t filtered = list_make();
    return reverse(process_unique_helper(original, filtered, element));
}
//helper function for unique
static list_t unique_helper(list_t original, list_t unique){
    if(list_isEmpty(original)){
        return unique;
    }
    else{
        int first_element = list_first(original);
        unique = list_make(first_element, unique);
        original = list_rest(original);
        original = process_unique(original, first_element);
        return unique_helper(original, unique);
    }
}
//processes a list and removes non-unique numbers, returning a list of unique numbers
list_t unique(list_t list){
    list = reverse(list);
    list_t temp = list_make();
    return reverse(unique_helper(list, temp));
}
//helper function that splits a list depending on n
static list_t split_helper(list_t list, list_t second, unsigned int n){
    if(n > 0){
        second = list_make(list_first(list), second);
        list = list_rest(list);
        --n;
        return split_helper(list, second, n);
    }
    else{
        return second;
    }
}
//returns the first half of the list split by n
static list_t secondhalf(list_t list, unsigned int n){
    list = reverse(list);
    list_t empty = list_make();
    split_helper(list,empty,size(list)-n);
}
//returns the second half of the list split by n
static list_t firsthalf(list_t list, unsigned int n){
    list_t empty = list_make();
    reverse(split_helper(list, empty, n));
}
//inserts list second in list first at point n
list_t insert_list(list_t first, list_t second, unsigned int n){
    if(list_isEmpty(first)){
        return second;
    }
    else{
        list_t first_half = firsthalf(first, n);
        list_t second_half = secondhalf(first, n);
        return append(append(first_half, second),second_half);
    }
}
//chops off the end of list depending on n
list_t chop(list_t list, unsigned int n){
    list_t empty = list_make();
    return reverse(split_helper(list, empty, size(list)-n));
}
//sums up tree
int tree_sum(tree_t tree){
    if(tree_isEmpty(tree)){
        return 0;
    }
    else{
        return tree_elt(tree) + tree_sum(tree_left(tree)) + tree_sum(tree_right(tree));
    }
}
//searches tree for value
bool tree_search(tree_t tree, int val){
    if(tree_isEmpty(tree)){
        return false;
    }
    else{
        if(tree_elt(tree) == val){
            return true;
        }
        else{
            return tree_search(tree_left(tree), val) || tree_search(tree_right(tree), val);
        }
    }
}
//finds the depth of the tree
int depth(tree_t tree){
    if(tree_isEmpty(tree)){
        return 0;
    }
    else{
        int right_depth = depth(tree_right(tree));
        int left_depth = depth(tree_left(tree));
        if(right_depth > left_depth){
            return right_depth + 1;
        }
        else{
            return left_depth + 1;
        }
    }
}
//finds the max element of the tree
int tree_max(tree_t tree){
    if(tree_isEmpty(tree)){
        return -999999999;
    }
    else{
        int current_element = tree_elt(tree);
        int right_element = tree_max(tree_right(tree));
        int left_element = tree_max(tree_left(tree));
        if(right_element > current_element){
            return right_element;
        }
        if(left_element > current_element){
            return left_element;
        }
        else{
            return current_element;
        }
    }
}
//returns a list from the tree sorted inorder
list_t traversal (tree_t tree){
    if(tree_isEmpty(tree)){
        return list_make();
    }
    list_t left_list = traversal(tree_left(tree));
    list_t elt = list_make(tree_elt(tree), list_make());
    list_t result = append(left_list, elt);
    list_t right_list = traversal(tree_right(tree));
    result = append(result, right_list);
    return result;
}
//finds if there is a monotonicly increasing path in the tree
bool tree_greaterPath(tree_t tree){
    if(tree_isEmpty(tree)){
        return true;
    }
    if(((tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_left(tree))) || (!tree_isEmpty(tree_left(tree)) && tree_elt(tree) < tree_elt(tree_left(tree)))) && tree_greaterPath(tree_left(tree))){
        return true;
    }
    if(((tree_isEmpty(tree_right(tree)) && tree_isEmpty(tree_left(tree))) || (!tree_isEmpty(tree_right(tree)) && tree_elt(tree) < tree_elt(tree_right(tree)))) && tree_greaterPath(tree_right(tree))){
        return true;
    }
    return false;
}
//finds if there is a monotonicly decreasing path in the tree
bool tree_lesserPath(tree_t tree){//underconstruction
    if(tree_isEmpty(tree)){
        return true;
    }
    if(((tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_left(tree))) || (!tree_isEmpty(tree_left(tree)) && tree_elt(tree) > tree_elt(tree_left(tree)))) && tree_lesserPath(tree_left(tree))){
        return true;
    }
    if(((tree_isEmpty(tree_right(tree)) && tree_isEmpty(tree_left(tree))) || (!tree_isEmpty(tree_right(tree)) && tree_elt(tree) > tree_elt(tree_right(tree)))) && tree_lesserPath(tree_right(tree))){
        return true;
    }
    return false;
}
//returns true if there is either a decreasing or increasing monotoic path
bool tree_hasMonotonicPath(tree_t tree){
    if(depth(tree)>1){
        return tree_lesserPath(tree)||tree_greaterPath(tree);
    }
    else{
        return false;
    }
}
//returns true if all root-leaf paths sum greater than the given int
bool tree_allPathSumGreater(tree_t tree, int sum){
    if(tree_isEmpty(tree)){
        return true;
    }
    else if(tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree)) && sum - tree_elt(tree) >= 0){
        return false;
    }
    else{
        return tree_allPathSumGreater(tree_left(tree), sum-tree_elt(tree)) && tree_allPathSumGreater(tree_right(tree), sum-tree_elt(tree));
    }
}
//returns true if tree b covers tree a
bool covered_by(tree_t A, tree_t B){
    if(tree_isEmpty(A)){
        return true;
    }
    if(tree_isEmpty(B)){
        return false;
    }
    else{
        if(tree_elt(A) == tree_elt(B) && covered_by(tree_left(A), tree_left(B)) && covered_by(tree_right(A), tree_right(B))){
            return true;
        }
    }
    return false;
}
//returns true if tree b contains tree a
bool contained_by(tree_t A, tree_t B){
    if(tree_isEmpty(A)){
        return true;
    }
    if(tree_isEmpty(B)){
        return false;
    }
    if(covered_by(A, B)){
        return true;
    }
    else{
        if(contained_by(A, tree_left(B)) || contained_by(A, tree_right(B))){
            return true;
        }
    }
    return false;
}
//inserts an element into a sorted tree in a manner that returns a sorted tree
tree_t insert_tree(int elt, tree_t tree){
    if(tree_isEmpty(tree)){
        return tree_make(elt, tree, tree);
    }
    if(elt < tree_elt(tree)){
        return tree_make(tree_elt(tree), insert_tree(elt, tree_left(tree)), tree_right(tree));
    }
    else if(elt > tree_elt(tree)){
        return tree_make(tree_elt(tree), tree_left(tree), insert_tree(elt, tree_right(tree)));
    }   
}