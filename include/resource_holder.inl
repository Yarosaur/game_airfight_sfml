
template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::Load(Identifier id, const std::string& filename)
{
	// Create and load resource
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceHolder::Load - Failed to load " + filename);

	// If loading successful, insert resource to map
	InsertResource(id, std::move(resource));
}


template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::Load(Identifier id,
     const std::string& filename, const Parameter& second_param)
{
	// Create and load resource
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename, second_param))
		throw std::runtime_error("ResourceHolder::Load - Failed to load " + filename);

	// If loading successful, insert resource to map
	InsertResource(id, std::move(resource));
}


template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::Get(Identifier id)
{
	auto found {resource_map_.find(id)};
	assert(found != resource_map_.end());

	return *found->second;
}


template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::Get(Identifier id) const
{
	auto found {resource_map_.find(id)};
	assert(found != resource_map_.end());

	return *found->second;
}


template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::InsertResource(Identifier id, std::unique_ptr<Resource> resource) 
{
	// Insert and check success
	auto inserted {resource_map_.insert(std::make_pair(id, std::move(resource)))};
	assert(inserted.second);
}
