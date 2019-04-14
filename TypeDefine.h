#pragma once

////////////////////Math Types

enum MathType : int
{
	Matrix3Size = 3,
	Matrix3TotalSize = Matrix3Size * Matrix3Size,
};

enum class State
{
	EActive,
	EPause,
	EDead,
};




const int thickness = 15;
const float paddleH = 100.0f;