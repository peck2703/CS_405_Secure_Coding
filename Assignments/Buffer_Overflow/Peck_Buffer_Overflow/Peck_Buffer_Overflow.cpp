// Peck_Buffer_Overflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <limits>
#include <iostream>

int main()
{
    std::cout << "Buffer Overflow Example" << std::endl;

    // TODO: The user can type more than 20 characters and overflow the buffer, resulting in account_number being replaced -
    //  even though it is a constant and the compiler buffer overflow checks are on.
    //  You need to modify this method to prevent buffer overflow without changing the account_number
    //  variable, and its position in the declaration. It must always be directly before the variable used for input.
    //  You must notify the user if they entered too much data.


    const std::string account_number = "CharlieBrown42";
    char user_input[20];

    std::cout << "Enter a value: ";

    //Force a cin to only take the length of user_input
    std::cin.width(sizeof(user_input));
    std::cin >> user_input;

    //We want to see if the user still tried to enter more characters that was allowed.
    int next_char = std::cin.peek();

    //Check to see if next_char is null or new line
    //std::char_traits<char>::eof() somehow checks for end of file statements
    if (next_char != ' ' &&  next_char != '\n' && next_char != std::char_traits<char>::eof()) {
        std::cout << "You have entered too many characters. The limit is: " << (sizeof(user_input) - 1) << std::endl;
        std::cout << "You have entered: " << user_input << std::endl;

        //Clear the buffer as needed. Set distance to ignore to maximum stream size
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else {
        std::cout << "You entered: " << user_input << std::endl;
        std::cout << "Account Number = " << account_number << std::endl;
    }
}