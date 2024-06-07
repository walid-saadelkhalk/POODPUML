#ifndef DATA_HPP
#define DATA_HPP

#include "Player.hpp"

// Function to write the data of the player in a json file
// The data is written with the player, the number of death, the number of wave and the time
// The data is written in a json file

void json(const Player& player, int nb_death, int nb_wave, int time);



#endif // DATA_HPP