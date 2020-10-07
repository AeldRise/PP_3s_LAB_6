#include <stdio.h>
#include <iostream>
#include <future>
#include <thread>
#include <cmath>

std::promise<double> promise;
double eps = 0.001;

double f(double x)
{
	return x + log10(x) - 0.5;
}

void thread_func1(double x0, double x1)
{
	double result;
	double x2;
	while (fabs(x1 - x0) >= eps)
	{
		x2 = x1 - (f(x1) * (x1 - x0)) / (f(x1) - f(x0));
		x0 = x1;
		x1 = x2;
	}
	result = x1;
	promise.set_value(result);
}

double thread_func2()
{
	return promise.get_future().get();
}

int main()
{
	double x0 = 0.1;
	double x1 = 1.0;
	std::thread th1(thread_func1, x0, x1);
	std::future<double> result = std::async(thread_func2);
	th1.join();
	std::cout << "Result = " << result.get() << std::endl;
	printf("\n\nPress any key...");
	return 0;
}
