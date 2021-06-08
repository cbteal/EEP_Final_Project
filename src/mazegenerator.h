#ifndef MAZEGENERATOR
#define MAZEGENERATOR

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "cstdlib"
#include "ctime"
#include <list>

/** 
	\class MazeGenerator
	\brief Generates Random Maze

	Maze generator randomly generates a random maze within a defined rectangle.\n
	Note that at the moment, the size is static and implementation is crude.\n
	To-do: Dynamically scale maze, add param for maze size, optimize finish line,

 */
class MazeGenerator {
public:
	MazeGenerator() { srand(time(0)); }
	void generate_maze(std::pair<double, double> location);
	const std::vector<std::pair<double, double>> get_walls();
	const std::pair<double, double> get_finish();


private:

	double _xmin = -340;
	double _xmax = 340;
	double _ymin = -200;
	double _ymax = 200;
	double _block_width = 20;

	double _block_mid = _block_width / 2;
	double _true_ymax = _ymax - _block_mid;
	double _true_ymin = _ymin + _block_mid;
	double _true_xmax = _xmax - _block_mid;
	double _true_xmin = _xmin + _block_mid;

	std::vector<std::pair<double, double>> _visited;
	std::vector<std::pair<double, double>> _start_walls;
	std::pair<double, double> _finish;


	bool has_neighbor(std::pair<double, double> location);
	bool is_valid(std::pair<double, double> location);
	bool is_visited(std::pair<double, double> location);
	int visited_neighbors(std::pair<double, double> location);
	std::pair<double, double> choose_valid_neighbor(std::pair<double, double> location);
	vector<int> generateRandomDirections();
	void fill_maze();
};

/**
	\brief Gets finish line coordinate

	Get finish checks the corners of the map for an open cell to
	place the finish line, which is just a custom agent.\n

	To-do: Make smarter and randomize, incorporate scaling and dynamic
	map size
*/
const std::pair<double, double> MazeGenerator::get_finish() {
	auto left_top = std::make_pair(-320, 180);
	auto left_bot = std::make_pair(-320, -180);
	auto right_top = std::make_pair(320, 180);
	auto right_bot = std::make_pair(320, -180);
	
	if (is_visited(left_top)) {
		return left_top;
	}
	if (is_visited(left_bot)) {
		return left_bot;
	}
	if (is_visited(right_top)) {
		return right_top;
	}
	if (is_visited(right_bot)) {
		return right_bot;
	}

	return _finish;
}

/**
	\brief Checks to see if maze generator has visited coordinate

	\b is_visisted checks to see if the current coordinate has been
	visited by the map generator. If it exists in the visited coordinates
	list it returns true, else false.
*/
bool MazeGenerator::is_visited(std::pair<double, double> location) {
	if (std::find(_visited.begin(), _visited.end(), location) != _visited.end()) {
		return true;
	}
	else {
		return false;
	}
}

/**
	\brief Generates vector of coordinates for walls to generate

	\b get_walls generates coordinates for walls by removing the visited
	coordinates from all possible coordinates.
*/
const std::vector<std::pair<double, double>> MazeGenerator::get_walls() {
	vector<std::pair<double, double>> diff;
	for (int i = 0; i < _start_walls.size(); i++) {
		if (!is_visited(_start_walls[i])) {
			diff.push_back(_start_walls[i]);
		}
	}
	std::cout << "Finish location: " << _finish.first << ", " << _finish.second << "\n";
	return diff;
}

/**
	\brief Checks to see if coordinate is within the border

	\b is_valid checks to see if a coordinate is within the border of the
	maze. Returns true if inside the border, else false.
*/
bool MazeGenerator::is_valid(std::pair<double, double> location) {
	if (location.first < _true_xmax && location.first > _true_xmin &&
		location.second < _true_ymax && location.second > _true_ymin) {
		return true;
	}
	else {
		return false;
	}
}

/**
	\brief Calculates how many neighboring coordinates have been visited

	\b visited_neighbors checks the neighbors (left, up, right, down) to see
	if they have been visited by the map generator and returns the number of
	neighbors that have been visited.
*/
int MazeGenerator::visited_neighbors(std::pair<double, double> location) {
	int neighbors_visited = 0;
	auto left = std::make_pair(location.first - _block_width, location.second);
	auto right = std::make_pair(location.first + _block_width, location.second);
	auto up = std::make_pair(location.first, location.second + _block_width);
	auto down = std::make_pair(location.first, location.second - _block_width);

	if (is_visited(left)) { neighbors_visited++; }
	if (is_visited(right)) { neighbors_visited++; }
	if (is_visited(up)) { neighbors_visited++; }
	if (is_visited(down)) { neighbors_visited++; }

	return neighbors_visited;
}

