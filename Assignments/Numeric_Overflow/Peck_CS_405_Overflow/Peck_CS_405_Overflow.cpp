// Peck_CS_405_Overflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
// NumericOverflows.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>     // std::cout
#include <limits>       // std::numeric_limits

/// <summary>
/// Template function to abstract away the logic of:
///   start + (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to add each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start + (increment * steps)</returns>
template <typename T>
T add_numbers(T const& start, T const& increment, unsigned long int const& steps, bool& overflowed)
{
    T result = start;

    //Start at a safe state
    overflowed = false;

    for (unsigned long int i = 0; i < steps; ++i)
    {
        //If the distance from the value to the max is smaller than the increment, it will
        //overflow when adding
        if (std::numeric_limits<T>::max() - result < increment) {
            //Overflow is predicted.
            
            //Triggered an overflowed state
            overflowed = true;

            //return last valid value
            return result;
        }
        //Safe to add. Will not overflow
        result += increment;
    }

    return result;
}

/// <summary>
/// Template function to abstract away the logic of:
///   start - (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to subtract each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start - (increment * steps)</returns>

template <typename T>
T subtract_numbers(T const& start, T const& decrement, unsigned long int const& steps, bool& overflowed)
{
    T result = start;

    overflowed = false;

    for (unsigned long int i = 0; i < steps; ++i)
    {
        //If the decrement is greater than the value, overflow will happen during subtraction
        if (decrement > result) {
            //Overflow happened
            overflowed = true;

            //Return the failure "signal"
            return result;
        }
        //Safe to subtract
        result -= decrement;
    }

    return result;
}

//  NOTE:
//    You will see the unary ('+') operator used in front of the variables in the test_XXX methods.
//    This forces the output to be a number for cases where cout would assume it is a character. 

template <typename T>
void test_overflow()
{
    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we add each step (result should be: start + (increment * steps))
    const T increment = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = 0;

    std::cout << "Overflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    //Bool to check if overflowed.
    bool didOverflow = false;

    std::cout << "\tAdding Numbers Without Overflow (" << +start << ", " << +increment << ", " << steps << ") = ";
    
    //Added a parameter to pass the boolean to see if we overflowed
    T result = add_numbers<T>(start, increment, steps, didOverflow);
    //If we did overflow, trigger error message to the user
    if (didOverflow) {
        std::cout << "The addition failed due to overflow. Returning last result before overflow." << +result << std::endl;
    }
    else {
        std::cout << +result << std::endl;
    }

    std::cout << "\tAdding Numbers With Overflow (" << +start << ", " << +increment << ", " << (steps + 1) << ") = ";
    
    //Added a parameter to pass the boolean if we overflowed
    result = add_numbers<T>(start, increment, steps + 1, didOverflow);
    
    //If overflowed, send an error message
    if (didOverflow) {
        std::cout << "The addition failed due to overflow. Returning last result before overflow: " << +result << std::endl;
    }
    else {
        std::cout << +result << std::endl;
    }
}

template <typename T>
void test_underflow()
{
    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we subtract each step (result should be: start - (increment * steps))
    const T decrement = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = std::numeric_limits<T>::max();

    std::cout << "Underflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    //Adding a boolean flag to see if we did overflow
    bool didOverflow = false;

    std::cout << "\tSubtracting Numbers Without Overflow (" << +start << ", " << +decrement << ", " << steps << ") = ";
    
    //Adding a parameter to pass the overflow flag
    auto result = subtract_numbers<T>(start, decrement, steps, didOverflow);

    //If overflowed, pass the message
    if (didOverflow) {
        std::cout << "The subtraction failed due to underflow. Returning last result before underflow: " << +result << std::endl;
    }
    else {
        std::cout << +result << std::endl;
    }

    std::cout << "\tSubtracting Numbers With Overflow (" << +start << ", " << +decrement << ", " << (steps + 1) << ") = ";
    
    //Adding a parameter to pass the overflow flag
    result = subtract_numbers<T>(start, decrement, steps + 1, didOverflow);

    if (didOverflow) {
        std::cout << "The subtraction failed due to underflow. Returning last result before underflow: " << +result << std::endl;
    }
    else {
        std::cout << +result << std::endl;
    }
}

void do_overflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Overflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_overflow<char>();
    test_overflow<wchar_t>();
    test_overflow<short int>();
    test_overflow<int>();
    test_overflow<long>();
    test_overflow<long long>();

    // unsigned integers
    test_overflow<unsigned char>();
    test_overflow<unsigned short int>();
    test_overflow<unsigned int>();
    test_overflow<unsigned long>();
    test_overflow<unsigned long long>();

    // real numbers
    test_overflow<float>();
    test_overflow<double>();
    test_overflow<long double>();
}

void do_underflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Undeflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_underflow<char>();
    test_underflow<wchar_t>();
    test_underflow<short int>();
    test_underflow<int>();
    test_underflow<long>();
    test_underflow<long long>();

    // unsigned integers
    test_underflow<unsigned char>();
    test_underflow<unsigned short int>();
    test_underflow<unsigned int>();
    test_underflow<unsigned long>();
    test_underflow<unsigned long long>();

    // real numbers
    test_underflow<float>();
    test_underflow<double>();
    test_underflow<long double>();
}

/// <summary>
/// Entry point into the application
/// </summary>
/// <returns>0 when complete</returns>
int main()
{
    //  create a string of "*" to use in the console
    const std::string star_line = std::string(50, '*');

    std::cout << "Starting Numeric Underflow / Overflow Tests!" << std::endl;

    // run the overflow tests
    do_overflow_tests(star_line);

    // run the underflow tests
    do_underflow_tests(star_line);

    std::cout << std::endl << "All Numeric Underflow / Overflow Tests Complete!" << std::endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu