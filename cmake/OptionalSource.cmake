#https://github.com/clementine-player/Clementine/tree/master/cmake

macro(optional_source TOGGLE)
  parse_arguments(OPTIONAL_SOURCE
    "SOURCES;HEADERS;INCLUDE_DIRECTORIES"
    ""
    ${ARGN}
  )

  if(${TOGGLE})
    list(APPEND SOURCES ${OPTIONAL_SOURCE_SOURCES})
    list(APPEND HEADERS ${OPTIONAL_SOURCE_HEADERS})
    include_directories(${OPTIONAL_SOURCE_INCLUDE_DIRECTORIES})
  else(${TOGGLE})
    list(APPEND OTHER_SOURCES ${OPTIONAL_SOURCE_SOURCES})
    list(APPEND OTHER_SOURCES ${OPTIONAL_SOURCE_HEADERS})

  endif(${TOGGLE})
endmacro(optional_source)
