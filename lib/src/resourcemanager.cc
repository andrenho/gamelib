#include "resourcemanager.hh"

#include <SDL3_image/SDL_image.h>

#include "ui.hh"


namespace gb {

ResourceManager::~ResourceManager()
{
    // cleanup();
}

SDL_Texture* ResourceManager::create_texture(std::vector<uint8_t> const& data)
{
    SDL_IOStream* stream = SDL_IOFromMem((void *) data.data(), (int) data.size());
    return IMG_LoadTexture_IO(::U().ren(), stream, true);
}

resource_idx_t ResourceManager::add_texture(std::vector<uint8_t> const& data)
{
    resources_idx_.emplace_back(create_texture(data));
    return resources_idx_.size() - 1;
}

void ResourceManager::add_texture(std::string const& name, std::vector<uint8_t> const& data)
{
    /*
    auto it = resources_str_.find(name);
    if (it != resources_str_.end())
        throw std::runtime_error("There's already a resource called `" + name + "`");
    */

    resources_str_.emplace(name, create_texture(data));
}

} // gb

gb::ResourceManager& R()
{
    static gb::ResourceManager res;
    return res;
}
