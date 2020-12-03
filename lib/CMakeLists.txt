add_library(Croissant INTERFACE)

target_sources(Croissant INTERFACE
               ${CMAKE_CURRENT_LIST_DIR}/Croissant/EqualityComparison.hpp
               ${CMAKE_CURRENT_LIST_DIR}/Croissant/LessComparison.hpp
               ${CMAKE_CURRENT_LIST_DIR}/Croissant/LessOrEqualComparison.hpp
               ${CMAKE_CURRENT_LIST_DIR}/Croissant/MoreComparison.hpp
               ${CMAKE_CURRENT_LIST_DIR}/Croissant/MoreOrEqualComparison.hpp
               ${CMAKE_CURRENT_LIST_DIR}/Croissant/Croissant.hpp
               ${CMAKE_CURRENT_LIST_DIR}/Croissant/Result.hpp
               ${CMAKE_CURRENT_LIST_DIR}/Croissant/Tags.hpp
               ${CMAKE_CURRENT_LIST_DIR}/Croissant/Value.hpp)

target_compile_features(Croissant INTERFACE cxx_std_20)

target_include_directories(Croissant INTERFACE ${CMAKE_CURRENT_LIST_DIR})