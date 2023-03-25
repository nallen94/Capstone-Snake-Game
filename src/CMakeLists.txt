set (exe_name snake_game)

set(target_headers 
    controller.h
    game.h
    renderer.h
    snake.h
    score.h
)

set(target_sources 
    main.cpp
    controller.cpp
    game.cpp
    renderer.cpp
    snake.cpp
    score.cpp
)
add_executable(${exe_name}
                ${target_headers}
                ${target_sources})

target_link_libraries(snake_game ${SDL2_LIBRARIES})
set_target_properties(${exe_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
