//
// Created by 邓初杰 on 24-5-2.
//

#ifndef STATE_H
#define STATE_H
enum State    //Represent the default state(value) to increase readability.
{
	NO_INITIALIZED = -1,
	NO_DISCOUNT = 1,
	CAKE = 0,
	COOKIE = 1,
	CAKE_DISCOUNT_RULE = 3,
	COOKIE_DISCOUNT_RULE = 5,
	WRONG_TYPE = -1,
};
#endif //STATE_H
