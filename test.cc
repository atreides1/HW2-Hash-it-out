#include "Cache0.cc"
#include <iostream>
#include <string>
uint32_t maxmem = 1024;

int evictor()
{
        return 0;
}


//test: create a cache and insert key
int test_insert()
{
        Cache c(maxmem, evictor, std::hash<std::string>()); //create cache object
        //string key = "a";
        //char * val = "z";
        //uint32_t size = 1;
        //c.set(key, val, size);
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
