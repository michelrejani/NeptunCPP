#include <string>
#include <iostream>
#include <thread>

using namespace std;

//The function we want to make the thread run.
void task1(string msg)
{
	while (true){
		cout << "task1 says: " << msg << "\n";
		this_thread::sleep_for(chrono::milliseconds(500));
	}
}

void task2(string msg)
{
	while (true){
		cout << "task2 says: " << msg << "\n";
		this_thread::sleep_for(chrono::seconds(2));
	}
}

int main()
{

	// Constructs the new thread and runs it. Does not block execution.
	thread t1(task1, "Hello");
	thread t2(task2, "Bigola");
	
	
	//// Initialize Winsock
	//int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	//if (iResult != 0) {
	//	printf("WSAStartup failed: %d\n", iResult);
	//	//return 1;
	//}
	//else{
	//	printf("WSAStartup suceed: %d\n", iResult);
	//}

	while (true){
		cout << "pudim \n";
		this_thread::sleep_for(chrono::seconds(1));
	}
		

	//Makes the main thread wait for the new thread to finish execution, therefore blocks its own execution.
	t1.join();
	t2.join();
	system("pause");
}