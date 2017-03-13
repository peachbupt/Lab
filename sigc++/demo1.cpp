#include <iostream>
#include <sigc++/sigc++.h>
#include <pthread.h>

using namespace std;

void notifier1()
{
	std::cout<<"["<<(unsigned long)pthread_self()<<"] Notifier1 worked\n";
}

class BaseWorker
{
public:
	void LongOperation()
	{
		mSignalFinished.emit();
	}
public:
	sigc::signal<void>	mSignalFinished;
};

class Worker1 : public BaseWorker
{};
class Worker2 : public BaseWorker
{};

class Notifier2 : public sigc::trackable
{
public:
	void LongOperationFinished()
	{
		std::cout<<"["<<pthread_self()<<"] Notifier2 worked\n";
	}
};

void* thread_1(void* data)
{
	Worker2* pWorker2 = (Worker2*)data;
	std::cout<<"["<<pthread_self()<<"] new thread created\n";
	pWorker2->LongOperation();
	return NULL;
}

int main()
{
	Notifier2 notifier2;
	Worker1	worker1;
	Worker2 worker2;

	worker1.mSignalFinished.connect(sigc::mem_fun(notifier2,
		&Notifier2::LongOperationFinished));
	worker1.mSignalFinished.connect(sigc::ptr_fun(notifier1));

    worker2.mSignalFinished.connect(sigc::mem_fun(notifier2,
        &Notifier2::LongOperationFinished));
    worker2.mSignalFinished.connect(sigc::ptr_fun(notifier1));

	std::cout<<"["<<pthread_self()<<"] worker 1 notify signal"<<std::endl;
	worker1.LongOperation();
 	std::cout<<"["<<pthread_self()<<"] worker 2 notify signal"<<std::endl;
	pthread_t id;
	pthread_create(&id, NULL, thread_1, (void*)&worker2);
	pthread_join(id, NULL);
	return 0;
}




