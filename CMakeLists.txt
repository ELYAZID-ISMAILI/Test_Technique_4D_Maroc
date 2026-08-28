cmake_minimum_required(VERSION 3.15)

project(Test_Technique_4D_Maroc VERSION 0.1 LANGUAGES CXX)

# --- IntelliSense (compile_commands.json pour VS Code) ---------------------
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- Standard C++17 --------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Build type par défaut : Release ---------------------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# --- Warnings globaux ------------------------------------------------------
add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Wfatal-errors)

# --- Threading (portable) --------------------------------------------------
find_package(Threads REQUIRED)

# --- Dépendances Conan (à décommenter au fur et à mesure) ------------------
# find_package(fmt REQUIRED)

# =====================================================================
# Exécutable 1 : checkValidaty
# Point d'entrée de démonstration
# =====================================================================
set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/apps/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/jsonValidate.cpp
)

add_executable(checkValidaty ${SOURCES})
target_include_directories(checkValidaty PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(checkValidaty PUBLIC Threads::Threads)
