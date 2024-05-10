cmake_minimum_required(VERSION 3.28)
project(113assignment1)

set(CMAKE_CXX_STANDARD 11)

add_executable(113assignment1 main.cpp
        Discount.h
        Product.h
        State.h
        Inventory_manager.h
        Warehouse.h
        Commodity_Inbound_Management_System.h
        Commodity_Outbound_Management_System.h
        Commodity_Search_System.h
)
