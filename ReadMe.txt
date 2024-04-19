Rakan Ghaith
M738R656
CS 540 Operating Systems
Programming Assignment 4

Date: 04/18/2024
Page Replacement Algorithms Simulation Program

This program demonstrates three key page replacement algorithms used in operating systems: First-In, First-Out (FIFO), Least Recently Used (LRU), and Optimal. It is designed to help understand how operating systems manage memory and handle page faults.
Features

    FIFO Algorithm: Manages memory frames using a simple FIFO queue, replacing the oldest page first.
    LRU Algorithm: Keeps track of page usage, ensuring that the least recently used page is replaced.
    Optimal Algorithm: Predictively replaces pages to minimize future page faults, based on upcoming page requests.

How It Works

    The program starts by initializing a predefined list of page requests and a set number of memory frames.
    It simulates each of the three algorithms, processing each page request and managing the memory frames accordingly.
    During simulation, the program outputs the result of each request, indicating page faults and the current state of memory frames.

Implementation Details

    Page Faults: The algorithms check if a page is in memory; if not, a page fault occurs, and the algorithm replaces the appropriate page.
    Memory Management: Each algorithm uses a different strategy to decide which memory frame to replace when a new page needs to be loaded.
    Console Output: The program provides a detailed step-by-step output showing memory state after each page request, page faults, and total faults after all requests are processed.

How to Run

Compile the program using a C++ compiler like g++