#pragma once
#include "GameObject.h"
#include "Shader.h"
class Menu : public GameObject {
	std::vector<unsigned int> menus;
	bool isChangeable; //Keeps player from accidentally going through all menus on one click
public:
	Menu(string const &path, std::vector<unsigned int> MenuIndex);
	bool InMenu() { return menus.size() > 0; }
	unsigned int CurrentMenu() { return menus.front(); }
	void Next() { menus.erase(menus.begin()); }
	bool GetChangeable() { return isChangeable; }
	void SetChangeable(bool value) { isChangeable = value; }
};

inline Menu::Menu(string const &path, std::vector<unsigned int> MenuIndex) : GameObject(path)
{
	menus = MenuIndex;
	isChangeable = true;
}