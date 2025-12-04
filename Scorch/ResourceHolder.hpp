#ifndef Resource_Holder_hpp
#define Resource_Holder_hpp

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>


template <typename Resource, typename Identifier>
class ResourceHolder
{
	public:
		void						load(Identifier id, const std::string& filename);
		template <typename Parameter>
		void						load(Identifier id, const std::string& filename, const Parameter& secondParam);
		
		void						load(std::string id, const std::string& filename);
		template <typename Parameter>
		void						load(std::string id, const std::string& filename, const Parameter& secondParam);

		Resource&					get(Identifier id);
		const Resource&				get(Identifier id) const;

		Resource&					get(std::string id);
		const Resource&				get(std::string id) const;


	private:
		void						insertResource(Identifier id, std::unique_ptr<Resource> resource);
		void						insertResource(std::string id, std::unique_ptr<Resource> resource);


	private:
		std::map<Identifier, std::unique_ptr<Resource>>	resourceMap;
		std::map<std::string, std::unique_ptr<Resource>> mResourceMap;
};

#include "ResourceHolder.inl"
#endif 
