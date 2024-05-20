//
// Created by 邓初杰 on 24-5-2.
//

#ifndef STATE_H
#define STATE_H
enum State    //Represent the default state(value) to increase readability.
{
	NOT_FIND = -5,
	OUT_OF_RANGE = -4,
	FAILED = -3,
	WRONG_TYPE = -2,
	NO_INITIALIZED = -1,
	SELLOUT = 0,
	NO_DISCOUNT = 1,
	QUIT = 2,
	SUCCESS = 3,

};
enum type
{
	CAKE = 0,
	COOKIE = 1,
	CAKE_DISCOUNT_RULE = 3,
	COOKIE_DISCOUNT_RULE = 5,
};
enum Commands
{
	ASCENDING_ORDER = 0,
	DESCENDING_ORDER = 1,
	BASE_NAME = 0,
	BASE_PRICE,
	BASE_QUANTITY,
	BASE_DISCOUNT,
};
#endif //STATE_H
