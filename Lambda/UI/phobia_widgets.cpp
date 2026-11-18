#define IMGUI_DEFINE_MATH_OPERATORS
#include "phobia_widgets.h"
#include "phobia_globals.h"
#include <Windows.h>

#pragma warning (disable : 4244)

struct tab_anim
{
float label_anim;
float hovered_anim;
float active_anim;
};

bool phobia::selected(const char* label, bool tab)
{
ImGuiWindow* window = ImGui::GetCurrentWindow();
if (window->SkipItems)
return false;

ImGuiContext& g = *GImGui;
const ImGuiStyle& style = g.Style;
const ImGuiID id = window->GetID(label);
const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
ImVec2 pos = window->DC.CursorPos;

const ImRect rect(pos, ImVec2(pos.x + label_size.x, pos.y + label_size.y));
ImGui::ItemSize(ImVec4(rect.Min.x, rect.Min.y, rect.Max.x, rect.Max.y), style.FramePadding.y);
if (!ImGui::ItemAdd(rect, id))
return false;

bool hovered, held;
bool pressed = ImGui::ButtonBehavior(rect, id, &hovered, &held, 0);

static std::map <ImGuiID, tab_anim> anim;
auto it_anim = anim.find(id);
if (it_anim == anim.end())
{
anim.insert({ id, {0.6f, 0.f, 0.f} });
it_anim = anim.find(id);
}

it_anim->second.label_anim = ImLerp(it_anim->second.label_anim, tab ? 0.0f : 0.6f, 0.05f * (1.0f - ImGui::GetIO().DeltaTime));
it_anim->second.hovered_anim = ImLerp(it_anim->second.hovered_anim, hovered ? 0.2f : 0.0f, 0.03f * (1.0f - ImGui::GetIO().DeltaTime));
it_anim->second.active_anim = ImLerp(it_anim->second.active_anim, tab ? 1.0f : 0.0f, 0.08f * (1.0f - ImGui::GetIO().DeltaTime));

window->DrawList->AddText(ImVec2((rect.Min.x + rect.Max.x) / 2.f - (label_size.x / 2.f), (rect.Min.y + rect.Max.y) / 2.f - (label_size.y / 2.f)), ImColor(1.0f, 1.0f, 1.0f, it_anim->second.label_anim + it_anim->second.hovered_anim), label);
window->DrawList->AddText(ImVec2((rect.Min.x + rect.Max.x) / 2.f - (label_size.x / 2.f), (rect.Min.y + rect.Max.y) / 2.f - (label_size.y / 2.f)), ImColor(accent_colour[0], accent_colour[1], accent_colour[2], it_anim->second.active_anim), label);

return pressed;
}

bool phobia::render_tab(const char* icon, const char* label, bool selected)
{
ImGuiWindow* window = ImGui::GetCurrentWindow();
if (window->SkipItems)
return false;

ImGuiContext& g = *GImGui;
const ImGuiID id = window->GetID(icon);
ImGui::CalcTextSize(icon);

ImVec2 pos = window->DC.CursorPos;
ImVec2 size = { 135, 30 };

const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
ImGui::ItemSize(size, 0);
if (!ImGui::ItemAdd(bb, id))
return false;

bool hovered, held;
bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, 0);

if (hovered || held)
ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);

static std::map<ImGuiID, float> hover_animation;
auto it_hover = hover_animation.find(id);
if (it_hover == hover_animation.end())
{
hover_animation.insert({ id, 0.f });
it_hover = hover_animation.find(id);
}
it_hover->second = ImClamp(it_hover->second + (0.2f * ImGui::GetIO().DeltaTime * (hovered || ImGui::IsItemActive() ? 1.f : -1.f)), 0.0f, 0.15f);
it_hover->second *= ImMin(ImGui::GetStyle().Alpha * 1.2f, 1.f);

static std::map<ImGuiID, float> filled_animation;
auto it_filled = filled_animation.find(id);
if (it_filled == filled_animation.end())
{
filled_animation.insert({ id, 0.f });
it_filled = filled_animation.find(id);
}
it_filled->second = ImClamp(it_filled->second + (2.55f * ImGui::GetIO().DeltaTime * (ImGui::IsItemHovered() ? 1.f : -1.0f)), it_hover->second, 1.f);
it_filled->second *= ImMin(ImGui::GetStyle().Alpha * 1.2f, 1.f);

