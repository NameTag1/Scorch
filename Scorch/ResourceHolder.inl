#include "ResourceHolder.hpp"
#include "DataTable.h"

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	//Prevent loading same resource twice
	if (resourceMap.find(id) != resourceMap.end())
		return;

	// Create and load resource
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

	// If loading successful, insert resource to map
	insertResource(id, std::move(resource));
}

template<typename Resource, typename Identifier>
inline void ResourceHolder<Resource, Identifier>::load(std::string id, const std::string& filename)
{
	//Prevent loading same resource twice
	if (mResourceMap.find(id) != mResourceMap.end())
		return;

	// Create and load resource
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

	// If loading successful, insert resource to map
	insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& secondParam)
{
	//Prevent loading same resource twice
	if (resourceMap.find(id) != resourceMap.end())
		return;
	
	// Create and load resource
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename, secondParam))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

	// If loading successful, insert resource to map
	insertResource(id, std::move(resource));
}

template<typename Resource, typename Identifier>
template<typename Parameter>
inline void ResourceHolder<Resource, Identifier>::load(std::string id, const std::string& filename, const Parameter& secondParam)
{
	//Prevent loading same resource twice
	if (mResourceMap.find(id) != resourceMap.end())
		return;

	// Create and load resource
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

	// If loading successful, insert resource to map
	insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	auto found = resourceMap.find(id);
	assert(found != resourceMap.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
	auto found = resourceMap.find(id);
	assert(found != resourceMap.end());

	return *found->second;
}

template<typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(std::string id)
{
	auto found = mResourceMap.find(id);
	/*if (found != resourceMap.end()) {
		load(id, DATATABLE::RESOURCE_LOCATIONS["id"]);

		found = mResourceMap.find(id);
		assert(found != resourceMap.end());
	}*/

	return *found->second;
}

template<typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(std::string id) const
{
	auto found = mResourceMap.find(id);
	assert(found != resourceMap.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insertResource(Identifier id, std::unique_ptr<Resource> resource) 
{
	// Insert and check success
	auto inserted = resourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insertResource(std::string id, std::unique_ptr<Resource> resource)
{
	// Insert and check success
	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}
