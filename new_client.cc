#include "cache.hh"
#include <cstring>
#include <iostream>
#include <unordered_map>
#include <tuple>
#include <stdio.h>
#include <curl/curl.h>

#include <cstring>

const char* url_get_k = "http://0.0.0.0:18080/key/";
const char* url_put_k_v = "http://0.0.0.0:18080/key/";
const char* url_delete_k = "http://0.0.0.0:18080/key/";
const char* url_head_k = "http://0.0.0.0:18080/key/";
const char* url_get_memsize = "http://0.0.0.0:18080/memsize";
const char* url_post = "http://0.0.0.0:18080/shutdown";

struct Cache::Impl 
{
	index_type maxmem_;
	hash_func hasher_;
	index_type memused_;
	index_type newest_;
	std::unordered_map<std::string, std::tuple<val_type, index_type, index_type>> unorderedmap_;

	CURL* curl_;
public:
	Impl(index_type maxmem, hash_func hasher) 
	: maxmem_(maxmem), hasher_(hasher), memused_(0), newest_(0), unorderedmap_(),
	curl_(curl_easy_init())
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

	int set(key_type key, val_type val, index_type size)
	{
		return 0;
	}

	val_type get(key_type key, index_type& val_size) const 
	{
/*                std::tuple<val_type, index_type, index_type> entry;
                try{
                        entry = unorderedmap_.at(key);
                } catch(const std::out_of_range& oor) {
                        val_size = 0;   // set val_size to 0 if we don't find the value
                        return NULL;
                }

                val_size = std::get<1>(entry);

*/              
		std::string get_key = url_get_k + key;
		char * cstr = new char [get_key.length()+1];
		std::strcpy (cstr, get_key.c_str());

		if(curl_) 
  		{
    			curl_easy_setopt(curl_, CURLOPT_URL, cstr);
    /* example.com is redirected, so we tell libcurl to follow redirection */ 
   			//curl_easy_setopt(curl_, CURLOPT_FOLLOWLOCATION, 1L);
 
    /* Perform the request, res will get the return code */ 
   			auto res = curl_easy_perform(curl_);
    /* Check for errors */ 
    			if(res != CURLE_OK)
				fprintf(stderr, "curl_easy_perform() failed: %s\n",
             			curl_easy_strerror(res));
 
    /* always cleanup */ 
    			curl_easy_cleanup(curl_);
  		}
		return 0;

	}
	// This deletes a (key, tuple) entry from the map
	int del(key_type key)
	{
		return 0;
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
        hash_func hasher) 
	: pImpl_(new Impl(maxmem,hasher))
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
int Cache::set(key_type key, val_type val, index_type size)
{
	return pImpl_->set(key,val,size);
}

// Retrieve a pointer to the value associated with key in the cache,
// or NULL if not found.
// Sets the actual size of the returned value (in bytes) in val_size
Cache::val_type Cache::get(key_type key, index_type& val_size) const 
{
        return pImpl_->get(key,val_size);
}


// Delete an object from the cache, if it's still there
int Cache::del(key_type key)
{
	return pImpl_->del(key);
}

// Compute the total amount of memory used up by all cache values (not keys)
Cache::index_type Cache::space_used() const 
{
	return pImpl_->space_used();
}
