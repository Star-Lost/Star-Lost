#pragma once

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

	static bool load(const std::string &name, ResourceType &out)
	{
		// By default, assume the resource is an SFML object
		return out.loadFromFile(name);
	}
};