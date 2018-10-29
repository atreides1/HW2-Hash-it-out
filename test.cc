#include "cache.hh"
#include <iostream>
#include <cassert>

uint32_t maxmem = 1024;
uint32_t small_mem = 5;

int evictor()
{
	return 0;	
}


//Just a utility func to insert a new line
void insert_line()
{
	std::cout << '\n';
}


//test: create a cache and check space_used 
int test_space_used()
{
	std::cout << "TEST: Create cache and check space used is updating:" << '\n';
	Cache c(maxmem, evictor, std::hash<std::string>()); //create cache object
	assert(c.space_used() == 0);
	std::string key = "a";
	std::string key1 = "b";
	char val[] = "z";
	uint32_t size = 1;
	c.set(key, val, size);	
	std::cout << "Space used after inserting: " << c.space_used() << '\n'; 
	assert(c.space_used() == 1);
	c.set(key1, val, size);
	assert(c.space_used() == 2);
	std::cout << "Space used after inserting: " << c.space_used() << '\n'; 
	insert_line();
	return 0;

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
	assert(c.space_used() == 1);
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
	assert(&val == c.get(key, size));
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
	assert(&val != c.get("b", size));
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
	assert(&val2 == c.get(key, size));
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
	std::cout << "deleting... "; 
	c.get(key, size);
	c.del(key);
	assert(c.space_used() == 0);
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
	assert(c.space_used() == 0);
	insert_line();
	return 0;
}

//test: try deleting a key that wasn't inserted
int test_delete_uninserted()
{
	std::cout << "TEST: Create cache and delete an uninserted key:" << '\n';
	Cache c(maxmem, evictor, std::hash<std::string>()); //create cache object
	std::string key = "a";
	std::cout << "deleting... "; 
	c.del(key);
	assert(c.space_used() == 0);
	insert_line();
	return 0;
}


//test: overfill cache mem in order to use the FIFO Evictor 
int test_evict()
{
	std::cout << "TEST: FIFO Eviction:" << '\n' << "The cache has a size of 5 bytes" << '\n';
	Cache c(small_mem, evictor, std::hash<std::string>()); //create cache object
	std::string key = "a";
	std::string key1 = "b";
	std::string key2 = "c";
	std::string key3 = "d";
	std::string key4 = "e";
	char val[] = "z";
	uint32_t size = 1;
	c.set(key, val, size);	
	c.set(key1, val, size);	
	c.set(key2, val, size);	
	c.set(key3, val, size);	
	c.set(key4, val, size);
	std::cout << "Attempting to retrieve evicted key 'a'..." << '\n';	
	c.get(key, size);	
	assert(c.space_used() == 4);
	insert_line();
	return 0;

}
int main() 
{
	insert_line();
	test_space_used();
	test_insert();
	test_query();
	test_query_uninserted();
	test_insert_and_mod();
	test_insert_and_delete();
	test_delete_and_query();
	test_delete_uninserted();
	test_evict();
	return 0;
}
