#include <iostream>
#include "wanderer.h"

using namespace enviro;


void WandererController::update() {

	auto current_angle = angle();
	auto front_dist = sensor_value(0);
	auto front_right_dist = sensor_value(1);
	auto front_left_dist = sensor_value(2);
	auto right_dist = sensor_value(3);

	double damping_term = 3;

	std::cout << " front_right, front, right : " << front_left_dist << ", " << front_dist << ", " << front_right_dist << "\n";
	
	if (front_dist < 12 && right_dist < 12) {
		if (sensor_reflection_type(0) == "Finish") {
			remove_agent(id());
		}
	}

	if (front_dist < 9 && right_dist < 9) {
		track_velocity(0, -8);
	}
	else {
		auto diff = front_right_dist - right_dist;
		if (diff > 5) {
			track_velocity(6, 8);
		}
		else if (diff < 0) {
			track_velocity(0, -3);
		}
		else {
			track_velocity(8, -0.5);
		}
	}
	
}