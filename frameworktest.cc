#include "cache.hh"
#include <iostream>
#include <cassert>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

uint32_t maxmem = 1024;
uint32_t small_mem = 5;



TEST_CASE("test_space_used", "[Space Used]")
{
		
	Cache c(maxmem, std::hash<std::string>()); //create cache object
	std::string key = "a";
	std::string key1 = "b";
	char val[] = "z";
	uint32_t size = 1;
	c.set(key, val, size);	
	c.set(key1, val, size);
	REQUIRE(c.space_used()==2);

}


//test: create a cache and insert key
TEST_CASE("test_insert", "[Space Used]")
{
//	std::cout << "TEST: Create cache and insert key:" << '\n';
	Cache c(maxmem, std::hash<std::string>()); //create cache object
	std::string key = "a";
	char val[] = "z";
	uint32_t size = 1;
	c.set(key, val, size);	
	REQUIRE(c.space_used() == 1);
}

//test: query key
TEST_CASE("query key", "[Query]")
{
//	std::cout << "TEST: Query key:" << '\n';
	Cache c(maxmem, std::hash<std::string>()); //create cache object
	std::string key = "a";
	char val[] = "z";
	uint32_t size = 1;
	c.set(key, val, size);	
	REQUIRE(&val == c.get(key, size));

}
//test: query key that wasn't inserted
TEST_CASE("query_uninserted_key", "[Query]")
{
//	std::cout << "TEST: Query key that wasn't inserted:" << '\n';
	Cache c(maxmem, std::hash<std::string>()); //create cache object
	std::string key = "a";
	char val[] = "z";
	uint32_t size = 1;
	c.set(key, val, size);	
	REQUIRE(&val != c.get("b", size));
}

//test: insert key and modify
TEST_CASE("Modify_stored_value", "[Set]")
{
//	std::cout << "TEST: Insert key and modify value:" << '\n';
	Cache c(maxmem, std::hash<std::string>()); //create cache object
	std::string key = "a";
	char val[] = "z";
	char val2[] = "y";
	uint32_t size = 1;
	c.set(key, val, size);	
        c.get(key, size);
	c.set(key, val2, size);
	REQUIRE(&val2 == c.get(key, size));

}
//test: insert key and delete
TEST_CASE("Delete Key", "[Delete]")
{
//	std::cout << "TEST: Create cache and delete key:" << '\n';
	Cache c(maxmem, std::hash<std::string>()); //create cache object
	std::string key = "a";
	char val[] = "z";
	uint32_t size = 1;
	c.set(key, val, size);	
	c.get(key, size);
	c.del(key);
	REQUIRE(c.space_used() == 0);
}

//test: query key that was evicted
TEST_CASE("Query  doesn't mod memused", "[Space Used]")
{
//	std::cout << "TEST: Create cache and check for deleted value:" << '\n';
	Cache c(maxmem, std::hash<std::string>()); //create cache object
	std::string key = "a";
	char val[] = "z";
	uint32_t size = 1;
	c.set(key, val, size);	
	c.get(key, size);
	c.del(key);
	c.get(key, size);
	REQUIRE(c.space_used() == 0);
}

//test: try deleting a key that wasn't inserted
TEST_CASE("Empty del doesn't mod memused", "[Space Used]")
{
//	std::cout << "TEST: Create cache and delete an uninserted key:" << '\n';
	Cache c(maxmem, std::hash<std::string>()); //create cache object
	std::string key = "a";
	c.del(key);
	REQUIRE(c.space_used() == 0);
}


//test: overfill cache mem in order to use the FIFO Evictor 
TEST_CASE("test_evict", "[Evict]")
{
//	std::cout << "TEST: FIFO Eviction:" << '\n' << "The cache has a size of 5 bytes" << '\n';
	Cache c(small_mem, std::hash<std::string>()); //create cache object
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
	c.get(key, size);	
	REQUIRE(c.space_used() == 4);

}
