#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height),
      sdl_window(nullptr, &SDL_DestroyWindow),
      sdl_renderer(nullptr, &SDL_DestroyRenderer)
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  sdl_window.reset(SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED, screen_width,
                                    screen_height, SDL_WINDOW_SHOWN));

  if (nullptr == sdl_window)
  {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer.reset(SDL_CreateRenderer(sdl_window.get(), -1, SDL_RENDERER_ACCELERATED));
  if (nullptr == sdl_renderer)
  {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer()
{
  SDL_Quit();
}

Renderer::Renderer(const Renderer &source)
    : screen_width(source.screen_width),
      screen_height(source.screen_height),
      grid_width(source.grid_width),
      grid_height(source.grid_height),
      sdl_window(nullptr, SDL_DestroyWindow),
      sdl_renderer(nullptr, SDL_DestroyRenderer)
{
  // Create a new window and renderer with the same properties as the original
  sdl_window.reset(SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED, screen_width,
                                    screen_height, SDL_WINDOW_SHOWN));

  if (nullptr == sdl_window)
  {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  sdl_renderer.reset(SDL_CreateRenderer(sdl_window.get(), -1, SDL_RENDERER_ACCELERATED));
}

Renderer &Renderer::operator=(const Renderer &source)
{

  if (&source == this)
    return *this;
  else
  {
    this->screen_width = source.screen_width;
    this->screen_height = source.screen_height;
    this->grid_width = source.grid_width;
    this->grid_height = source.grid_height;

    this->sdl_window.reset(SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED, source.screen_width,
                                            source.screen_height, SDL_WINDOW_SHOWN));
    this->sdl_renderer.reset(SDL_CreateRenderer(sdl_window.get(), -1, SDL_RENDERER_ACCELERATED));
  }

  return *this;
}

Renderer& Renderer::operator= (Renderer &&source)
{
  if(&source == this)
    return *this;
  else
  {
    this->screen_width = source.screen_width;
    this->screen_height = source.screen_height;
    this->grid_width = source.grid_width;
    this->grid_height = source.grid_height;

    sdl_window=std::move(source.sdl_window);
    sdl_renderer=std::move(source.sdl_renderer);

    return *this;

  }
}

Renderer::Renderer(Renderer &&other)
    : screen_width(other.screen_width),
      screen_height(other.screen_height),
      grid_width(other.grid_width),
      grid_height(other.grid_height),
      sdl_window(std::move(other.sdl_window)),
      sdl_renderer(std::move(other.sdl_renderer)) {}

void Renderer::Render(Snake const snake, SDL_Point const &food)
{
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer.get(), 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer.get(), &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body)
  {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer.get(), &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive)
  {
    SDL_SetRenderDrawColor(sdl_renderer.get(), 0x00, 0x7A, 0xCC, 0xFF);
  }
  else
  {
    SDL_SetRenderDrawColor(sdl_renderer.get(), 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer.get(), &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer.get());
}

void Renderer::Render(Snake const snake, std::vector<SDL_Point> const &obstacles)
{
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer.get(), 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer.get());

  SDL_SetRenderDrawColor(sdl_renderer.get(), 0xFF, 0x00, 0x00, 0xFF);
  for (auto obstacle : obstacles)
  {
    // Render obstacles
    block.x = obstacle.x * block.w;
    block.y = obstacle.y * block.h;
    SDL_RenderFillRect(sdl_renderer.get(), &block);
  }

  // // Update Screen
  SDL_RenderPresent(sdl_renderer.get());
}

void Renderer::UpdateWindowTitle(int highscore, int score, int fps)
{
  std::string title{"High Score: "+ std::to_string(highscore) +" Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window.get(), title.c_str());
}
