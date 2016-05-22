#pragma once
#include <map>
#include <string>

static const std::string thirdparty_resource_path = "..\\..\\Resources\\";
static const std::string internal_resource_path = "..\\..\\..\\Resources\\";

// Pre-declaration, check bottom of file for implementation
template<typename ResourceType>
struct get_resource_folder
{
	static std::string path() { return ""; }
};

// ResourceType is sf::Sound or an sf::Texture for instance
template<typename ResourceType>
class resource
{
public:
	const ResourceType *get_resource(const std::string &name) const
	{
		auto lookup = resources.find(name);
		if (lookup == resources.cend())
			return nullptr;

		return &(lookup->second);
	}

	const ResourceType *load_resource(const std::string &name)
	{
		// Check if this resource already exists first
		auto cache = get_resource(name);
		if (cache != nullptr)
			return cache;

		// Create our new entry and get the iterator to it
		// so we can delete it later, if we have to, and also
		// load resources directly into it
		auto newentry = resources.emplace(name, ResourceType{}).first;

		// Prepend the type-specific resource path like Images\\ for sf::Textures
		auto specific_path = get_resource_folder<ResourceType>::path() + name;

		// Try to load from our internal 
		if (newentry->second.loadFromFile(internal_resource_path + specific_path))
			return &newentry->second;

		// .. If that fails, try third party resources
		if (newentry->second.loadFromFile(thirdparty_resource_path + specific_path))
			return &newentry->second;

		// Didn't find nothin
		return nullptr;
	}

private:
	std::map<std::string, ResourceType> resources;
};

// This structure lets us associate types
// with sub-folders in the Resources folders
template<>
struct get_resource_folder<sf::Texture>
{
	static std::string path() { return "Images\\"; }
};

template<>
struct get_resource_folder<sf::SoundBuffer>
{
	static std::string path() { return "Sounds\\"; }
};