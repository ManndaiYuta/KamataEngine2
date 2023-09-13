#pragma once
typedef struct Vec2 
{
	int X;
	int Y;
}Vec2;

typedef struct Transform 
{
	Vec2 Center;
	int Rad;
	int Spd;
	int Color;
}Transform;