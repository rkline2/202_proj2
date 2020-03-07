#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "Diver.h"
#include "Material.h"
#include "Game.h"
using namespace std;

const int MIN_UNIQUE = 32;

Diver::Diver() {
    m_myName = "Player";
    m_numMaterials = 0;
}

Diver::Diver(string name) {
    m_myName = name;
    m_numMaterials = 0;
}

string Diver::GetName() {
    return m_myName;
}

void Diver::SetName(string name) {
    m_myName = name;
}

void Diver::DisplayMaterials() {
    for (int i = 0; i < PROJ2_SIZE; i++) {
        cout << i + 1 << ". " << m_myMaterials[i].m_name;
        cout << " " << m_myMaterials[i].m_quantity << endl;
    }
    
}

int Diver::CheckMaterial(Material item) {
    int invalid = -1;
    for (int index = 0; index < PROJ2_SIZE; index++) {
        if ((m_myMaterials[index].m_name == item.m_name) && (m_myMaterials[index].m_quantity > 0)) {
            return index;
        }
    }
    return invalid;
}

void Diver::AddMaterial(Material item) {
    m_myMaterials[m_numMaterials] = item;
    m_numMaterials++;
}

void Diver::IncrementQuantity(Material item) {
    for (int i = 0; i < PROJ2_SIZE; i++) {
        if (item.m_name == m_myMaterials[i].m_name) {
            m_myMaterials[i].m_quantity += 1;
        }
    }
}



bool Diver::DecrementQuantity(Material item) {
    if (item.m_quantity > 0) {
        return true;
    }
    else {
        return false;
    }
}

bool Diver::CheckQuantity(Material item_a, Material item_b) {
    if (item_a.m_quantity == 0 || item_b.m_quantity == 0) {
        return false;
    }
    else if ((item_a.m_name == item_b.m_name) && item_a.m_quantity < 2) {
        return false;
    }
    return true;
}

Material Diver::GetMaterial(int index) {
    return m_myMaterials[index];
}

int Diver::CalcDepth() {
    int sum = 0;
    for (int i = MIN_UNIQUE; i < PROJ2_SIZE; i++) {
        if (m_myMaterials[i].m_quantity > 0) {
            sum += (m_myMaterials[i].m_depth * m_myMaterials[i].m_quantity);
        }
    }
    return sum;
}
