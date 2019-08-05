add_library(myolinux SHARED IMPORTED)
set_target_properties(myolinux PROPERTIES IMPORTED_LOCATION /path/to/libmyo)

add_library(gesturenetwork SHARED IMPORTED)
set_target_properties(gesturenetwork PROPERTIES IMPORTED_LOCATION /path/to/network)

add_executable(gesture
  gesture.cpp)

target_link_libraries(gesture
                      PRIVATE
                        myolinux
			gesturenetwork)

