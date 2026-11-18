#pragma once

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <map>

#include "../ImGui/imgui.h"
#include "../ImGui/imgui_internal.h"

extern ImFont* phobia_font;
extern ImFont* phobia_big_font;
extern ImFont* phobia_icon_font;
extern ImFont* phobia_title_font;

namespace phobia
{
bool selected(const char* label, bool tab = false);
bool render_tab(const char* icon, const char* label, bool selected);
bool menu_child(const char* name, const ImVec2& size_arg, bool border = false, ImGuiWindowFlags flags = 0);
void add_colored_text(ImDrawList* draw, const ImVec2& pos, ImU32 color1, ImU32 color2, const char* text);

bool checkbox(const char* label, bool* v);
bool keybind(const char* label, int* key);
bool slider(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format);
bool slider_int(const char* label, int* v, int v_min, int v_max, const char* format);
bool slider_float(const char* label, float* v, float v_min, float v_max, const char* format);
}
