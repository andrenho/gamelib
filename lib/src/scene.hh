#ifndef SCENE_HH
#define SCENE_HH
#include <optional>

namespace gb {

struct Pen {
    uint8_t                  opacity;
    double                   angle;
    std::optional<SDL_Point> rotation_center {};
};

class Scene {

};

}

#endif //SCENE_HH
