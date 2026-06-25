// Peck_Module_5_Encryption.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <ctime>

/// <summary>
/// encrypt or decrypt a source string using the provided key
/// </summary>
/// <param name="source">input string to process</param>
/// <param name="key">key to use in encryption / decryption</param>
/// <returns>transformed string</returns>
std::string encrypt_decrypt(const std::string& source, const std::string& key)
{
    // get lengths now instead of calling the function every time.
    // this would have most likely been inlined by the compiler, but design for perfomance.
    const auto key_length = key.length();
    const auto source_length = source.length();

    // assert that our input data is good
    assert(key_length > 0);
    assert(source_length > 0);

    std::string output = source;

    // loop through the source string char by char
    for (size_t i = 0; i < source_length; ++i)
    { 
        //Using the XOR operator ^, replace the output, by pairing with a character in the key
        output[i] = source[i] ^ key[i % key_length];
    }

    // our output length must equal our source length
    assert(output.length() == source_length);

    // return the transformed string
    return output;
}

std::string read_file(const std::string& filename)
{
    std::string file_text = "John Q. Smith\nThis is my test string";

    //Open the file
    std::ifstream file(filename);

    //Check if file opened successfully
    if (!file.is_open()) {
        std::cout << "Error Opening File." << std::endl;
        return "";
    }

    //read the file in its entirety
    std::stringstream buffer;
    buffer << file.rdbuf();

    //Assign the value of buffer to file_text
    file_text = buffer.str();

    //Return formatted buffer
    return file_text;
}

std::string get_student_name(const std::string& string_data)
{
    std::string student_name;

    // find the first newline
    size_t pos = string_data.find('\n');
    // did we find a newline
    if (pos != std::string::npos)
    { // we did, so copy that substring as the student name
        student_name = string_data.substr(0, pos);
    }

    return student_name;
}

void save_data_file(const std::string& filename, const std::string& student_name, const std::string& key, const std::string& data)
{
    //Get the current calendar time for the timestamp
    std::time_t now = std::time(nullptr);

    //Grab the local time
    std::tm local_time;
    localtime_s(&local_time, &now);

    //Format the timestamp using yyyy-mm-dd
    std::stringstream ss;
    ss << std::put_time(&local_time, "%Y-%m-%d");
    std::string timestamp = ss.str();

    //Open the file
    std::ofstream file(filename);

    //Check if the file cannot be created
    if (!file.is_open()) {
        return;
    }

    //  Line 1: student name
    file << student_name << "\n";
    
    //  Line 2: timestamp (yyyy-mm-dd)
    file << timestamp << "\n";

    //  Line 3: key used
    file << key << "\n";

    //  Line 4+: data
    file << data;
}

int main()
{
    std::cout << "Encyption Decryption Test!" << std::endl;

    // input file format
    // Line 1: <students name>
    // Line 2: <Lorem Ipsum Generator website used> https://pirateipsum.me/ (could be https://www.lipsum.com/ or one of https://www.shopify.com/partners/blog/79940998-15-funny-lorem-ipsum-generators-to-shake-up-your-design-mockups)
    // Lines 3+: <lorem ipsum generated with 3 paragraphs> 
    //  Fire in the hole bowsprit Jack Tar gally holystone sloop grog heave to grapple Sea Legs. Gally hearties case shot crimp spirits pillage galleon chase guns skysail yo-ho-ho. Jury mast coxswain measured fer yer chains man-of-war Privateer yardarm aft handsomely Jolly Roger mutiny.
    //  Hulk coffer doubloon Shiver me timbers long clothes skysail Nelsons folly reef sails Jack Tar Davy Jones' Locker. Splice the main brace ye fathom me bilge water walk the plank bowsprit gun Blimey wench. Parrel Gold Road clap of thunder Shiver me timbers hempen halter yardarm grapple wench bilged on her anchor American Main.
    //  Brigantine coxswain interloper jolly boat heave down cutlass crow's nest wherry dance the hempen jig spirits. Interloper Sea Legs plunder shrouds knave sloop run a shot across the bow Jack Ketch mutiny barkadeer. Heave to gun matey Arr draft jolly boat marooned Cat o'nine tails topsail Blimey.

    const std::string file_name = "inputdatafile.txt";
    const std::string encrypted_file_name = "encrypteddatafile.txt";
    const std::string decrypted_file_name = "decrytpteddatafile.txt";
    const std::string source_string = read_file(file_name);
    const std::string key = "password";

    // get the student name from the data file
    const std::string student_name = get_student_name(source_string);

    // encrypt sourceString with key
    const std::string encrypted_string = encrypt_decrypt(source_string, key);

    // save encrypted_string to file
    save_data_file(encrypted_file_name, student_name, key, encrypted_string);

    // decrypt encryptedString with key
    const std::string decrypted_string = encrypt_decrypt(encrypted_string, key);

    // save decrypted_string to file
    save_data_file(decrypted_file_name, student_name, key, decrypted_string);

    std::cout << "Read File: " << file_name << " - Encrypted To: " << encrypted_file_name << " - Decrypted To: " << decrypted_file_name << std::endl;

    // students submit input file, encrypted file, decrypted file, source code file, and key used
}