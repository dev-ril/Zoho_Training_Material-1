#include <iostream>
#include <vector>
#include <stack>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

mutex m;
condition_variable cv;

stack <int> buffer;

int number_of_producers = 5;
int number_of_consumers = 5;
int max_items = 5;
int delay = 5;

void produce(int p_id)
{
	//Acquiring mutex
	unique_lock <mutex> lock(m);
	int product;

	cv.wait(lock, []{return buffer.size() < 5;});

	// To add produced item to buffer
	product = buffer.size();
	buffer.push(product);

	cout << "Producer " << p_id << " produced " << product << "\n" << endl;
	cv.notify_all();
}

void consume(int c_id)
{
	//Acquiring mutex
	unique_lock <mutex> lock(m); 
	int product;

	cv.wait(lock, [] {return buffer.size() > 0; });

	product = buffer.top();
	// To remove consumed item from buffer
	buffer.pop(); 

	cout << "Consumer " << c_id << " consumed " << product << "\n" << endl;
	cv.notify_all();

}

void producer(int id)
{
	for (int i = 0; i < max_items; i++)
	{
		produce(id);
		this_thread::sleep_for(chrono::milliseconds(3000));
	}
	cout << "Producer "<< id << " has exited" << "\n" << endl;

}

void consumer(int id)
{
	for (int i = 0; i < max_items; i++)
	{
		consume(id);
		this_thread::sleep_for(chrono::milliseconds(5000));
	}
	cout << "Consumer " << id << " has exited" << "\n" << endl;

}

int main()
{
	vector <thread> producers_and_consumers;

	cout << "PRODUCER-CONSUMER USING STD::LIBRARY\n"

	//For creating 10 producer threads
	for (int i = 0; i < number_of_producers; i++)
	{
		producers_and_consumers.push_back(thread(producer, i));
	}
	
	//For creating 10 consumer threads
	for (int i = 0; i < number_of_consumers; i++)
	{
		producers_and_consumers.push_back(thread(consumer, i));
	}

	//To ensure all the threads are completed
	for (auto& t : producers_and_consumers)
	{
		t.join();
	}

	return 0;
}