/**
	\brief Checks to see if coordinate has a valid neighbor

	\b has_neighbor checks to see if there is a valid neighbor which is used
	by the map generator to determine if it can continue to move from its current
	location.
*/
bool MazeGenerator::has_neighbor(std::pair<double, double> location) {

	auto left = std::make_pair(location.first - _block_width, location.second);
	auto right = std::make_pair(location.first + _block_width, location.second);
	auto up = std::make_pair(location.first, location.second + _block_width);
	auto down = std::make_pair(location.first, location.second - _block_width);

	if (is_valid(left) && !is_visited(left) && visited_neighbors(left) < 2) {
		return true;
	}
	if (is_valid(right) && !is_visited(right) && visited_neighbors(right) < 2) {
		return true;
	}
	if (is_valid(up) && !is_visited(up) && visited_neighbors(up) < 2) {
		return true;
	}
	if (is_valid(down) && !is_visited(down) && visited_neighbors(down) < 2) {
		return true;
	}
	return false;
}

/**
	\brief Generates a random int used for choosing a direction (left, up, right, down)

	Not used
*/
vector<int> MazeGenerator::generateRandomDirections() {
	vector<int> randoms;
	for (int i = 0; i < 4; i++)
		randoms.push_back(i + 1);

	std::random_shuffle(randoms.begin(), randoms.end());

	return randoms;
}

/**
	\brief Fills all possible maze coordinates

	\b fill_maze will generate a vector of all possible coordinates
*/
void MazeGenerator::fill_maze() {
	for (double x = -320; x <= 320; x += 20) {
		for (double y = -180; y <= 180; y += 20) {
			_start_walls.push_back(std::make_pair(x,y));
		}
	}
}

/**
	\brief Chooses a valid neighbor for the maze generator

	\b choose_valid_neighbor will choose a neighbor which is valid, has not
	been visited, and does not have more than one neighbor.
*/
std::pair<double, double> MazeGenerator::choose_valid_neighbor(std::pair<double, double> location) {
	vector<std::pair<double, double>> valid_cells;
	auto left = std::make_pair(location.first - _block_width, location.second);
	auto right = std::make_pair(location.first + _block_width, location.second);
	auto up = std::make_pair(location.first, location.second + _block_width);
	auto down = std::make_pair(location.first, location.second - _block_width);

	if (is_valid(left) && !is_visited(left) && visited_neighbors(left) < 2) {
		valid_cells.push_back(left);
	}
	if (is_valid(right) && !is_visited(right) && visited_neighbors(right) < 2) {
		valid_cells.push_back(right);
	}
	if (is_valid(up) && !is_visited(up) && visited_neighbors(up) < 2) {
		valid_cells.push_back(up);
	}
	if (is_valid(down) && !is_visited(down) && visited_neighbors(down) < 2) {
		valid_cells.push_back(down);
	}

	//std::cout << "VALID CELLS: " << valid_cells.size() << "\n";


	std::random_shuffle(valid_cells.begin(), valid_cells.end());

	return valid_cells[0];
}


/**
	\brief Generates a random maze

	\b generate_maze returns coordinates for the walls of a randomly
	generated maze. Its input is the starting location for the generator.
*/
void MazeGenerator::generate_maze(std::pair<double, double> location) {
	fill_maze();
	vector<std::pair<double, double>> stack;

	_visited.push_back(location);
	stack.push_back(location);

	while (!stack.empty()) {   // While there are still possible paths
		auto cell = stack.back(); // Grab top of stack (current location)
		//std::cout << "STACK SIZE: " << stack.size() << "\n";
		stack.pop_back(); // Pop current location off the stack
		if (has_neighbor(cell)) { // If there is a valid neighbor
			//std::cout << "FOUND NEIGHBOR\n";
			stack.push_back(cell); // Add current location back to stack
			auto next_cell = choose_valid_neighbor(cell); // Select a valid neighbor to move to
			_visited.push_back(next_cell); // Add neighbor coordinate to visited
			stack.push_back(next_cell); // Add neighbor coordinate to stack (now current location)
		}
	}

	_finish = _visited.back(); // Not used, but returns last visited coordinate
}
#endif