#pragma once

struct IDirect3DDevice9;

namespace phobia
{
void init(IDirect3DDevice9* device);
void draw(bool open);
}
