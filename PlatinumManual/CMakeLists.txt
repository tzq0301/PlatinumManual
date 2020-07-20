cmake_minimum_required(VERSION 3.15)
project(PlatinumManual C)

set(CMAKE_C_STANDARD 99)

add_executable(PlatinumManual main.c yyh.h manage_schedule.h yyh.c manage_schedule.c manage_password.c manage_password.h manage_url_of_web_page.c manage_url_of_web_page.h manage_diary.c manage_diary.h manage_address_list.c manage_address_list.h)