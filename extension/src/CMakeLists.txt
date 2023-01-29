# SPDX-License-Identifier: Unlicense

# Get Sources
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.c**)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS *.h**)

target_sources( ${PROJECT_NAME}
    PRIVATE
        #Example.h
        #Example.cpp
        #GDExtensionTemplate.h
        #GDExtensionTemplate.cpp
        #RegisterExtension.cpp
        ${SOURCES}
        ${HEADERS}
)

target_include_directories( ${PROJECT_NAME}
    PRIVATE
        "src"
)
