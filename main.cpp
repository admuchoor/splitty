#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct Person
{
    std::vector<double> items;
    double total;
    
    Person() : total(0) {}
    Person(const double initial_total) : total(initial_total)
    {
        // don't need the items vector right now, but could be useful for verbose output
        items.push_back(initial_total);
    }

};


std::vector<std::string> split_string(const std::string& s, const std::string& delim)
{
    std::vector<std::string> splitted;

    auto start = 0U;
    auto end = s.find(delim);
    while (end != std::string::npos)
    {
        splitted.push_back(s.substr(start, end - start));
        start = end + delim.length();
        end = s.find(delim, start);
    }
    splitted.push_back(s.substr(start, end));

    return splitted;
}

void update_record(std::unordered_map<std::string, Person>& people, const std::vector<std::string>& splitted, const double price)
{
    double price_per = price / splitted.size();
    for (const auto& name : splitted)
    {
        if (auto it = people.find(name); it != people.end())
        {
            it->second.items.push_back(price_per);
            it->second.total += price_per;
        }
        else
        {
            Person person{price_per};
            people[name] = person;
        }
    }
}

int main(int argc, char** argv)
{
    std::cout << std::setprecision(2) << std::fixed;

    unsigned int num_items;
    std::cout << "How many items were there: ";
    std::cin >> num_items;
    
    double subtotal = 0; 
    std::unordered_map<std::string, Person> people;
    for (unsigned int i = 0; i < num_items; i++)
    {
        double price; 
        std::cout << "How much did item " << i << " cost: ";
        std::cin >> price;
        
        std::string splitted;
        std::cout << "Who split item " << i << " (comma separated names): ";
        std::cin >> splitted;
        
        update_record(people, split_string(splitted, ","), price);
        subtotal += price; 
    }
    
    double total;
    std::cout << "What was the total after tip/tax: ";
    std::cin >> total;

    for (const auto& [name, person] : people)
    {
        std::cout << name << " owes " << total * (person.total / subtotal) << std::endl;
    }

    return 0;
}
