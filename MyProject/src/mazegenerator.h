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

	Maze generator randomly generates a random maze within a defined rectangle.
	Note that at the moment, the size is static and implementation is crude.
	To-do: Dynamically scale maze, add param for maze size, optimize finish line

	\var _xmin double
    \brief Minimum x coordinate of border
    
    \var _xmax double
	\brief Maximum x coordinate of border

	\var _ymin double
	\brief Minimum y coordinate of border

	\var _ymax double
	\brief Maxium y coordinate of border

	\var _block_width double
	\brief Width of wall block
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

bool MazeGenerator::is_visited(std::pair<double, double> location) {
	if (std::find(_visited.begin(), _visited.end(), location) != _visited.end()) {
		return true;
	}
	else {
		return false;
	}
}

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

bool MazeGenerator::is_valid(std::pair<double, double> location) {
	if (location.first < _true_xmax && location.first > _true_xmin &&
		location.second < _true_ymax && location.second > _true_ymin) {
		return true;
	}
	else {
		return false;
	}
}

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


vector<int> MazeGenerator::generateRandomDirections() {
	vector<int> randoms;
	for (int i = 0; i < 4; i++)
		randoms.push_back(i + 1);

	std::random_shuffle(randoms.begin(), randoms.end());

	return randoms;
}

void MazeGenerator::fill_maze() {
	for (double x = -320; x <= 320; x += 20) {
		for (double y = -180; y <= 180; y += 20) {
			_start_walls.push_back(std::make_pair(x,y));
		}
	}
}
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


//void MazeGenerator::generate_maze(std::pair<double,double> location) {
//	//std::cout << "HELLO\n";
//	//std::cout << "YMIN " << _true_ymin << "YMAX " << _true_ymax << " XMIN " << _true_xmin << " XMAX " << _true_xmax << "\n";
//	if (visited_neighbors(location) > 2) {
//		std::cout << "MORE THAN ONE VISITED NEIGHBORS\n";
//		return;
//	}
//	_visited.push_back(location);
//	std::cout << "Adding " << location.first << ", " << location.second << " \n";
//	auto p = new_direction(location);
//	generate_maze(p);
//}



void MazeGenerator::generate_maze(std::pair<double, double> location) {
	fill_maze();
	vector<std::pair<double, double>> stack;

	_visited.push_back(location);
	stack.push_back(location);

	while (!stack.empty()) {
		auto cell = stack.back();
		//std::cout << "STACK SIZE: " << stack.size() << "\n";
		stack.pop_back();
		if (has_neighbor(cell)) {
			//std::cout << "FOUND NEIGHBOR\n";
			stack.push_back(cell);
			auto next_cell = choose_valid_neighbor(cell);
			/*if (next_cell.first == 999 and next_cell.second == 999) {
				break;
			}*/
			_visited.push_back(next_cell);
			stack.push_back(next_cell);
			//_visited.push_back(next_cell);
			//std::cout << "TEST\n";
		}
	}

	_finish = _visited.back();
}
#endif