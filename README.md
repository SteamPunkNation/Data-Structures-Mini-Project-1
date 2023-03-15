# Data-Structures-Mini-Project-1
This is a project done by Andrew Donate, Noah Legault, and Devin St John.
The project required three seperate programs coded in C++.
## Part A: BST-AVL API
Problem Description
Task: In this project, we are giving you a semi-complete API for binary search tree. It implements most of
the functions need it for BST. However, it does not implement local search like range search. In addition,
you will be adding the ability of the self-balancing which allow the tree to keep balance in the presence of
insertion, deletion

## Part B: TRANSFORMING AN ARRAY INTO A HEAP
Problem Introduction
Here, you will be transforming an array into a heap, in this case a min-heap (opposite to the one we learned
in class max-heap). Transforming an array into heap is the first step of the famous sorting algorithm
HeapSort(). By the way, keep in mind that HeapSort is used for external sort when you need to sort huge
files that don’t fit into the memory of your computer.
Problem Description
Task. Your task is to implement this first step and convert a given array of integers into a heap. You will
do that by applying a certain number of swaps to the array. Swap is an operation which exchanges
elements 𝑎𝑖 and 𝑎𝑗 of the array 𝑎 for some 𝑖 and 𝑗. You will need to convert the array into a heap using
only 𝑂(𝑛) swaps, as was described in the lectures. Note that you will need to use a min-heap instead
of a max-heap in this problem!
![image](https://user-images.githubusercontent.com/23602136/225462703-2bacee2c-456f-49c9-bacc-d8ab92d6d3be.png)

## Part C: Application, Simulating a Linux scheduler
Problem Introduction
An important component of the operating systems are the schedulers. They come in different forms and
flavors: we have simple ones such as round-robin, lottery, stride, and those based on priorities such as
multi-level feedback queues. In this problem you will simulating an scheduler based on priorities that
processes a list of tasks in parallel.
Problem Description
Task. You have a program which is parallelized and uses 𝑛 independent threads to process the given list of 𝑚
jobs or tasks. Threads take tasks in the order they are given in the input. If there is a free thread, it
immediately takes the next job from the list. If a thread has started processing a job, it doesn’t interrupt
or stop until it finishes processing the job. If several threads try to take jobs from the list
simultaneously, the thread with smaller index takes the job. For each job you know exactly how long
will it take any thread to process this job, and this time is the same for all the threads. You need to
determine for each job which thread will process it and when will it start processing.
