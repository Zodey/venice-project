#include "imgui.h"

namespace c {
inline ImVec4 accent = ImColor(255, 255, 255, 255);

namespace background {
inline ImVec4 bg = ImColor(26, 26, 26, 255);
inline ImVec2 size = ImVec2(800, 460);
inline float rounding = 10.f;
}
namespace child {
inline ImVec4 bg = ImColor(32, 32, 32, 255);
inline ImVec4 border = ImColor(50, 50, 50, 255);
inline ImVec4 border_text = ImColor(105, 105, 105, 255);
inline float rounding = 10.f;
}
namespace tabs {
inline ImVec4 bg_active = ImColor(41, 41, 41, 255);
inline ImVec4 bg_hov = ImColor(38, 38, 38, 255);
inline ImVec4 bg = ImColor(0, 0, 0, 0);
inline ImVec4 i_bg_hov = ImColor(38, 38, 38, 255);
inline ImVec4 i_bg = ImColor(0, 0, 0, 0);
inline float rounding = 5.f;
}
namespace checkbox {
inline ImVec4 checkmark_active = ImColor(255, 255, 255, 255);
inline ImVec4 checkmark_inactive = ImColor(0, 0, 0, 0);
inline ImVec4 i_bg_hov = ImColor(45, 45, 45, 255);
inline ImVec4 i_bg = ImColor(32, 32, 32, 255);
inline float rounding = 3.f;
}
namespace slider {
inline ImVec4 circle = ImColor(255, 255, 255, 255);
inline ImVec4 i_bg_hov = ImColor(45, 45, 45, 255);
inline ImVec4 i_bg = ImColor(32, 32, 32, 255);
inline float rounding = 3.f;
}
namespace input_text {
inline ImVec4 i_bg_selected = ImColor(50, 50, 50, 255);
inline ImVec4 i_bg_hov = ImColor(45, 45, 45, 255);
inline ImVec4 i_bg = ImColor(32, 32, 32, 255);
inline float rounding = 4.f;
}
namespace keybind {
inline ImVec4 i_bg_hov = ImColor(45, 45, 45, 255);
inline ImVec4 i_bg = ImColor(32, 32, 32, 255);
inline float rounding = 4.f;
}
namespace combo {
inline ImVec4 i_bg_selected = ImColor(41, 41, 41, 255);
inline ImVec4 i_bg_hov = ImColor(45, 45, 45, 255);
inline ImVec4 i_bg = ImColor(28, 28, 28, 255);
inline float rounding = 3.f;
}
namespace selectable {
inline ImVec4 i_bg_hov = ImColor(45, 45, 45, 255);
inline ImVec4 i_bg = ImColor(32, 32, 32, 255);
inline float rounding = 3.f;
}
namespace scroll {
inline ImVec4 i_bg_hov = ImColor(90, 90, 90, 200);
inline ImVec4 i_bg = ImColor(60, 60, 60, 150);
inline float rounding = 3.f;
}
namespace picker {
inline ImVec4 i_bg = ImColor(20, 20, 20, 255);
inline float rounding = 3.f;
}
namespace button {
inline ImVec4 i_bg_hov = ImColor(45, 45, 45, 255);
inline ImVec4 i_bg = ImColor(28, 28, 28, 255);
inline float rounding = 4.f;
}
namespace text {
inline ImVec4 text_active = ImColor(255, 255, 255, 255);
inline ImVec4 text_hov = ImColor(180, 180, 180, 255);
inline ImVec4 text = ImColor(105, 105, 105, 255);
}
}