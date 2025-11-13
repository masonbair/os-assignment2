# os-assignment2
## Bankers Algorithm 

This is the second assignment for Operating systems at Kent State University. For this homework, we had to recreate the bankers algorithm. This algorithm is used for determing if a computer has enough resources to give out to all the processes to avoid a deadlock. 

Just like a bank, a bank can only loan out so much money to its customers. If a bank runs out of money to loan, it can cause a deadlock. So the bank needs to strategically hand out money so that it will get enough money back for the next person and so on.

The algorithm I wrote works as follows. We have an allocation 2D vector and a max allocation 2D vector. The max allocation tells use how many resources we need for this process to be completed, and the allocation tells us how many resources are currently assigned to the process. We also have a vector that tells us how many available resources we have. From these two 2D vectors, we make a new 2D vector called needed, which is the amount of avaible resources needed to finish this process.

The vector of available resources is important, as that is used to determine what processes can run. And after a process is completed, the allocated resources from that process are added to the allocation 2D vector.

This goes through until all processes can be completed. If a process cannot be completed then that results in a deadlock.

As for the question of is this sequence in a safe state: Yes it is.

After running the algorithm, a safe sequence is as follows
P3, P4, P1, P2, P0

## How to run this program
This c++ program takes in a file as input and uses this file to run the algorithm.

Firstly to compile the program run
```bash
g++ bankers.cpp -o bankers
```
Secondly, you need to create a new text file for your input data. In our case we made a input.txt file.
For this file, the data is read as numbers. The first number is the amount of processes, and the second number is the amount of resources:
In our case: 5 3

Then, we need to have two 5x3 data fields for the allocation and max allocation:
In our case:
0 1 0
2 0 0
3 0 2
2 2 1
0 0 2
7 5 3
3 3 2
9 0 2
2 2 2
4 3 3

Where:
0 1 0
2 0 0
3 0 2
2 2 1
0 0 2
Is the allocation

and 
7 5 3
3 3 2
9 0 2
2 2 2
4 3 3
Is the max allocation

and finally, we have the current amount of available resources:
3 2 2

# Thirdly
Once you have your file constructed you can now run the program
```bash
./bankers input.txt
```

After the program finishes, you should be left with the output:
```
After running the algorithm, a safe sequence is as follows
P3, P4, P1, P2, P0
```