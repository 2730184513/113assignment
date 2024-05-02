cmake_minimum_required(VERSION 3.28)
project(113assignment1)

set(CMAKE_CXX_STANDARD 11)

add_executable(113assignment1 main.cpp
        Specific_Product_class.h
        Abstract_Discount_class.h
        Abstract_Product_class.h
        Specific_Discount_class.h
        State.h
        Inventory_manager.h)
