#pragma once
#include "grid.hpp"

class Simulation {
public:
	Simulation(int width, int height, int cellSize) :
		grid(width, height, cellSize), temp_grid(width, height, cellSize) {};
	void Draw();
	void SetCellValue(int row, int column, int value); 
	void ToggleCellValue(int row, int column);
	void Clear();
	int CountLiveNeighbors(int row, int column);
	void Update();
private:
	Grid grid;
	Grid temp_grid;
};
