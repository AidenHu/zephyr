cmake_minimum_required(VERSION 3.8.2)
include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(socket_tcp)

target_include_directories(app PRIVATE $ENV{ZEPHYR_BASE}/subsys/net/ip)
FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE ${app_sources})
