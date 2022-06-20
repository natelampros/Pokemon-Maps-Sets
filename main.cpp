#include <iostream>
#include <fstream>
#include <sstream>
#include "HashMap.h"

using namespace std;

int main(int argc, char * argv[]) {
    if (argc < 3)
    {
        cerr << "Please provide name of input and output files";
        return 1;
    }
    cout << "Input file: " << argv[1] << endl;
    ifstream in(argv[1]);
    if (!in)
    {
        cerr << "Unable to open " << argv[1] << " for input";
        return 1;
    }
    cout << "Output file: " << argv[2] << endl;
    ofstream out(argv[2]);
    if (!out)
    {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
    }


//    Set<int> mySet;
//    out << "My Set: " << endl;
//    mySet.insert(9);
//    mySet.insert(4);
//    mySet.insert(7);
//    mySet.insert(8);
//    out << "SIZE: " << mySet.size() << endl;
//    out << mySet.toString() << endl;
//    out << "Clear" << endl;
//    mySet.clear();
//    out << mySet.toString() << endl;


    Set<string> mySet;
    HashMap<string, string> pokemon;
    HashMap<string, string> moves;
    HashMap<string,Set<string>> effectivities;
    HashMap<string,Set<string>> ineffectivities;

    for (string line; getline(in, line);) {
        try {
            string commandLine, itemValue;
            if (line.size() == 0) continue;

            istringstream iss(line);
            iss >> commandLine;


            if (commandLine == "Set:"){
                string items;
                out << line << endl;

                while(iss >> items){
                    mySet.insert(items);
                }

                out << "  [" << mySet.toString() << "]\n" << endl ;
                mySet.clear();
            }
            else if (commandLine == "Pokemon:") {
                string pokemonName;
                string pokemonType;
                iss >> pokemonName;
                iss >> pokemonType;
                out << line << endl;
                pokemon[pokemonName] = pokemonType;
            }
            else if (commandLine == "Move:") {
                string move;
                string moveType;
                iss >> move;
                iss >> moveType;
                out << line << endl;
                moves[move] = moveType;
            }
            else if (commandLine == "Effective:") {
                string items;
                string key;
                out << line << endl;
                iss >> key;
                while(iss >> items){
                    mySet.insert(items);
                }
                effectivities[key] = mySet;

                mySet.clear();
            }
            else if (commandLine == "Ineffective:") {
                string items;
                string key;
                out << line << endl;
                iss >> key;
                while(iss >> items){
                    mySet.insert(items);
                }
                ineffectivities[key] = mySet;

                mySet.clear();
            }
            else if (commandLine == "Pokemon") {
                out << endl << "Pokemon: ";
                out << pokemon.toString();
            }
            else if (commandLine == "Moves") {
                out << endl << "Moves: ";
                out << moves.toString();

            }
            else if (commandLine == "Effectivities") {
                out << endl << "Effectivities: ";
                out << effectivities.toString();
            }
            else if (commandLine == "Ineffectivities") {
                out << endl << "Ineffectivities: ";
                out << ineffectivities.toString();
            }
            else if (commandLine == "Battle:") {
                out << line << endl;
                string pokemon1, move1, pokemon2, move2;
                iss >> pokemon1 >> move1 >> pokemon2 >> move2;
                out << pokemon1 << " (" << move1 << ") vs " << pokemon2 << " (" << move2 << ")" << endl;
                //Charmander (flamethrower) vs Squirtle (water_gun)

                size_t effective1To2 = effectivities[moves[move1]].count(pokemon[pokemon2]);
                size_t ineffective1To2 = ineffectivities[moves[move1]].count(pokemon[pokemon2]);
                size_t effective2To1 = effectivities[moves[move2]].count(pokemon[pokemon1]);
                size_t ineffective2To1 = ineffectivities[moves[move2]].count(pokemon[pokemon1]);

                size_t score = 2 + effective2To1 - effective1To2 - ineffective2To1 + ineffective1To2;

                if (effective1To2) {
                    out << "   " << pokemon1 << "'s " << move1 << " is super effective against " << pokemon2 << endl;
                }
                else if (ineffective1To2) {
                    out << "   " << pokemon1 << "'s " << move1 << " is ineffective against " << pokemon2 << endl;
                }
                else {
                    out << "   " << pokemon1 << "'s " << move1 << " is effective against " << pokemon2 << endl;
                }

                if (effective2To1) {
                    out << "   " << pokemon2 << "'s " << move2 << " is super effective against " << pokemon1 << endl;
                }
                else if (ineffective2To1) {
                    out << "   " << pokemon2 << "'s " << move2 << " is ineffective against " << pokemon1 << endl;
                }
                else {
                    out << "   " << pokemon2 << "'s " << move2 << " is effective against " << pokemon1 << endl;
                }

                if (score == 2) {
                    out << "  The battle between " << pokemon1 << " and " << pokemon2 << " is a tie." << endl;
                }
                else {
                    out << "  In the battle between " << pokemon1 << " and " << pokemon2 << ", " << (score < 2 ? pokemon1 : pokemon2) << " wins!" << endl;
                }
            }
        }
        catch (string error) {
            out << error << endl;
        }
    }


    in.close();
    out.close();

    in.open(argv[2]);

    string line;
    if (in.is_open()) {
        while (getline(in, line)) {
            try {
                //if (line.empty()) continue;
                cout << line << endl;
            } catch (exception &e) { cout << e.what(); }
        }
    } else cout << "Unable to read from output file." << endl;
    in.close();
}
