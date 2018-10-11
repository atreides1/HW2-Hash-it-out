#include "Cache0.cc"
#include <iostream>

uint32_t maxmem = 1024;

void evictor()
{
}


//test: create a cache and insert key
int test_insert()
{
	//Cache c(maxmem, evictor, std::hash); //create cache object
	return 0;

}

//test: query key
//test: query key that wasn't inserted
//test: insert key and modify
//test: insert key and delete
//test: query key that was evicted

int main() 
{
	test_insert();
	return 0;
}
