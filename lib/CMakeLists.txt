add_library(Croissant INTERFACE)

target_sources(Croissant INTERFACE
               ${CMAKE_CURRENT_LIST_DIR}/Croissant/EqualityComparaison.hpp
               ${CMAKE_CURRENT_LIST_DIR}/Croissant/LessComparaison.hpp
               ${CMAKE_CURRENT_LIST_DIR}/Croissant/LessOrEqualComparaison.hpp
               ${CMAKE_CURRENT_LIST_DIR}/Croissant/MoreComparaison.hpp
               ${CMAKE_CURRENT_LIST_DIR}/Croissant/MoreOrEqualComparaison.hpp
               ${CMAKE_CURRENT_LIST_DIR}/Croissant/Croissant.hpp
               ${CMAKE_CURRENT_LIST_DIR}/Croissant/Result.hpp
               ${CMAKE_CURRENT_LIST_DIR}/Croissant/Tags.hpp
               ${CMAKE_CURRENT_LIST_DIR}/Croissant/Value.hpp)

target_compile_features(Croissant INTERFACE cxx_std_20)

target_include_directories(Croissant INTERFACE ${CMAKE_CURRENT_LIST_DIR})