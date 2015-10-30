#ifndef RESOURCE_CACHE_HPP
#define RESOURCE_CACHE_HPP

#include <map>
#include <memory>
#include <stdexcept>
#include <cassert>

template <typename Resource, typename Identifier>
class ResourceCache
{
public:
  void load( Identifier id, const sf::String& filename );
  template <typename Parameter>
  void load( Identifier id, const sf::String& filename, const Parameter& param );
  Resource& get( Identifier id );
  const Resource& get( Identifier id ) const;

private:
  void insertResource( Identifier id, std::unique_ptr<Resource> resource );
  std::map<Identifier, std::unique_ptr<Resource>> mResources;
};

#include "ResourceCache.inl"

#endif