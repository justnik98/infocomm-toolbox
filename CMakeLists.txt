cmake_minimum_required(VERSION 3.22)
project(infocomm_toolbox)

set(CMAKE_CXX_STANDARD 20)

add_executable(infocomm_toolbox main.cpp channels/channel.cpp channels/channel.hpp channels/awgnchannel.cpp channels/awgnchannel.hpp)
