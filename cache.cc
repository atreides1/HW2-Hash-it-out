#include "cache.hh"

class Cache::Impl {
 public:
  int value_;
};

Cache::Cache()
: pimpl_(new Impl())
{
  pimpl_->value_ = 56;
}


Cache::Cache(Cache::index_type maxmem,
             Cache::evictor_type evictor = [](){ return 0; },
             Cache::hash_func hasher = std::hash<std::string>());

Cache::~Cache()
{
}

//
void Cache::set(Cache::key_type key, Cache::val_type val, Cache::index_type size)
{

}
Cache::val_type Cache::get(Cache::key_type key) const
{

}
void Cache::del(Cache::key_type key)
{

}

Cache::index_type Cache::space_used() const
{

}
