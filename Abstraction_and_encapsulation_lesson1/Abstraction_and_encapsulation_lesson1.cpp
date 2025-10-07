#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

class Address
{
private:

    std::string city{};
    std::string street{};
    std::string house{};
    std::string apartment{};
public:

    Address(std::string& setCity, std::string& setStreet, std::string& setHouse, std::string& setApartment) : city{ setCity }, street{ setStreet }, house{ setHouse }, apartment{ setApartment }
    {
    }
    Address() {};
    const std::string get_output_address()
    {
        return (city + ' ' + street + ' ' + house + ' ' + apartment);
    };
};

Address* create_arr(int size);
void delete_arr(Address*& array);

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int size{};
    Address* example = nullptr;
    std::string filePath = "in.txt";
    std::ifstream file(filePath);
    if (file.is_open())
    {
        file >> size;
        std::string city, street, house, apartment;
        example = create_arr(size);
        file >> std::ws;
        for (int i{}; i < size; ++i)
        {
            std::getline(file, city);
            std::getline(file, street);
            std::getline(file, house);
            std::getline(file, apartment);
            Address address{ city, street, house, apartment };
            example[i] = address;

        }
        file.close();
    }
    else
    {
        std::cout << "Файл не найден!";
    }
    std::string output_FilePath = "out.txt";
    std::ofstream output_File(output_FilePath);
    if (output_File.is_open())
    {
        output_File << size << std::endl;
        for (int i{}; i < size; ++i)
        {
            output_File << example[i].get_output_address() << std::endl;
        }
        output_File.close();
    }
    else
    {
        std::cout << "Файл не найден!";
    }
    delete_arr(example);
    return EXIT_SUCCESS;
}


Address* create_arr(int size)
{
    return new Address[size]{};
}


void delete_arr(Address*& array)
{
    delete[] array;
    array = nullptr;
}

