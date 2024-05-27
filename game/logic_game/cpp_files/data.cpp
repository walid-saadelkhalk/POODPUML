#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>

int json(int nb_death, int nb_wave, int time) {
    // Read the existing JSON file
    std::ifstream i("data.json");
    nlohmann::json j;
    
    // Check if the file is empty
    if (i.peek() == std::ifstream::traits_type::eof()) {
        // The file is empty
        // Initialize it with an empty JSON array
        j = nlohmann::json::array();
    } else {
        // The file is not empty, parse it
        i >> j;
    }

    // Add scores
    nlohmann::json joueur;
    joueur["nom"] = "Sam Gamgee";
    joueur["death"] = nb_death;
    joueur["wave"] = nb_wave;
    joueur["time"] = time;
    j.push_back(joueur);

    // Write the updated JSON object to the file
    std::ofstream o("data.json");
    o << j << std::endl;

    std::cout << joueur["nom"] << " a terminé la partie avec " << joueur["death"] << " morts et " << joueur["wave"] << " vagues. En " << joueur["time"] << " secondes." << std::endl;

    return 0;
}