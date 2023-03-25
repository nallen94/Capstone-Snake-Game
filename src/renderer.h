#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include <memory>

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  //Rule of five implementation
  Renderer(const Renderer& source);
  Renderer& operator = (const Renderer& source);

  Renderer(Renderer &&other);
  Renderer& operator= (Renderer&& source);

  void Render(Snake const snake, SDL_Point const &food);
  void Render(Snake const snake, std::vector<SDL_Point> const &);
  void UpdateWindowTitle(int score, int fps);

 private:

  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> sdl_window;
  std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> sdl_renderer;

  std::size_t screen_width;
  std::size_t screen_height;
  std::size_t grid_width;
  std::size_t grid_height;
};

#endif