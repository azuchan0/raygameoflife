#include "simulation.hpp"

void Simulation::Draw() {
	grid.Draw();
}

void Simulation::SetCellValue(int row, int column, int value) {
	grid.SetValue(row, column, value);
}

void Simulation::ToggleCellValue(int row, int column) {
	grid.SetValue(row, column, 1 - grid.GetValue(row, column));
}

void Simulation::Clear() {
	grid.Clear();
}

int Simulation::CountLiveNeighbors(int row, int column)
{
	int live_neighbors = 0;
	std::vector<std::pair<int, int>> neighborOffsets = {
		{-1, 0}, // above
		{1, 0}, // below
		{0, -1}, // left
		{0, 1}, // right
		{-1, -1}, // diagonal upper left
		{-1, 1}, // diagonal upper right
		{1, -1}, // diagonal lower left
		{1, 1} //diagonal lower right
	};

	for (const auto& offset : neighborOffsets) {
		int neighbor_row = (row + offset.first + grid.GetRows()) % grid.GetRows();
		int neighbor_column = (column + offset.second + grid.GetColumns()) % grid.GetColumns();
		live_neighbors += grid.GetValue(neighbor_row, neighbor_column);
	}
	return live_neighbors;
}

void Simulation::Update() {
	for (int row = 0; row < grid.GetRows(); row++) {
		for (int column = 0; column < grid.GetColumns(); column++) {
			int liveNeighbors = CountLiveNeighbors(row, column); 
			int cellValue = grid.GetValue(row, column);

			if (cellValue == 1) {
				if (liveNeighbors > 3 || liveNeighbors < 2) {
					temp_grid.SetValue(row, column, 0);
				}
				else {
					temp_grid.SetValue(row, column, 1);
				}
			}
			else {
				if (liveNeighbors == 3) {
					temp_grid.SetValue(row, column, 1);
				}
				else {
					temp_grid.SetValue(row, column, 0);
				}

			}
		}
	}
	grid = temp_grid;
}
