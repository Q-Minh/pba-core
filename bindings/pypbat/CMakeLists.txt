target_sources(PhysicsBasedAnimationToolkit_Python
    PRIVATE
    "PythonBindings.cpp"
)

add_subdirectory(fem)
add_subdirectory(geometry)
add_subdirectory(math)
add_subdirectory(profiling)

target_link_libraries(PhysicsBasedAnimationToolkit_Python
    PRIVATE
    PBAT_PyFem
    Python::Module
    pybind11::headers
)