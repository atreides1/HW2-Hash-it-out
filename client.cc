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
const char* url_del_k = "http://0.0.0.0:18080/key/";
const char* url_head_k = "http://0.0.0.0:18080/key/k";
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
		//size not used, throws warning 
	{
		//convert val (void *) to string
	
	/*	
		char *char_val = (char*) (val);
		std::string str_val(char_val);
		std::string set_kv = url_put_k_v + key + "/" + str_val;
		char * setstr = new char [set_kv.length()+1];
		std::strcpy (setstr, set_kv.c_str());
		if(curl_)
	       	{
			//auto headers = curl_slist_append(headers, client_id_header);
    			//auto headers = curl_slist_append(headers, "Content-Type: application/json");

    			//curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, headers); 
    			curl_easy_setopt(curl_, CURLOPT_URL, setstr);  
    			curl_easy_setopt(curl_, CURLOPT_CUSTOMREQUEST, "PUT"); 

    			//curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, json_struct); 
	
    			auto res = curl_easy_perform(curl_);

    			
			if (res != CURLE_OK)
				fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));	
			//curl_slist_free_all(headers);
    			curl_easy_cleanup(curl_);

 
		}
		curl_global_cleanup(); 
	*/	
		return 0;
	}


	val_type get(key_type key, index_type& val_size) const 
	{
		//val_size not used, throws warning
		
		//converting params to a char * since that what lib-curl takes as a url
		std::string get_key = url_get_k + key;
		char * cstr = new char [get_key.length()+1];
		std::strcpy (cstr, get_key.c_str());

		if(curl_) 
  		{
    			curl_easy_setopt(curl_, CURLOPT_URL, cstr);
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
		std::string del_key = url_del_k + key;
		char * delstr = new char [del_key.length()+1];
		std::strcpy (delstr, del_key.c_str());
		if(curl_)
		{

			curl_easy_setopt(curl_, CURLOPT_CUSTOMREQUEST, "DELETE");
			curl_easy_setopt(curl_, CURLOPT_URL, delstr);
			curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, "{\"key\": \"value\"}");
			struct curl_slist *headers = NULL;

			headers = curl_slist_append(headers, "content-type: application/json");
			curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, headers);
			CURLcode ret = curl_easy_perform(curl_);
			if (ret != CURLE_OK)
				fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(ret));	
			curl_slist_free_all(headers);
			curl_easy_cleanup(curl_);
		}
		return 0;
	}

	index_type space_used() const
	{

		if(curl_) 
  		{
    			curl_easy_setopt(curl_, CURLOPT_URL, url_get_memsize);
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
		return memused_; 
	}


	void shutdown()
	{
	
		if(curl_)
		{
			curl_easy_setopt(curl_, CURLOPT_URL, url_post);
    			/* Now specify the POST data */
    			curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, "{\"key\": \"value\"}");

    			/* Perform the request, res will get the return code */
    			auto res = curl_easy_perform(curl_);
    			/* Check for errors */
    			if(res != CURLE_OK)
      				fprintf(stderr, "curl_easy_perform() failed: %s\n",
              				curl_easy_strerror(res));

    			/* always cleanup */
    			curl_easy_cleanup(curl_);
		}
	}

	void head()
	{
	if(curl_) {
  		curl_easy_setopt(curl_, CURLOPT_URL, url_head_k);
 
  		/* get us the resource without a body! */
  		curl_easy_setopt(curl_, CURLOPT_NOBODY, 1L);
 
  		/* Perform the request */
  		curl_easy_perform(curl_);
		}		
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
