# Effective multi-threaded summation of large numbers
This is a program for parallelizing the calculation of the sum of large numbers using multiple threads. 
The program divides the range of numbers to be summed into smaller segments and assigns each segment to a separate thread for processing.
The individual thread results are then combined to obtain the final sum. This approach speeds up the calculation of the sum, especially for large input ranges,
by utilizing multiple CPU cores in parallel.

# Functors
In C++, functors are objects that act like functions. They are also known as function objects.
Functors are implemented as classes that overload the function call operator operator(). 
When you create an instance of a functor class and call it like a function, 
the operator() function is executed. This allows you to use the functor as if it were a function.

# Notes
In the loop, a new AccumulateFunctor object is created on each iteration using the new keyword. new dynamically allocates memory for the object on the heap, and returns a pointer to that memory.

The address of the dynamically allocated object is then stored in a pointer variable named functor. This pointer variable is local to the loop, so it goes out of scope at the end of each iteration.

However, the memory that functor points to is still valid, because it was dynamically allocated on the heap. The memory will remain valid until it is explicitly deallocated using the delete keyword, or until the program terminates.

The pointer variable functor is then pushed into the functors vector using the push_back method. push_back makes a copy of the pointer variable, and stores the copy in the vector.

The functors vector is a container that holds a sequence of pointers to AccumulateFunctor objects. When the vector is destroyed, either explicitly or implicitly (when the program terminates), it frees the memory of the pointers it contains.

However, the AccumulateFunctor objects themselves are not managed by the vector. They were dynamically allocated using new, so they must be explicitly deallocated using delete.

So in summary, the pointers stored in the functors vector remain valid even after the loop ends, because they point to dynamically allocated memory that is not freed until the program terminates. However, the AccumulateFunctor objects themselves are not managed by the vector, so they must be explicitly deallocated using delete to avoid a memory leak.


# Important Note
The functor variable inside the loop and the pointer stored in the functors vector both point to the same dynamically allocated memory.

When you use the new keyword to allocate memory for an object on the heap, it returns a pointer to that memory. In this case, the pointer returned by new is stored in the functor variable inside the loop, and then copied into the functors vector using push_back.

So both functor and the pointer in the functors vector point to the same dynamically allocated memory. When you access the pointer in the vector later, you are accessing the same memory that was allocated by new inside the loop.

It's worth noting that because both functor and the pointer in the vector point to the same memory, modifying the object through one pointer will also affect the object accessed through the other pointer. In this code, that doesn't seem to be a problem because the objects are read-only, but it's something to be aware of in general.

# Link to the source for the solution
https://www.youtube.com/watch?v=3aqxaZsvn80&list=PLHn7_PzMqzs7c1Ywzpy58SK9zqcNnXQ_B&ab_channel=arisaif
