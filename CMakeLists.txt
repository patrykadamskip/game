# Minimalna wymagana wersja CMake
cmake_minimum_required(VERSION 3.10)

# Nazwa projektu
project(arenagame CXX)

# Ustawienia dla kompilacji z architekturą 32-bitową
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")

# Dodanie ścieżki do plików nagłówkowych i źródłowych
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Inc ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/SDL2_files/include ${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB SOURCES "Src/*.cpp")

# Ścieżki do bibliotek SDL2
link_directories(${CMAKE_SOURCE_DIR}/ThirdParty/SDL2_files/lib)

# Tworzenie pliku wykonywalnego
add_executable(arenagame ${SOURCES})

# Linkowanie z bibliotekami SDL2
target_link_libraries(arenagame SDL2main SDL2 SDL2_image SDL2_ttf)

# Kopiowanie SDL2.dll do folderu `Build` po kompilacji
add_custom_command(TARGET arenagame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/ThirdParty/SDL2_files/lib/SDL2.dll"
    "$<TARGET_FILE_DIR:arenagame>"
)

# Kopiowanie SDL2_image.dll do folderu `Build` po kompilacji
add_custom_command(TARGET arenagame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/ThirdParty/SDL2_files/lib/SDL2_image.dll"
        "$<TARGET_FILE_DIR:arenagame>"
)

# Kopiowanie SDL2_ttf.dll do folderu `Build` po kompilacji
add_custom_command(TARGET arenagame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/ThirdParty/SDL2_files/lib/SDL2_ttf.dll"
    "$<TARGET_FILE_DIR:arenagame>"
)

# Copy the entire 'Assets' folder to 'Build'
add_custom_command(TARGET arenagame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/Assets
        ${CMAKE_BINARY_DIR}/Assets
)