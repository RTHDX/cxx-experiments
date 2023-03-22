#include <vector>
#include <iostream>
#include <thread>
#include <ranges>
#include <cassert>

#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/string_cast.hpp>

using path_t = std::vector<glm::vec3>;
struct segment_t { size_t start, end; };

bool operator == (const segment_t& lhs, const segment_t& rhs) {
    return lhs.start == rhs.start && lhs.end == rhs.end;
}

segment_t g_segment;


segment_t get_current_segment(const path_t& path, size_t i) {
    if (i > path.size() - 2) { assert(false); }

    return {.start = i, .end = i + 1};
}

glm::vec3 lerp(const glm::vec3& start, const glm::vec3& end, float f) {
    glm::vec3 dir = glm::normalize(end - start);
    return start + f * dir;
}

int main() {
    glm::vec4 point {0.0, 0.0, 0.0, 1.0};

    path_t path {
        {0.0, 0.0, 0.0},
        {0.0, 0.0, 1.0},
        {1.0, 0.0, 1.0},
        {1.0, 0.0, 2.0},
        {2.0, 0.0, 2.0}
    };

    float factor = 0.0f;
    float speed  = 0.1f;
    size_t i = 0;
    glm::mat4 model(1.0);

    while (i != path.size() - 1) {
        segment_t current = get_current_segment(path, i);
        if (current != g_segment) {
            g_segment = current;
            std::cout << "Segment changed!" << std::endl;
        }
        auto pos = lerp(path[current.start], path[current.end], factor);
        model = glm::translate(glm::mat4(1.0), pos);
        auto mod_pos = model * point;
        std::cout << "Current position: " << glm::to_string(pos) << std::endl;
        std::cout << "Modified point: " << glm::to_string(mod_pos) << std::endl;
        if (factor + speed > 1.0) {
            factor = 0.0f;
            ++i;
        } else {
            factor += speed;
        }
    }
}
