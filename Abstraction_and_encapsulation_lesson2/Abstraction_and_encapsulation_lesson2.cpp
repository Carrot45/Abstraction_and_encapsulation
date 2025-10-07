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
    {}
    Address() {};
    const std::string get_output_address()
    {
        return (city + ' ' + street + ' ' + house + ' ' + apartment);
    };
    std::string getCity()
    {
        return city;
    }
};

Address* create_arr(int size);
void delete_arr(Address*& array);
void sort(Address* address, int size);

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
    sort(example, size);
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

void sort(Address* address, int size)
    {
        for (int i{}; i < size - 1; ++i)
        {     
            bool swapped = false;
            for (int j{}; j < size - 1 - i; ++j)
            {
                if (address[j].getCity() > address[j + 1].getCity())
                {
                    Address temporary = address[j];
                    address[j] = address[j + 1];
                    address[j + 1] = temporary;
                    swapped = true;
                }
            }
            if (!swapped)
            {
                break;
            }            
        }
    }

   
