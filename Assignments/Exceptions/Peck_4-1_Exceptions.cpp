// Peck_4-1_Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <exception>
#include <stdexcept>    

class MyCustomException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Custom exception triggered!";
    }
};

bool do_even_more_custom_application_logic()
{
    std::cout << "Running Even More Custom Application Logic." << std::endl;

    // Throwing a standard runtime error from C++ libraries
    throw std::runtime_error("Runtime Error check failed.");

    return true;
}
void do_custom_application_logic()
{
    std::cout << "Running Custom Application Logic." << std::endl;

    //Try-Catch block to catch a standard exception
    try
    {
        //Wrapped this inside the Try block
        if (do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        //Function caught, but did not throw the exception
        std::cout << "Standard Exception thrown " << e.what() << std::endl;
    }

    std::cout << "Leaving Custom Application Logic." << std::endl;

    //Throw custom exception
    throw MyCustomException();
}

float divide(float num, float den)
{
    // Exception must match the one try/catch block that calls this function.
    if (den == 0.0f) {
        throw std::invalid_argument("Division by zero");
    }
    //If execution succeeds (which it will not), return value.
    return (num / den);
}

void do_division() noexcept
{
    float numerator = 10.0f;
    float denominator = 0;
    //Storing this value as 0 to initialize it. Throwing it in a 
    //try-catch block to perform the check while keeping it in
    //scope of this function
    float result = 0.0f;

    //Adding Try-Catch block to see if divide causes a divide by zero error
    try {
        result = divide(numerator, denominator);
    }
    //Throw an exception if the divide exception is thrown
    catch (const std::invalid_argument& e){
        std::cout << "Cannot Divide by 0. " << e.what() << std::endl;
    }

    //No exception is thrown, executes rest of function. Should never reach this as den is hard-coded as '0'
    std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
}

int main()
{
    std::cout << "Exceptions Tests!" << std::endl;
    
    //Try-Catch block to catch all exceptions here.
    try
    {
        do_division();
        do_custom_application_logic();
    }
    catch (const MyCustomException& e)
    {
        //Main function caught the custom exception
        std::cout << "Main function caught custom exception. " << e.what() << std::endl;
    }
    catch (const std::exception& e) 
    {
        //Main function caught the standard exception
        std::cout << "Main function caught standard exception. " << e.what() << std::endl;
    }
    catch (...) 
    {
        //Main function caught an unknown exception
        std::cout << "Main function caught unknown exception. " << std::endl;
    }
}
