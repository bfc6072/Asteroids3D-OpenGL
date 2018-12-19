/*
Authors: Barrington Campbell & Kaloyana Mihova
Class: IGME.309.03
Proffesor: David Schwartz

File Name: Menu.h
Description: This is the menu object class. This manages what menu screen is being displayed to the player.
*/

#pragma once
#include "GameObject.h"
#include "Shader.h"
class Menu : public GameObject {
	std::vector<unsigned int> menus; //List of int's associated to the different menu lookups
	bool isChangeable; //Keeps player from accidentally going through all menus on one click
	bool isPaused;
	unsigned int pauseLookup;

public:
	Menu(string const &path, std::vector<unsigned int> MenuIndex, unsigned int pause);
	bool InMenu() { return menus.size() > 0; }				//True if the player is in a menu sequence
	unsigned int CurrentMenu() { return menus.front(); }	//Returns current menu lookup Int
	unsigned int Pause() { return pauseLookup; }
	bool GetPause() { return isPaused; }
	void SetPause(bool value)
	{
		isPaused = !isPaused;
		isPaused == true ? menus.push_back(pauseLookup) : menus.erase(menus.begin());
	}
	void Next() { menus.erase(menus.begin()); }				//Goes to next menu screen
	bool GetChangeable() { return isChangeable; }			//Detects if the screen can be changed
	void SetChangeable(bool value) { isChangeable = !isChangeable; }//Set's the changable bool value
};

inline Menu::Menu(string const &path, std::vector<unsigned int> MenuIndex, unsigned int pause) : GameObject(path)
{
	menus = MenuIndex;
	isChangeable = true;
	pauseLookup = pause;
	isPaused = false;
}