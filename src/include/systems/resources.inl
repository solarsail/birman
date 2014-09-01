template <typename Resource, typename ID>
ResourceHolder<Resource, ID>::ResourceHolder() {}

template <typename Resource, typename ID>
ResourceHolder<Resource, ID>& ResourceHolder<Resource, ID>::get()
{
	static ResourceHolder<Resource, ID> self;
	return self;
}

template <typename Resource, typename ID>
void ResourceHolder<Resource, ID>::load(ID id, const std::string& filename)
{
    // Create and load Resource
    auto res = std::make_shared<Resource>();
    if (!res->loadFromFile(filename))
        throw std::runtime_error("[ResourceHolder::load] Failed to load " + filename);
    // Insert resource to map on successful load
    insert_resource(id, res);
}

template <typename Resource, typename ID>
template <typename Param>
void ResourceHolder<Resource, ID>::load(ID id, const std::string& filename, const Param& p)
{
    // Create and load Resource
    auto res = std::make_shared<Resource>();
    if (!res->loadFromFile(filename, p))
        throw std::runtime_error("[ResourceHolder::load(2)] Failed to load " + filename);
    // Insert resource to map on successful load
    insert_resource(id, res);
}

template <typename Resource, typename ID>
typename ResourceHolder<Resource, ID>::ResPtr ResourceHolder<Resource, ID>::get(ID id)
{
    auto found = _resource_map.find(id);
    assert(found != _resource_map.end());

    return found->second;
}

template <typename Resource, typename ID>
const typename ResourceHolder<Resource, ID>::ResPtr ResourceHolder<Resource, ID>::get(ID id) const
{
    auto found = _resource_map.find(id);
    assert(found != _resource_map.end());

    return found->second;
}

template <typename Resource, typename ID>
void ResourceHolder<Resource, ID>::insert_resource(ID id, ResPtr res)
{
    auto inserted = _resource_map.insert(std::make_pair(id, res));
    assert(inserted.second);
}
