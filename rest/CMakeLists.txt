add_library(Rest 
SHARED 
rest.cpp 
session.cpp 
not_implemented.cpp 
get_method.cpp 
post_method.cpp 
not_found.cpp 
bad_request.cpp 
validate.cpp
)

find_package(Boost 1.83 REQUIRED COMPONENTS json url)

target_include_directories(Rest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)

target_link_libraries(Rest PUBLIC Boost::boost Boost::json Boost::url CNPJ)

target_compile_features(Rest PUBLIC cxx_std_23)