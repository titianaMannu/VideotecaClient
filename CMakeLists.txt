cmake_minimum_required(VERSION 3.14)
project(VideotecaClient C)

set(CMAKE_C_STANDARD 99)
link_directories("${PROJECT_SOURCE_DIR}/mysql")
add_executable(VideotecaClient main.c jsmn.c jsmn.h inout.c parse.c program.h utils.c utils.h cliente.c cliente.h main.h manager.c manager.h impiegato.c impiegato.h)
target_link_libraries(VideotecaClient mysqlclient)