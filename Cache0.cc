#include "cache.hh"
#include <unordered_map>
#include <vector>
#include <iostream>
 // Disallow cache copies, to simplify memory management.
//  Cache(const Cache&) = delete;
 // Cache& operator=(const Cache&) = delete;

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

  // Add a <key, value> pair to the cache.
  // If key already exists, it will overwrite the old value.
  // **********WHAT DOES THIS MEAN????????????????????????*********** Both the key and the value are to be deep-copied (not just pointer copied).
  // If maxmem capacity is exceeded, sufficient values will be removed
  // from the cache to accomodate the new value.
//  void set(key_type key, val_type val, index_type size);
        void set(key_type key, val_type val, index_type size)
        {
                //while (bytes_used + size >= maxmem)
                //{
                        //del(    ); OR Do I call some sort of evictor?
                        //Don't do the thing, evict? Del rand val?
                //}

                storage[key] = val;
                key_bytes[key] = size;
                bytes_used_ += size;


        }

  // Retrieve a pointer to the value associated with key in the cache,
  // or NULL if not found.
  // Sets the actual size of the returned value (in bytes) in val_size.
        val_type get(key_type key, index_type& val_size) const
        {
                // = key_bytes[key];
                //return storage[key];

                val_type val_at = storage.at(key);
                index_type actual_size = key_bytes.at(key);
                val_size = actual_size;
                return val_at;
        }

  // Delete an object from the cache, if it's still there
//  void del(key_type key);
        void del(key_type key)
        {
                index_type byte_size = key_bytes.at(key);
                bytes_used_ -= byte_size;
                storage.erase(key);
        }

  // Compute the total amount of memory used up by all cache values (not keys)
//  index_type space_used() const;
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
