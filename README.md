# Subnautica

## 1. Description
Initially, you will need to read in a list of materials and recipes from a file and load them into an array of Materials. The list of materials is static,
and you can assume that the size can be stored in a constant (PROJ2_SIZE). The diver does not start with anything but can start searching for raw materials.
Anytime a raw material is found, it is added to the diver’s collection of items. Then when a specific recipe is met (two pieces of quartz becomes one piece of
glass, for example), the diver can try and merge two pieces of raw material to make an advanced material. Then two items (raw or advanced) can be combined to
build a unique item that increases the diver’s depth. The list of all available combinations is available below in section 9 of this document.

## 2. Background

Subnautica is an open-world adventure game that was initially released Unknown Worlds Entertainment in 2014. The main character of the game
(our Diver) starts after crash landing on a mostly ocean covered planet named 4546B. The player is wearing a simple scuba suit initially and
wanders around the planet exploring areas and gathering resources to build new items. For this project, you will be required to create a text-based
version of this game.

In this implementation of Subnautica, you will be implementing the role of the Diver. For our purposes, the Diver can search for basic materials
(such as lead or titanium), combine basic material into advanced material, and then combine advanced material into unique diving equipment. The goal
is to build equipment to allow us to exceed the 1000-meter mark for our diving depth.

## 3. Overview
In this project, you will:<br>
  *	Practice basic C++ syntax including branching structures
  *	Write classes and instantiate those classes using a constructor
  *	Use arrays to hold objects
  *	Use simple file input
  *	Practice breaking projects into multiple files
  *	Use a makefile to compile a project
