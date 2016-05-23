#pragma once
#include <map>
#include <string>

extern const std::string thirdparty_resource_path;
extern const std::string internal_resource_path;

template<typename ResourceType>
class resource;

// This type is used for preprocessing certain resources
// like for instance replacing magenta colors in textures
// with transparency. The default implementation
// does nothing at all, except basic loading
template<typename ResourceType>
class resource_loader
{
	friend class resource<ResourceType>;
	static const std::string path;

	static bool load_internally(const std::string &name, ResourceType &out)
	{
		return out.loadFromFile(name);
	}
};

// This class when instantiated becomes a cache of the ResourceType type
// and can be used to look up or load resources of that type.
// Internally it uses resource_loader to provide resource type specific
// preprocessing.
// ResourceType can be an sf::Sound or an sf::Texture for instance
template<typename ResourceType>
class resource
{
	bool load_internally(const std::string &name, ResourceType &out) const
	{
		return resource_loader<ResourceType>::load_internally(name, out);
	}

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
		auto new_entry = resources.emplace(name, ResourceType{}).first;

		// Prepend the type-specific resource path like Images\\ for sf::Textures
		auto specific_path = resource_loader<ResourceType>::path + name;

		// Try to load from our internal resources
		if (load_internally(internal_resource_path + specific_path, new_entry->second))
			return &new_entry->second;

		// .. If that fails, try third party resources
		if (load_internally(thirdparty_resource_path + specific_path, new_entry->second))
			return &new_entry->second;

		// Didn't find nothin
		return nullptr;
	}

private:
	std::map<std::string, ResourceType> resources;
};

// This is type-specific resource loading code.
// It specifically replaces magenta colors with transparency
// in all textures when loaded
template<>
class resource_loader<sf::Texture>
{
	friend class resource<sf::Texture>;

	static const std::string path;
	static bool load_internally(const std::string &name, sf::Texture &out)
	{
		sf::Image img;
		if (!img.loadFromFile(name))
			return false;
		// Replace magenta with transparency
		img.createMaskFromColor(sf::Color{ 255, 0, 255, 255 });

		return out.loadFromImage(img);
	}
};