#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

class Address
{
private:
    std::string city{}; // поля
    std::string street{};
    int house{};
    int apartment{};

public:
    // конструктор
    Address(const std::string& setCity, const std::string& setStreet, int setHouse, int setApartment) : city{ setCity }, street{ setStreet }, house{ setHouse }, apartment{ setApartment } {}
    Address() {}
    // чтение из файла, создание массива, заполнение массива      
    static Address** read_and_create_arr(const std::string& path_to_file, int& size)
    {
        std::ifstream file(path_to_file);
        if (file.is_open())
        {
            file >> size;
            file >> std::ws;
            Address** addresses{ new Address * [size] {} };
            std::string city, street, house1, apartment1;
            for (int i{}; i < size; ++i)
            {
                std::getline(file, city);
                std::getline(file, street);
                std::getline(file, house1);
                std::getline(file, apartment1);
                int house = std::stoi(house1);
                int apartment = std::stoi(apartment1);
                addresses[i] = new Address(city, street, house, apartment);
            }
            file.close();
            return addresses;
        }
        else
        {
            std::cout << "Файл не найден!";
        }
    }

    static void sort(Address** addresses, int& size)
    {
        bool snapped{ false };
        for (int i{}; i < size - 1; ++i)
        {
            snapped = false;
            for (int j{}; j < size - 1 - i; ++j)
            {                
                if (addresses[j]->city < addresses[j + 1]->city)
                {
                    Address* temporary{ addresses[j] };
                    addresses[j] = addresses[j + 1];
                    addresses[j + 1] = temporary;
                    snapped = true;
                }
            }
            if (!snapped) 
            {
                break; 
            }
        }
    }

    // запись в файл
    static void output_to_file(const std::string& path_to_file, Address** addresses, int& size)
    {
        std::ofstream file(path_to_file);
        if (file.is_open())
        {
            file << size << '\n';
            for (int i = size - 1; i >= 0; --i)
            {
                file << addresses[i]->city << ", " << addresses[i]->street << ", " << addresses[i]->house << ", " << addresses[i]->apartment << '\n';
            }
            file.close();
        }
    }
};

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::string filePath = "in.txt";
    std::string output_FilePath = "out.txt";
    int size{};
    Address address{};
    Address** addresses = Address::read_and_create_arr(filePath, size);
    address.sort(addresses, size);
    address.output_to_file(output_FilePath, addresses, size);
    for (int i = 0; i < size; ++i)
    {
        delete addresses[i];
    }
    delete[] addresses;
    return EXIT_SUCCESS;
}