static std::map<ImGuiID, float> fill_animation;
auto it_fill = fill_animation.find(id);
if (it_fill == fill_animation.end())
{
fill_animation.insert({ id, 0.f });
it_fill = fill_animation.find(id);
}
it_fill->second = ImClamp(it_fill->second + (2.55f * ImGui::GetIO().DeltaTime * (selected ? 1.f : -1.0f)), it_hover->second, 1.f);
it_fill->second *= ImMin(ImGui::GetStyle().Alpha * 1.2f, 1.f);

ImGui::GetWindowDrawList()->AddText(phobia_big_font, 19, ImVec2(bb.Min.x + 40, bb.Min.y + 5), ImColor(65, 65, 65, int(255 * ImGui::GetStyle().Alpha)), label);
ImGui::GetWindowDrawList()->AddText(phobia_icon_font, 18, ImVec2(bb.Min.x + 10, bb.Min.y + 5), ImColor(65, 65, 65, int(255 * ImGui::GetStyle().Alpha)), icon);

if (selected)
{
ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(bb.Min.x, bb.Min.y), ImVec2(bb.Max.x, bb.Max.y), ImColor(41, 41, 41, int(255 * it_fill->second)), 5);
ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(pos.x, pos.y + 5), ImVec2(pos.x + it_fill->second * 2, pos.y + 25), ImColor(174, 139, 148, int(255 * ImGui::GetStyle().Alpha)), 10.f, ImDrawFlags_RoundCornersRight);

ImGui::GetWindowDrawList()->AddText(phobia_icon_font, 18, ImVec2(bb.Min.x + 10, bb.Min.y + 5), ImColor(255, 255, 255, int(255 * it_fill->second)), icon);
ImGui::GetWindowDrawList()->AddText(phobia_big_font, 19, ImVec2(bb.Min.x + 40, bb.Min.y + 5), ImColor(255, 255, 255, int(255 * it_fill->second)), label);
}

if (ImGui::IsItemHovered())
{
ImGui::GetWindowDrawList()->AddRect(ImVec2(bb.Min.x - 1, bb.Min.y), ImVec2(bb.Max.x, bb.Max.y), ImColor(75, 75, 75, int(255 * it_filled->second)), 5);
}

return pressed;
}

bool phobia::menu_child(const char* name, const ImVec2& size_arg, bool border, ImGuiWindowFlags flags)
{
ImGuiContext& g = *GImGui;
ImGuiWindow* parent_window = g.CurrentWindow;
const ImGuiID id = parent_window->GetID(name);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 8));
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 3));

flags |= ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_ChildWindow;
flags |= (parent_window->Flags & ImGuiWindowFlags_NoMove);

const ImVec2 content_avail = ImGui::GetContentRegionAvail();
ImVec2 size = ImFloor(size_arg);
const int auto_fit_axises = ((size.x == 0.0f) ? (1 << ImGuiAxis_X) : 0x00) | ((size.y == 0.0f) ? (1 << ImGuiAxis_Y) : 0x00);
if (size.x <= 0.0f)
size.x = ImMax(content_avail.x + size.x, 4.0f);
if (size.y <= 0.0f)
size.y = ImMax(content_avail.y + size.y, 4.0f);
ImGui::SetNextWindowSize(size - ImVec2(0, 7 * dpi_scale));

char title[256];
ImFormatString(title, IM_ARRAYSIZE(title), "%s/%s_%08X", parent_window->Name, name, id);

const float backup_border_size = g.Style.ChildBorderSize;
g.Style.ChildBorderSize = 0.0f;
bool ret = ImGui::Begin(title, NULL, flags);
g.Style.ChildBorderSize = backup_border_size;

ImGuiWindow* child_window = g.CurrentWindow;
child_window->ChildId = id;
child_window->AutoFitChildAxises = (ImS8)auto_fit_axises;

if (child_window->BeginCount == 1)
parent_window->DC.CursorPos = child_window->Pos;

if (g.NavActivateId == id && !(flags & ImGuiWindowFlags_NavFlattened) && (child_window->DC.NavLayersActiveMask != 0 || child_window->DC.NavHasScroll))
{
ImGui::FocusWindow(child_window);
ImGui::NavInitWindow(child_window, false);
ImGui::SetActiveID(id + 1, child_window);
g.ActiveIdSource = ImGuiInputSource_Nav;
}

