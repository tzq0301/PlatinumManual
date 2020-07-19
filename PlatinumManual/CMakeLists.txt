cmake_minimum_required(VERSION 3.15)
project(PlatinumManual C)

set(CMAKE_C_STANDARD 99)

add_executable(PlatinumManual main.c lyy.h yyh.h hyk.h yyh.c lyy.c hyk.c manage_password.c manage_password.h manage_url_of_web_page.c manage_url_of_web_page.h)