#include "cache.hh"
#include <iostream>

uint32_t maxmem = 1024;

int evictor()
{
	return 0;	
}


//Just a utility func to insert a new line
void insert_line()
{
	std::cout << '\n';
}


//test: create a cache and insert key
int test_insert()
{
	std::cout << "TEST: Create cache and insert key:" << '\n';
	Cache c(maxmem, evictor, std::hash<std::string>()); //create cache object
	std::string key = "a";
	char val[] = "z";
	uint32_t size = 1;
	c.set(key, val, size);	
	insert_line();
	return 0;

}

//test: query key

int test_query()
{
	std::cout << "TEST: Query key:" << '\n';
	Cache c(maxmem, evictor, std::hash<std::string>()); //create cache object
	std::string key = "a";
	char val[] = "z";
	uint32_t size = 1;
	c.set(key, val, size);	
	c.get(key, size);
	insert_line();
	return 0;

}
//test: query key that wasn't inserted
int test_query_uninserted()
{
	std::cout << "TEST: Query key that wasn't inserted:" << '\n';
	Cache c(maxmem, evictor, std::hash<std::string>()); //create cache object
	std::string key = "a";
	char val[] = "z";
	uint32_t size = 1;
	c.set(key, val, size);	
	c.get("b", size);
	insert_line();
	return 0;
}

//test: insert key and modify
int test_insert_and_mod()
{
	std::cout << "TEST: Insert key and modify value:" << '\n';
	Cache c(maxmem, evictor, std::hash<std::string>()); //create cache object
	std::string key = "a";
	char val[] = "z";
	char val2[] = "y";
	uint32_t size = 1;
	c.set(key, val, size);	
	std::cout << "Original value: ";
        c.get(key, size);
	c.set(key, val2, size);
	std::cout << "New value: ";
	c.get(key, size);
	insert_line();
	return 0;

}
//test: insert key and delete
int test_insert_and_delete()
{
	std::cout << "TEST: Create cache and delete key:" << '\n';
	Cache c(maxmem, evictor, std::hash<std::string>()); //create cache object
	std::string key = "a";
	char val[] = "z";
	uint32_t size = 1;
	c.set(key, val, size);	
	std::cout << val << '\n';
	std::cout << "deleting... "; 
	c.get(key, size);
	c.del(key);
	insert_line();
	return 0;
}

//test: query key that was evicted

int test_delete_and_query()
{
	std::cout << "TEST: Create cache and check for deleted value:" << '\n';
	Cache c(maxmem, evictor, std::hash<std::string>()); //create cache object
	std::string key = "a";
	char val[] = "z";
	uint32_t size = 1;
	c.set(key, val, size);	
	std::cout << "deleting... " << '\n'; 
	c.get(key, size);
	c.del(key);
	std::cout << "access deleted val: ";
	c.get(key, size);
	insert_line();
	return 0;
}
int main() 
{
	insert_line();
	test_insert();
	test_query();
	test_query_uninserted();
	test_insert_and_mod();
	test_insert_and_delete();
	test_delete_and_query();
	return 0;
}
