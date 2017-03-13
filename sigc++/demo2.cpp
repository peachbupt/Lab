#include <iostream>
#include <sigc++/sigc++.h>

class Detector
{
public:
	sigc::signal<void, std::string> signal_detected;
public:
	void run()
	{
		signal_detected("Beijing");
	}
};

void warn_people(std::string where)
{
	std::cout<<"there is aliens in "<<where<<"!"<<std::endl;
}

int main()
{
	Detector d;
	d.signal_detected.connect(sigc::ptr_fun(warn_people));
	d.run();
	return 0;
}