auto pos = ImGui::GetWindowPos() - ImVec2(0, 23 * dpi_scale);
auto p = ImGui::GetWindowPos() - ImVec2(0, 7 * dpi_scale);

parent_window->DrawList->AddRectFilled(pos, p + size_arg, ImColor(32, 32, 32, int(255 * ImGui::GetStyle().Alpha)), 5);
parent_window->DrawList->AddRect(pos, p + size_arg, ImColor(50, 50, 50, int(255 * ImGui::GetStyle().Alpha)), 5);
parent_window->DrawList->AddText(phobia_big_font, 17 * dpi_scale, pos + ImVec2(10 * dpi_scale, 8 * dpi_scale), ImColor(105, 105, 105, int(255 * ImGui::GetStyle().Alpha)), name);

return ret;
}

void phobia::add_colored_text(ImDrawList* draw, const ImVec2& pos, ImU32 color1, ImU32 color2, const char* text)
{
const char* start = text;
const char* end = text;
ImVec2 currentPos = pos;

while (*end)
{
if (*end == '(')
{
if (start != end)
{
float partWidth = ImGui::CalcTextSize(start, end).x;
draw->AddText(currentPos, color1, start, end);
currentPos.x += partWidth;
}
start = end + 1;
}
else if (*end == ')')
{
if (start != end)
{
float partWidth = ImGui::CalcTextSize(start, end).x;
draw->AddText(currentPos, color1, start, end);
currentPos.x += partWidth;
}
float partWidth = ImGui::CalcTextSize(start, end).x;
currentPos.x -= partWidth;
draw->AddText(currentPos, color2, start, end);
currentPos.x += partWidth;
start = end + 1;
}
++end;
}

if (start != end)
draw->AddText(currentPos, color1, start, end);
}








bool phobia::checkbox(const char* label, bool* v)
{
ImGuiWindow* window = ImGui::GetCurrentWindow();
if (window->SkipItems)
return false;

ImGuiContext& g = *GImGui;
const ImGuiStyle& style = g.Style;
const ImGuiID id = window->GetID(label);

const float square_sz = ImGui::GetFrameHeight();
const float spacingx = style.ItemInnerSpacing.x - 5;
const float spacingy = style.ItemInnerSpacing.y - 20;
const ImVec2 pos = window->DC.CursorPos + ImVec2(square_sz + spacingx, square_sz + spacingy);
const ImRect total_bb(pos, pos + ImVec2(square_sz, square_sz));
ImGui::ItemSize(total_bb, style.FramePadding.y);
if (!ImGui::ItemAdd(total_bb, id))
return false;

bool hovered, held;
bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);
if (pressed)
{
*v = !(*v);
ImGui::MarkItemEdited(id);
}

static std::map<ImGuiID, float> hover_animation;
auto it_hover = hover_animation.find(id);
if (it_hover == hover_animation.end())
{
hover_animation.insert({ id, 0.f });
it_hover = hover_animation.find(id);
}
it_hover->second = ImClamp(it_hover->second + (0.2f * ImGui::GetIO().DeltaTime * (hovered || ImGui::IsItemActive() ? 1.f : -1.f)), 0.0f, 0.15f);
it_hover->second *= ImMin(ImGui::GetStyle().Alpha * 1.2f, 1.f);

static std::map<ImGuiID, float> filled_animation;
auto it_filled = filled_animation.find(id);
if (it_filled == filled_animation.end())
{
filled_animation.insert({ id, 0.f });
it_filled = filled_animation.find(id);
}
it_filled->second = ImClamp(it_filled->second + (2.55f * ImGui::GetIO().DeltaTime * (ImGui::IsItemHovered() ? 1.f : -1.0f)), it_hover->second, 1.f);
it_filled->second *= ImMin(ImGui::GetStyle().Alpha * 1.2f, 1.f);

const ImRect check_bb(pos, pos + ImVec2(square_sz, square_sz));
ImGui::RenderNavHighlight(total_bb, id);

