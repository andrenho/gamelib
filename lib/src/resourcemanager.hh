#ifndef RESOURCEMANAGER_HH
#define RESOURCEMANAGER_HH

#include <SDL3/SDL.h>

#include <cstdint>
#include <unordered_map>
#include <variant>
#include <vector>

namespace gb { class ResourceManager; }; gb::ResourceManager& R();  // forward declaration

namespace gb {

using resource_idx_t = size_t;
using Resource = std::variant<SDL_Texture*, /*Tile,*/ SDL_Cursor*>;

class ResourceManager {
public:
    ~ResourceManager();
    // void cleanup();

    resource_idx_t add_texture(std::vector<uint8_t> const& data);
    void           add_texture(std::string const& name, std::vector<uint8_t> const& data);

private:
    ResourceManager() = default;
    friend ResourceManager& ::R();

    std::unordered_map<std::string, Resource> resources_str_;
    std::vector<Resource> resources_idx_;

    static SDL_Texture* create_texture(std::vector<uint8_t> const& data);
};

} // gb

#endif //RESOURCEMANAGER_HH
