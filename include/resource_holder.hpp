#ifndef __AIRPLANE_RESOURCE_HOLDER_HPP__
#define __AIRPLANE_RESOURCE_HOLDER_HPP__

#include <memory>
#include <map>
#include <string>
#include <stdexcept>
#include <cassert>

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
    void            Load(Identifier id, const std::string& filename);
    
    template <typename Parameter>
    void            Load(Identifier id, const std::string& filename, const Parameter& second_param);

    Resource&       Get(Identifier id);
    const Resource& Get(Identifier id) const;

private:
    void             InsertResource(Identifier id, std::unique_ptr<Resource> resource);

private:
    std::map<Identifier, std::unique_ptr<Resource>> resource_map_;
};


#include "resource_holder.inl"

#endif //__RESOURCE_HOLDER__
