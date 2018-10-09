#include "cache.hh"
#include <unordered_map>
#include <vector>
#include <iostream>
struct Cache::Impl {
        index_type maxmem_;
        evictor_type evictor_;
        hash_func hasher_;
        index_type bytes_used_;

        std::unordered_map<std::string, const void*> storage;

        std::unordered_map<std::string, uint32_t> key_bytes;
        //std::vector<key_type> keys_;
        //std::vector<val_type> values_;
        //std::vector<index_type> sizes_;

        Impl(index_type maxmem, evictor_type evictor, hash_func hasher)
        :maxmem_(maxmem), evictor_(evictor), hasher_(hasher), bytes_used_(0)
        {

        }
        ~Impl() = default;
        //declare funcs again

        void set(key_type key, val_type val, index_type size)
        {
                //code to save key, value, and size somewhere
                storage[key] = val;
                key_bytes[key] = size;
                bytes_used_ += size;


        }

        val_type get(key_type key, index_type& val_size) const
        {
                //val_size = key_bytes[key];
                return storage[key];
        }

        void del(key_type key)
        {


        }

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
