#include "cache.hh"
#include <iostream>
//#include <string>
uint32_t maxmem = 1024;

int evictor()
{
	return 0;	
}


//test: create a cache and insert key
int test_insert()
{
	std::cout << "Create cache and insert key:" << '\n';
	Cache c(maxmem, evictor, std::hash<std::string>()); //create cache object
	std::string key = "a";
	char val[] = "z";
	uint32_t size = 1;
	c.set(key, val, size);	
	std::cout << '\n';
	return 0;

}

//test: query key

int test_query()
{
	std::cout << "Query key:" << '\n';
	Cache c(maxmem, evictor, std::hash<std::string>()); //create cache object
	std::string key = "a";
	char val[] = "z";
	uint32_t size = 1;
	c.set(key, val, size);	
	std::cout << '\n';
	c.get(key, size);
	std::cout << '\n';
	return 0;

}
//test: query key that wasn't inserted
int test_query_uninserted()
{
	std::cout << "Query key that wasn't inserted:" << '\n';
	Cache c(maxmem, evictor, std::hash<std::string>()); //create cache object
	std::string key = "a";
	char val[] = "z";
	uint32_t size = 1;
	c.set(key, val, size);	
	std::cout << c.get("b", size) << '\n';
	return 0;
}

//test: insert key and modify
int test_insert_and_mod()
{
	std::cout << "Insert key and modify value:" << '\n';
	Cache c(maxmem, evictor, std::hash<std::string>()); //create cache object
	std::string key = "a";
	char val[] = "z";
	char val2[] = "y";
	uint32_t size = 1;
	c.set(key, val, size);	
	std::cout << "Original value: " << c.get(key, size) << '\n';
	c.set(key, val2, size);
	std::cout << "New value: " << c.get(key, size) << '\n';
	return 0;

}
//test: insert key and delete
int test_insert_and_delete()
{
	std::cout << "Create cache and insert key:" << '\n';
	Cache c(maxmem, evictor, std::hash<std::string>()); //create cache object
	std::string key = "a";
	char val[] = "z";
	uint32_t size = 1;
	c.set(key, val, size);	
	std::cout << val << '\n';
	std::cout << "deleting... " << c.get(key, size) << '\n';
	c.del(key);
	return 0;
}

//test: query key that was evicted

int test_delete_and_query()
{
	std::cout << "Create cache and insert key:" << '\n';
	Cache c(maxmem, evictor, std::hash<std::string>()); //create cache object
	std::string key = "a";
	char val[] = "z";
	uint32_t size = 1;
	c.set(key, val, size);	
	std::cout << val << '\n';
	std::cout << "deleting... " << c.get(key, size) << '\n';
	c.del(key);
	std::cout << "access deleted val: " << c.get(key, size) << '\n';
	return 0;
}
int main() 
{
	test_insert();
	test_query();
	test_query_uninserted();
	test_insert_and_mod();
	test_insert_and_delete();
	test_delete_and_query();
	return 0;
}
