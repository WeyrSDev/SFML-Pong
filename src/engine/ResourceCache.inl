
template <typename Resource, typename Identifier>
void ResourceCache<Resource, Identifier>::load( Identifier id, const sf::String& filename )
{
  // Create and load resource
  auto resource = std::make_unique<Resource>();
  if( !resource->loadFromFile( filename ) )
    throw std::runtime_error( "ResourceCache::load - Failed to load " + filename );

  // If loading successful, insert resource to map
  insertResource( id, std::move( resource ) );
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceCache<Resource, Identifier>::load( Identifier id, const sf::String& filename, const Parameter& secondParam )
{
  // Create and load resource
  auto resource = std::make_unique<Resource>();
  if( !resource->loadFromFile( filename, secondParam ) )
    throw std::runtime_error( "ResourceCache::load - Failed to load " + filename );

  // If loading successful, insert resource to map
  insertResource( id, std::move( resource ) );
}

template <typename Resource, typename Identifier>
Resource& ResourceCache<Resource, Identifier>::get( Identifier id )
{
  auto found = mResources.find( id );
  assert( found != mResources.end() );

  return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceCache<Resource, Identifier>::get( Identifier id ) const
{
  auto found = mResources.find( id );
  assert( found != mResources.end() );

  return *found->second;
}

template <typename Resource, typename Identifier>
void ResourceCache<Resource, Identifier>::insertResource( Identifier id, std::unique_ptr<Resource> resource )
{
  // Insert and check success
  // TODO already inserted resources fire assertion, fix with checking first then insert if not present
  auto inserted = mResources.insert( std::make_pair( id, std::move( resource ) ) );
  assert( inserted.second );
}
