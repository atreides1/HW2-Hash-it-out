#include "cache.hh"
//Everything is deferred to Impl
//You can't start by putting all your data into a big array then hashing into. 
//Put all your data in an unordered map - gives you the hashing that you need to test with
struct Cache::Impl {
  index_type maxmem_;
  evictor_type evictor_type;
  hash_func hasher_;
  index_type memused_;
    Impl(index_type maxmem, evictor_type evictor, hash_func hasher)
        :maxmem_(maxmem), evictor_(evictor), hasher_(hasher), memused_(0)
    {
    }
    ~Impl() = default;
    void set(key_type key, val_type val, index_type size)
    {
    }
    val_type Cache::get(key_type key, index_type& val_size) const
    {
    }
    void del(key_type key)
    {
    }
    index_type Cache::space_used() const
    {
    }

};

Cache::Cache(index_type maxmem,
      evictor_type evictor,
      hash_func hasher);
  : pImpl_(new Impl(maxmem, evictor, hasher))
{
//Not allowed to assign to a unique pointer. Need to initialize data members
}

Cache::~Cache();
{

}
// Disallow cache copies, to simplify memory management.

void Cache::set(key_type key, val_type val, index_type size);
{
    pImpl_->set(key,val,size);  //Pointer to implementation- same as *pImpl.___
}
// Retrieve a pointer to the value associated with key in the cache,
// or NULL if not found.
// Sets the actual size of the returned value (in bytes) in val_size.
Cache::val_type Cache::get(key_type key, index_type& val_size) const;
{
    return pImpl_->get(key,size);
}
// Delete an object from the cache, if it's still there
void Cache::del(key_type key);
{
    pImpl_->del(key);
}
// Compute the total amount of memory used up by all cache values (not keys)
Cache::index_type Cache::space_used() const;
{
   return pImpl_->space_used();
}