ImGui::GetWindowDrawList()->AddRect(ImVec2(check_bb.Min.x - 1, check_bb.Min.y - 1), ImVec2(check_bb.Min.x + square_sz, check_bb.Min.y + square_sz), ImColor(41, 41, 41, int(255 * ImGui::GetStyle().Alpha)), 3);
ImGui::GetWindowDrawList()->AddRect(ImVec2(check_bb.Min.x - 1, check_bb.Min.y - 1), ImVec2(check_bb.Min.x + square_sz, check_bb.Min.y + square_sz), ImColor(75, 75, 75, int(255 * it_filled->second)), 3);

if (*v)
ImGui::RenderCheckMark(window->DrawList, check_bb.Min + ImVec2(square_sz * 0.15f, square_sz * 0.10f), ImColor(174, 139, 148, int(255 * ImGui::GetStyle().Alpha)), square_sz - 6);

ImGui::GetWindowDrawList()->AddText(ImVec2(check_bb.Max.x + spacingx + 10, check_bb.Min.y), ImColor(105, 105, 105, int(255 * ImGui::GetStyle().Alpha)), label);
ImGui::GetWindowDrawList()->AddText(ImVec2(check_bb.Max.x + spacingx + 10, check_bb.Min.y), ImColor(255, 255, 255, int(255 * it_filled->second)), label);

if (*v)
ImGui::GetWindowDrawList()->AddText(ImVec2(check_bb.Max.x + spacingx + 10, check_bb.Min.y), ImColor(255, 255, 255, int(255 * ImGui::GetStyle().Alpha)), label);

return pressed;
}

bool phobia::slider(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format)
{
ImGuiWindow* window = ImGui::GetCurrentWindow();
if (window->SkipItems)
return false;

ImGuiContext& g = *GImGui;
const ImGuiStyle& style = g.Style;
const ImGuiID id = window->GetID(label);
const float w = ImGui::CalcItemWidth();

const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
const float avail = ImGui::GetContentRegionAvail().x;
const ImVec2 start = window->DC.CursorPos;
const ImRect frame_bb(start + ImVec2(20 * dpi_scale, 18 * dpi_scale), start + ImVec2(avail - 20 * dpi_scale, 36 * dpi_scale));
const ImRect total_bb(start, start + ImVec2(avail, 40 * dpi_scale));

ImGui::ItemSize(total_bb, style.FramePadding.y);
if (!ImGui::ItemAdd(total_bb, id, &frame_bb, ImGuiItemFlags_Inputable))
return false;

if (format == NULL)
format = ImGui::DataTypeGetInfo(data_type)->PrintFmt;

const bool hovered = ImGui::IsItemHovered();
bool temp_input_is_active = ImGui::TempInputIsActive(id);

if (!temp_input_is_active)
{
const bool clicked = (hovered && g.IO.MouseClicked[0]);
const bool make_active = (clicked || g.NavActivateId == id);

if (make_active && clicked && g.IO.KeyCtrl)
temp_input_is_active = true;

if (make_active && !temp_input_is_active)
{
ImGui::SetActiveID(id, window);
ImGui::SetFocusID(id, window);
ImGui::FocusWindow(window);
g.ActiveIdUsingNavDirMask |= (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
}
}

if (temp_input_is_active)
return ImGui::TempInputScalar(frame_bb, id, label, data_type, p_data, format, NULL, NULL);

static std::map<ImGuiID, float> filled_animation;
auto it_filled = filled_animation.find(id);
if (it_filled == filled_animation.end())
{
filled_animation.insert({ id, 0.f });
it_filled = filled_animation.find(id);
}
it_filled->second = ImClamp(it_filled->second + (2.55f * ImGui::GetIO().DeltaTime * (ImGui::IsItemHovered() ? 1.f : -1.0f)), 0.0f, 1.f);
it_filled->second *= ImMin(ImGui::GetStyle().Alpha * 1.2f, 1.f);

ImGui::RenderNavHighlight(frame_bb, id);
ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, ImColor(26, 26, 26, int(255 * ImGui::GetStyle().Alpha)), true, g.Style.FrameRounding);

ImRect grab_bb;
const bool value_changed = ImGui::SliderBehavior(frame_bb, id, data_type, p_data, p_min, p_max, format, 0, &grab_bb);

if (value_changed)
ImGui::MarkItemEdited(id);

if (grab_bb.Max.x > grab_bb.Min.x)
window->DrawList->AddRectFilled(frame_bb.Min + ImVec2(0, 1), grab_bb.Max + ImVec2(2, 1), ImColor(174, 139, 148, int(255 * ImGui::GetStyle().Alpha)), 3.0f);

window->DrawList->AddRect(frame_bb.Min, ImVec2(frame_bb.Max.x, frame_bb.Min.y + 18 * dpi_scale), ImColor(50, 50, 50, int(255 * ImGui::GetStyle().Alpha)), 3.0f);
window->DrawList->AddRect(frame_bb.Min, ImVec2(frame_bb.Max.x, frame_bb.Min.y + 18 * dpi_scale), ImColor(75, 75, 75, int(255 * it_filled->second)), 3.0f);

char value_buf[64];
const char* value_buf_end = value_buf + ImGui::DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, p_data, format);

