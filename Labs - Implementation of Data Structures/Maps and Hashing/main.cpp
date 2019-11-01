#include <ctime>
#include <string>
#include <utility>
#include <iostream>
#include "hashmap.hpp"

int main(){

	std::cout << std::boolalpha;
	
	hashmap<std::string> map;
	
	map.add(53, "First");
	map.add(38, "Second");
	map.add(12, "Third");
	
	std::cout << "Is there something with key " << 53 << "? " << map.has_key(53) << std::endl;
	std::cout << "Is there something with key " << 38 << "? " << map.has_key(38) << std::endl;
	std::cout << "Is there something with key " << 12 << "? " << map.has_key(12) << std::endl;
	std::cout << "Is there something with key " << 7 << "? " << map.has_key(7) << std::endl;
	std::cout << "Is there something with key " << 92 << "? " << map.has_key(92) << std::endl;
	std::cout << "Is there something with key " << -46 << "? " << map.has_key(-46) << std::endl;
	
	std::cout << "Does it have a value " << "First" << "? " << map.has_value("First") << std::endl;
	std::cout << "Does it have a value " << "Second" << "? " << map.has_value("Second") << std::endl;
	std::cout << "Does it have a value " << "Third" << "? " << map.has_value("Third") << std::endl;
	std::cout << "Does it have a value " << "Fourth" << "? " << map.has_value("Fourth") << std::endl;
	
	std::cout << "What is the position of value " << "First" << "? " << map.get_key("First") << std::endl;
	std::cout << "What is the position of value " << "Second" << "? " << map.get_key("Second") << std::endl;
	std::cout << "What is the position of value " << "Third" << "? " << map.get_key("Third") << std::endl;
	std::cout << "What is the position of value " << "Fourth" << "? " << map.get_key("Fourth") << std::endl;
	
	std::cout << "Getting something with key " << 53 << "... We got " << map.get(53) << std::endl;
	std::cout << "Getting something with key " << 38 << "... We got " << map.get(38) << std::endl;
	std::cout << "Getting something with key " << 12 << "... We got " << map.get(12) << std::endl;
	std::cout << "Getting something with key " << -46 << "... We got " << map.get(-46) << std::endl;
}
