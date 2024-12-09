#pragma once
#include "Tree.h"
#include <vector>
#include <raylib.h>

class Programm 
{
	bool Running;
	bool InputWord;
	bool DeleteDuplicates;

public:
	Programm() : Running(1), InputWord(0), DeleteDuplicates(0) {};
	~Programm() = default;
	
	bool GetRun() { return Running; };
	bool GetInW() { return InputWord; };
	bool GetDeD() { return DeleteDuplicates; };
	
	void SetRun(bool _v) { Running = _v; }
	void SetInW(bool _v) { InputWord = _v; }
	void SetDeD(bool _v) { DeleteDuplicates = _v; }
};

void UI(Tree tree);

int count_letter(Node* node, char target);

void draw_tree_recursive(Node* node, Vector2 pos, float horizontalOffset, float verticalStep, int level, Tree& tree);

Vector2 offset_to_circle(Vector2 from, Vector2 to, float radius);