# CMakeLists.txt
#
# Ejemplo de archivo de configuracion para cmake
# cuando se utilizan librerias de ROOT
# 
# Hector Perez abril 2022

cmake_minimum_required(VERSION 3.10)
project(rootExample)

# Esta linea le indica a cmake que localice la 
# instalacion de ROOT. Para que esto funcione
# se debe hacer ejecutar el comando (o su equivalente)
# 
#   source /ruta/a/la/instalacion/de/root/bin/thisroot.sh
#
# previamente
find_package(ROOT REQUIRED)

# Esta instruccion hace que los headers (.h) de ROOT
# esten disponibles al momento de compilacion
include_directories(${ROOT_INCLUDE_DIRS})

add_executable(root_example example01.cpp)

# Tambien se debe indicar la ruta a las librerias
# para hacer el enlazado del ejecutable.
target_link_libraries(root_example ${ROOT_LIBRARIES} )

