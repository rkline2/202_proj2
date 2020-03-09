/*************************************************
** File: Diver.cpp
** 
** Project: CMSC 202 Project 2, Spring 2020
**
** Author: Rooklyn Kline
**
** Date: 3/10/2020
**
** Section: 23
**
** E-mail: rkline2@umbc.edu
**
** This file has all of the functions located
** in the Diver class. It stores all of the player's information 
** inside of the member variables. The majority of these 
** functions will be used in the Game.cpp file to receive information
** about the player (Diver).
**
*************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "Diver.h"
#include "Material.h"
#include "Game.h"
using namespace std;

// Default Constructor: Diver
// Automatically builds a new diver
Diver::Diver() {
    m_myName = "Player";
    m_numMaterials = 0;
}


// Override Constructor: Diver
// Given a name, changes the diver's name
Diver::Diver(string name) {
    m_myName = name;
    m_numMaterials = 0;
}

// GetName
// Returns the name of the diver
string Diver::GetName() {
    return m_myName;
}

// SetName
// Given a string, changes the player's name
void Diver::SetName(string name) {
    m_myName = name;
}

// DisplayMaterials
// Displays the known materials from the player 
void Diver::DisplayMaterials() {
   for (int i = 0; i < PROJ2_SIZE; i++) {
        cout << i + 1 << ". " << m_myMaterials[i].m_name;
        cout << " " << m_myMaterials[i].m_quantity << endl;
    }
}

// CheckMaterial
// Given the material, returns the index
// if the quantity is greater than zero
int Diver::CheckMaterial(Material item) {
    for (int index = 0; index < PROJ2_SIZE; index++) {
        if (m_myMaterials[index].m_name == item.m_name) {
            return index;
        }
    }
    return INVALID;
}

// AddMaterial
// Given the material, copies the
// material to m_myMaterials
void Diver::AddMaterial(Material item) {
    m_myMaterials[m_numMaterials] = item;
    m_numMaterials++;
}


// IncrementQuantity
// Given the material, increments the material's
// quantity by one
void Diver::IncrementQuantity(Material item) {
        m_myMaterials[CheckMaterial(item)].m_quantity++;
}

// DecrementQuantity
// Given the material, returns true if the
// materials quantity is greater than zero
bool Diver::DecrementQuantity(Material item) {
    if (m_myMaterials[CheckMaterial(item)].m_quantity <= 0) {
        return false;
    }
    else {
        m_myMaterials[CheckMaterial(item)].m_quantity--;
    }
}

// CheckQuantity
// Given two materials, retruns true if BOTH materals
// have enough to merge. Otherwise, it retuns false. 
bool Diver::CheckQuantity(Material item_a, Material item_b) {
    if (item_a.m_quantity == 0 || item_b.m_quantity == 0) {
        return false;
    }
    else if ((item_a.m_name == item_b.m_name) && item_a.m_quantity < TWO_VAL) {
        return false;
    }
    return true;
}


// GetMaterial
// Given the index, returns the
// material from  m_myMaterials  
Material Diver::GetMaterial(int index) {
    return m_myMaterials[index];
}


// CalcDepth
// Returns the sum of all of depth
// points from m_myMaterials 
int Diver::CalcDepth() {
    int sum = 0;
    for (int i = MIN_UNIQUE; i < PROJ2_SIZE; i++) {
        if (m_myMaterials[i].m_quantity > 0) {
            sum += (m_myMaterials[i].m_depth * m_myMaterials[i].m_quantity);
        }
    }
    return sum;
}
