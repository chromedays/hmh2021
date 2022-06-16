cmake_minimum_required(VERSION 3.14)

if(WIN32)
  add_executable(handmade_hero WIN32 "win32_handmade.cpp" )
  # target_link_libraries( handmade_hero PUBLIC SDL2.lib PUBLIC SDL2main.lib
  # PUBLIC gdi32.lib PUBLIC Shell32.lib PUBLIC d3d11.lib PUBLIC dxgi.lib PUBLIC
  # dxguid.lib PUBLIC d3dcompiler.lib PUBLIC winmm.lib PUBLIC Shcore.lib)
endif()
