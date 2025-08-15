cmake_minimum_required(VERSION 4.0)
project(Algorithm)

set(CMAKE_CXX_STANDARD 20)



add_executable(Enumeration LQB/Day_one/Enumeration.cpp)
add_executable(PrefixSum LQB/Day_one/PrefixSum.cpp)
add_executable(Recursion LQB/Day_one/Recursion.cpp)
add_executable(Simulation LQB/Day_one/Simulation.cpp)

add_executable(getIntersectionNode LeetCode/getIntersectionNode.cpp)
add_executable(hasCycle LeetCode/hasCycle.cpp)
add_executable(isPalindrome LeetCode/isPalindrome.cpp)
add_executable(moveZeroes LeetCode/moveZeroes.cpp)
add_executable(reverseList LeetCode/reverseList.cpp)
add_executable(twoSum LeetCode/twoSum.cpp)
add_executable(mergeTwoLists LeetCode/mergeTwoLists.cpp)
add_executable(inorderTraversal LeetCode/inorderTraversal.cpp)