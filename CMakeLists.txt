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
add_compile_options(-Wall -Wextra -Wpedantic -Wshadow)

# --- Threading (portable) --------------------------------------------------
find_package(Threads REQUIRED)

# --- Dépendances Conan (à décommenter au fur et à mesure) ------------------
# find_package(fmt REQUIRED)

# =====================================================================
# Exécutable 1 : main_hello
# Point d'entrée de démonstration
# =====================================================================
set(SOURCES_MAIN_HELLO
    ${CMAKE_CURRENT_SOURCE_DIR}/apps/main_hello.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/src/foo.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/src/bar.cpp
)

add_executable(main_hello ${SOURCES_MAIN_HELLO})
target_include_directories(main_hello PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(main_hello PUBLIC Threads::Threads)
# target_link_libraries(main_hello PUBLIC fmt::fmt)

# =====================================================================
# Exécutable 2 : main_graph  (exemple à décommenter le jour venu)
# Description : ...
# =====================================================================
# set(SOURCES_MAIN_GRAPH
#     ${CMAKE_CURRENT_SOURCE_DIR}/apps/main_graph.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/src/graph/bfs.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/src/graph/dfs.cpp
# )
#
# add_executable(main_graph ${SOURCES_MAIN_GRAPH})
# target_include_directories(main_graph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
# target_link_libraries(main_graph PUBLIC Threads::Threads)