auto value_size = ImGui::CalcTextSize(value_buf, value_buf_end, true);
ImGui::RenderText(ImVec2(frame_bb.Max.x - value_size.x, start.y), value_buf, value_buf_end);

if (label_size.x > 0.0f)
ImGui::RenderText(ImVec2(frame_bb.Min.x, start.y), label);

return value_changed;
}

bool phobia::slider_int(const char* label, int* v, int v_min, int v_max, const char* format)
{
return phobia::slider(label, ImGuiDataType_S32, v, &v_min, &v_max, format);
}

bool phobia::slider_float(const char* label, float* v, float v_min, float v_max, const char* format)
{
return phobia::slider(label, ImGuiDataType_Float, v, &v_min, &v_max, format);
}


static const char* vk_name(int vk)
{
static char buf[16];

switch (vk)
{
case VK_LBUTTON: return "M1";
case VK_RBUTTON: return "M2";
case VK_MBUTTON: return "M3";
case VK_XBUTTON1: return "M4";
case VK_XBUTTON2: return "M5";
case VK_BACK: return "BACK";
case VK_TAB: return "TAB";
case VK_RETURN: return "ENTER";
case VK_SHIFT: return "SHIFT";
case VK_CONTROL: return "CTRL";
case VK_MENU: return "ALT";
case VK_CAPITAL: return "CAPS";
case VK_ESCAPE: return "ESC";
case VK_SPACE: return "SPACE";
case VK_LEFT: return "LEFT";
case VK_UP: return "UP";
case VK_RIGHT: return "RIGHT";
case VK_DOWN: return "DOWN";
case VK_INSERT: return "INS";
case VK_DELETE: return "DEL";
case VK_HOME: return "HOME";
case VK_END: return "END";
case VK_PRIOR: return "PGUP";
case VK_NEXT: return "PGDN";
default: break;
}

if (vk >= 0x70 && vk <= 0x87)
{
sprintf_s(buf, "F%d", vk - 0x6F);
return buf;
}

if (vk >= 'A' && vk <= 'Z')
{
buf[0] = (char)vk;
buf[1] = 0;
return buf;
}

sprintf_s(buf, "0x%X", vk);
return buf;
}

bool phobia::keybind(const char* label, int* key)
{
ImGuiWindow* window = ImGui::GetCurrentWindow();
if (window->SkipItems)
return false;

ImGuiContext& g = *GImGui;
const ImGuiID id = window->GetID(label);

char buf[32];
if (g.ActiveId == id)
strcpy_s(buf, "[...]");
else if (*key != 0)
sprintf_s(buf, "[%s]", vk_name(*key));
else
strcpy_s(buf, "[...]");

const ImVec2 text_size = ImGui::CalcTextSize(buf, NULL, true);
const ImVec2 pos = window->DC.CursorPos;
const ImRect bb(pos, pos + ImVec2(text_size.x + 4.f, 18.f));

ImGui::ItemSize(bb);
if (!ImGui::ItemAdd(bb, id))
return false;

bool hovered, held;
bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);

if (pressed)
ImGui::SetActiveID(id, window);

if (g.ActiveId == id)
{
for (int vk = 1; vk < 255; vk++)
{
if (vk == VK_LBUTTON)
continue;

if (GetAsyncKeyState(vk) & 0x8000)
{
if (vk == VK_ESCAPE)
*key = 0;
else
*key = vk;

ImGui::ClearActiveID();
break;
}
}
}

ImU32 col = (g.ActiveId == id) ? ImColor(255, 255, 255, 255) : (hovered ? ImColor(180, 180, 180, 255) : ImColor(105, 105, 105, 255));
ImGui::GetWindowDrawList()->AddText(pos, col, buf);

return pressed;
}


