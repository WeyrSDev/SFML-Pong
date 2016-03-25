#ifndef CORE_RESOURCECACHE_HPP
#define CORE_RESOURCECACHE_HPP

#include <map>
#include <memory>
#include <stdexcept>
#include <cassert>
#include <type_traits>

namespace core
{

template <typename Resource, typename Identifier>
class ResourceCache
{
public:
  explicit ResourceCache( LogSystem* log ) 
    : mLog( log )
  {
    if( mLog != nullptr ) {
//      mLog->write( "Starting Resource Cache for " + std::string( typeid( Resource ).name() ),
//                   LogType::DEBUG );
    }
  }

  void load( Identifier id, const sf::String& filename );
  template <typename Parameter>
  void load( Identifier id, const sf::String& filename, const Parameter& param );
  Resource& get( Identifier id );
  const Resource& get( Identifier id ) const;

private:
  void insertResource( Identifier id, std::unique_ptr<Resource> resource );
  std::map<Identifier, std::unique_ptr<Resource>> mResources;
  LogSystem* mLog;
};

#include "ResourceCache.inl"

} // end namespace core

#endif