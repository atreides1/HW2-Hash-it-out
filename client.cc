/*
Jillian James and Marika Swanberg
This is the implementation file for cache.hh called cache.cc

Run with the command:
g++ -Wall -Wextra -Werror -pedantic cache.cc test.cc -o test

On a machine using:
OS: Ubuntu 17.10
Memory: 3.9 GiB
Processor: Intel Core i5-7267U CPU @3.10GHz
OS Type: 64-bit
Disk 66.3 GB
*/




#include "cache.hh"
#include <cstring>
#include <iostream>
#include <unordered_map>
#include <tuple>

#include <pstream.h>
#include <string>
/*

int main()
{
} 
 */

struct Cache::Impl 
{
	index_type maxmem_;
	evictor_type evictor_;
	hash_func hasher_;
	index_type memused_;
	index_type newest_;
	std::unordered_map<std::string, std::tuple<val_type, index_type, index_type>> unorderedmap_;
	std::string servername;
	std::string portnum;

public:
	Impl(index_type maxmem, evictor_type evictor, hash_func hasher) 
	: maxmem_(maxmem), evictor_(evictor), hasher_(hasher), memused_(0), newest_(0), unorderedmap_()
	{

	}
	~Impl()
	{
		auto it = unorderedmap_.begin();
		while (it != unorderedmap_.end()) 
		{
			delete[] static_cast<const char*>(std::get<0>(it->second));
			it = unorderedmap_.erase(it);
		}
	}

	void set(key_type key, val_type val, index_type size)
	{
		//QUESTION: HOW DO I MAKE THESE BE STRINGS? DO I HAVE TO SPECIFY TYPE?
		std::string command = "curl -X PUT http://"+servername+":"+portnum+"/key/"+key+"/"+val;
		readwrite(command);
		return;
	}

	val_type get(key_type key, index_type& val_size) const 
	{
		return std::get<0>(entry);
	}
	
	// This deletes a (key, tuple) entry from the map
	void del(key_type key)
	{
		return;
	}

	index_type space_used() const
	{
		return memused_;
	}


	void evictor()
	{
	
	}

};

Cache::Cache(index_type maxmem,
        evictor_type evictor,
        hash_func hasher) 
	: pImpl_(new Impl(maxmem,evictor,hasher))
 {

}

Cache::~Cache(){
	// we don't need anything here because pimpl is a unique_ptr
}

// Add a <key, value> pair to the cache.
// If key already exists, it will overwrite the old value.
// Both the key and the value are to be deep-copied (not just pointer copied).
// If maxmem capacity is exceeded, sufficient values will be removed
// from the cache to accomodate the new value.
void Cache::set(key_type key, val_type val, index_type size){
	return pImpl_->set(key,val,size);
}

// Retrieve a pointer to the value associated with key in the cache,
// or NULL if not found.
// Sets the actual size of the returned value (in bytes) in val_size
Cache::val_type Cache::get(key_type key, index_type& val_size) const {
	return pImpl_->get(key,val_size);
}

// Delete an object from the cache, if it's still there
void Cache::del(key_type key){
	pImpl_->del(key);
}

// Compute the total amount of memory used up by all cache values (not keys)
Cache::index_type Cache::space_used() const {
	return pImpl_->space_used();
}

void readwrite (std::string command)
{

  // run a process and create a streambuf that reads its stdout and stderr
  redi::ipstream proc(command, redi::pstreams::pstdout | redi::pstreams::pstderr);
  std::string line;
  // read child's stdout
  while (std::getline(proc.out(), line))
    std::cout << "stdout: " << line << '\n';
  // read child's stderr
  while (std::getline(proc.err(), line))
    std::cout << "stderr: " << line << '\n';
}


