cmake_minimum_required(VERSION 3.31)
project(Data_Structure C)

set(CMAKE_C_STANDARD 11)

add_executable(List_one Day_one/List_one.c)
add_executable(List_two Day_one/List_two.c)
add_executable(Stack_one Day_two/Stack_one.c)
add_executable(Stack_two Day_two/Stack_two.c)
add_executable(StackList Day_two/StackList.c)
add_executable(Queue_one Day_three/queue_one.c)
add_executable(Queue_two Day_three/Queue_two.c)
add_executable(QueueList Day_three/QueueList.c)
add_executable(Tree_one Day_four/Tree_one.c)

add_executable(Tree_two Day_four/Tree_two.c)