#include <vector>
#include <thread>
#include <iostream>
#include <algorithm>

typedef unsigned long long ULLONG;
 

struct Sum
{
	Sum() : sum(0) {};
	Sum(const Sum&) = default;
	Sum& operator=(const Sum&) = default;
	~Sum() = default;
	void operator()(ULLONG  start, ULLONG  end)
	{
		this->sum = 0;
		for (ULLONG i = start; i <= end; ++i)
		{
			this->sum += i;
		}
		
	}
	ULLONG sum;
};

ULLONG vectAccumulate(std::vector<Sum*>& vect)
{
	ULLONG total{ 0 };

	for (const auto& item : vect)
	{

		total += item->sum;

	}
	return total;
}

int main()
{
	constexpr int number_of_threads = 10000;    //1, 5,  3 , 6 , 8 , 9 , 5 , 10000
	constexpr ULLONG  number_of_items = 1000 * 1000 * 1000; //5, 1, ,7 , 21 ,21 ,26, 10 ,1000 * 1000 * 1000
	constexpr ULLONG  step = number_of_items / number_of_threads;

	ULLONG  NUM = number_of_threads;

	if (number_of_items % number_of_threads != 0)
	{
		NUM = number_of_threads - 1;
	}

	ULLONG  counter = 1;
	size_t  index = 0;
	ULLONG  start = 0;
	ULLONG  end = 0;
	std::vector<std::thread> workers;
	std::vector<Sum*> vectSum(number_of_threads);

	//Assigning a task to a specific thread
	for (; index < NUM; ++index, counter += step)
	{
		start = counter;
		end = counter + step - 1;

		std::cout << start << "  , " << end << " , " << index << '\n';

		Sum* sumObj = new Sum();
		//workers.push_back(std::thread(std::ref(*sumNumObj), start, end));
		//The following is more efficient
		workers.emplace_back(std::ref(*sumObj), start, end);

		/*
	The sumObj variable inside the loop and the pointer stored in the vectSum vector both
	point to the same dynamically allocated memory.
	When you use the new keyword to allocate memory for an object on the heap,
	it returns a pointer to that memory.
	In this case, the pointer returned by new is stored in the sumObj variable inside the loop,
	and then copied into the vectSum vector using push_back.
	So both sumObj and the pointer in the vectSum vector point to the same dynamically allocated memory.
	When you access the pointer in the vector later, you are accessing the same memory that
	was allocated by new inside the loop.
	*/


		vectSum.at(index) = sumObj; //It is being copied (we are copying the memory address into the vector)
		//OR
		//vectSum.push_back(sumNumObj);

	}

	if (number_of_items % number_of_threads != 0)
	{
		std::cout << counter << "  , " << number_of_items << " , " << index << '\n';

		Sum* sumObj = new Sum();
		//workers.push_back(std::thread(std::ref(*sumNumObj), counter, number_of_items));
		//The following is more efficient
		workers.emplace_back(std::ref(*sumObj), counter, number_of_items);

		/*
		The sumObj variable inside the loop and the pointer stored in the vectSum vector both
		point to the same dynamically allocated memory.
		When you use the new keyword to allocate memory for an object on the heap,
		it returns a pointer to that memory.
		In this case, the pointer returned by new is stored in the sumObj variable inside the loop,
		and then copied into the vectSum vector using push_back.
		So both sumObj and the pointer in the vectSum vector point to the same dynamically allocated memory.
		When you access the pointer in the vector later, you are accessing the same memory that
		was allocated by new inside the loop.
		*/

		vectSum.at(index) = (sumObj); //It is being copied (we are copying the memory address into the vector)
		//OR
		//vectSum.push_back(sumNumObj);

		/*

		 The at method requires that the vector already has at least n elements,
		 where n is the index of the element you want to access.
		 If the vector has fewer than n elements, std::out_of_range exception is thrown.
		On the other hand, the push_back method can be used to add elements to an empty vector,
		or to a vector that already has some elements.
		In the latter case, the size of the vector is automatically increased to accommodate the new elements.

		*/

	}

	//Waiting for the threads to join
	std::for_each(workers.begin(), workers.end(),

		[](std::thread& th) -> void
		{th.join(); }

	);


	std::cout << "total: " << vectAccumulate(vectSum) << "\n";

	//Release the memory
	for (auto& item : vectSum)
	{
		delete item;
	}


}