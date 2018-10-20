#include "cache.hh"
#include <unordered_map>
#include <vector>
#include <iostream>
#include <map>
// Disallow cache copies, to simplify memory management.
//  Cache(const Cache&) = delete;
// Cache& operator=(const Cache&) = delete;

struct Cache::Impl {
        index_type maxmem_;
        evictor_type evictor_;
        hash_func hasher_;
        index_type bytes_used_;
	
	hash_func new_hash = [](hash_func hasher) {if (hasher != NULL) { return hasher; } else { return std::function<uint32_t(key_type)>;}}; 
        std::unordered_map<std::string, const void*, hash_func> storage;
	std::map<std::string, uint32_t> key_bytes;
        Impl(index_type maxmem, evictor_type evictor, hash_func hasher)
        :maxmem_(maxmem), evictor_(evictor), hasher_(hasher), bytes_used_(0) 
        {	
		storage.max_load_factor(.5);
        }
        ~Impl() = default;

  // Add a <key, value> pair to the cache.
  // If key already exists, it will overwrite the old value.
  // **********WHAT DOES THIS MEAN????????????????????????*********** Both the key and the value are to be deep-copied (not just pointer copied).
  // If maxmem capacity is exceeded, sufficient values will be removed
  // from the cache to accomodate the new value.
        void set(key_type key, val_type val, index_type size)
        {
                while (bytes_used_ + size >= maxmem_)
                {
			evictor_();
                }
          

		storage[key] = val;
                key_bytes[key] = size;
                bytes_used_ += size;
		
		std::cout << "Inserting: Key: " << key << ", Value: " << val << '\n';

        }

  // Retrieve a pointer to the value associated with key in the cache,
  // or NULL if not found.
  // Sets the actual size of the returned value (in bytes) in val_size.
        val_type get(key_type key, index_type& val_size) const
        {
		if (storage.count(key) > 0)
		{
                	val_type val_at = storage.at(key);
                	index_type actual_size = key_bytes.at(key);
                	val_size = actual_size;
			std::cout << "Retrieving: Key: " << key << ", Value: " << val_at << '\n';
			return val_at;
		}
		else
		{
			std::cout << "Key: " << key << " not found." << '\n';
			return 0;	
		}
        }

  // Delete an object from the cache, if it's still there
        void del(key_type key)
        {
		if (storage.count(key) == 0)
		{
			std::cout << "Key not stored in cache." << '\n';
		}
		else
		{
			index_type byte_size = key_bytes.at(key);
                	bytes_used_ -= byte_size;
                	storage.erase(key);
                	key_bytes.erase(key);
			std::cout << "Key: " << key << " successfully deleted." << '\n';
        	}

	}

  // Compute the total amount of memory used up by all cache values (not keys)
        index_type space_used() const
        {
                return bytes_used_;
        }
};


// Create a new cache object with a given maximum memory capacity.
Cache::Cache(index_type maxmem,
        evictor_type evictor,
        hash_func hasher)

        :pImpl_(new Impl(maxmem, evictor, hasher))
{
}

Cache::~Cache()
{
}


  // Add a <key, value> pair to the cache.
  // If key already exists, it will overwrite the old value.
  // Both the key and the value are to be deep-copied (not just pointer copied).
  // If maxmem capacity is exceeded, sufficient values will be removed
  // from the cache to accomodate the new value.
void Cache::set(key_type key, val_type val, index_type size)
{

        pImpl_ ->set(key, val, size);
}

  // Retrieve a pointer to the value associated with key in the cache,
  // or NULL if not found.
  // Sets the actual size of the returned value (in bytes) in val_size.
Cache::val_type Cache::get(key_type key, index_type& val_size) const
{
        return pImpl_ ->get(key, val_size);
}

  // Delete an object from the cache, if it's still there
void Cache::del(key_type key)
{

        pImpl_ ->del(key);
}

  // Compute the total amount of memory used up by all cache values (not keys)
Cache::index_type Cache::space_used() const
{
        return pImpl_ ->space_used();

}
