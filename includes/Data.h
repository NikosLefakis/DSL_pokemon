#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <functional>
#include <cmath>
#define coutln Coutln::output()

class Pokemon;
class Ability;
class Round;

std::vector<Pokemon *> allPokemons;
std::vector<Ability *> allAbilities;
std::vector<int> x;
std::function<void()> ability_tmp;

std::vector<std::function<void()>>afterAbilities_p1;
std::vector<int>afterIndex_p1;
std::vector<std::function<void()>>forAbilities_p1;
std::vector<int>forIndex_p1;

std::vector<std::function<void()>>afterAbilities_p2;
std::vector<int>afterIndex_p2;
std::vector<std::function<void()>>forAbilities_p2;
std::vector<int>forIndex_p2;

Pokemon *player1;
Pokemon *player2;
Pokemon *learn;
Round *rounds;
int isActive;
bool check;
int turn = 0;
int which = 0;
int roundsss;


class Round {
    private:
        int current_round = 1;

    public:
        Round() {}

        /* Getters */
        int getCurrentRound() {
            return this->current_round;
        }

        /* Setters */
        void setCurrentRound(int round) {
            this->current_round = round;
        }

        void nextRound() {
            this->current_round++;
        }
};

class Ability {
    private:
        std::string ability_name;
        std::function<void()> ability_action;

    public:
        /* Constructor */
        Ability(std::string ability_name,std::function<void()> ability_action) : ability_name(ability_name),ability_action(ability_action) {
            /* Ability's name must not have space. */
            assert(ability_name.find(' ') == std::string::npos && "Ability's name must not contain a space.");

            /* Check if Ability Name Exists */
            for (const Ability *exist : allAbilities) {
                if (exist->ability_name == ability_name) {
                    std::cerr << "Ability with name '" + ability_name + "' is already created." << std::endl;
                    assert(false);
                }
            }

            allAbilities.push_back(this);
        };

        /* Default Constructor */
        Ability() {}

        /* Getters */
        std::string getAbilityName() {
            return ability_name;
        }

        std::function<void()> getAbilityAction() {
            return ability_action;
        }
      
        /* Setters */
        void setAbilityName(std::string ability_name) {
            this->ability_name = ability_name;
        }

        void setAbilityAction(std::function<void()> ability_action) {
            this->ability_action = ability_action;
        }
};

class Abilities {
    public:
        /* Constructor */
        Abilities() {}

        /* [] overloading */
        void operator[](Ability *ability) {}
};

class dummyClass {}; /* For POKEBALL ATTACKER/DEFENDER _ */

class dummyClassPokeball { /* For POKEBALL ATTACKER/DEFENDER ---α */
    public:
        dummyClassPokeball operator--() {
            return *this;
        }

        dummyClassPokeball operator-() {
            return *this;
        }
};

class Pokemon {
    private:
        std::string name;
        std::string type;
        int hp;
        int max_hp;
        bool inPokeball = true;
        std::vector<Ability *> abilities;
    
    public:
        /* Constructor */
        Pokemon(std::string name,std::string type,int hp) : name(name),type(type),hp(hp) {
            /* Pokemon with that name is already created */
            for (const Pokemon *exist : allPokemons) {
                if (exist->name == name) {
                    std::cerr << "Pokemon with name '" + name + "' is already created." << std::endl;
                    assert(false);
                }
            }

            /* Pokemon's HP must be positive */
            assert(hp > 0 && "Pokemon's HP must be positive.");

            /* Pokemon's Type must be one of them (Electric, Fire, Water, Grass) */
            assert((type == "Grass" || type == "Water" || type == "Fire" || type == "Electric") 
                    && "Pokemon's Type must be one of them (Electric, Fire, Water, Grass)");

            this->max_hp = hp;
            allPokemons.push_back(this);
        }

        /* Default Constructor */
        Pokemon(){}

        /* Setters */
        void setPokemonName(std::string name) {
            this->name = name;
        }

        void setPokemonType(std::string type) {
            this->type = type;
        }

        void setPokemonHP(int hp) {
            if (hp <= 0) {
                this->hp = 0;
            } else {
                this->hp = hp;
            }
        }

        void setPokemonMaxHP(int max_hp){
            this->max_hp = max_hp;
        }
        
        void setPokemoninPokeball(bool inPokeball) {
            this->inPokeball = inPokeball;
        }

        void setPokemonAbility(Ability* ability) {
            this->abilities.push_back(ability);

            /* Pokemon can have 1 - 4 abilities */
            if (this->abilities.size() == 5) {
                std::cout << "Pokemon: " << this->name << " cannot learn more abilities!" << std::endl;
                assert(false);
            }

            /* Ability already learned */
            for (size_t i=0; i<this->abilities.size()-1; i++) {
                if (abilities.at(i)->getAbilityName() == ability->getAbilityName()) {
                    std::cout << "Ability: " << ability->getAbilityName() << " is already learned!" << std::endl;
                    assert(false);
                }
            }
        }

        /* Getters */
        std::string getPokemonName() {
            return this->name;
        }

        std::string getPokemonType() {
            return this->type;
        }

        int getPokemonHP() {
            return this->hp;
        }

        int getPokemonMaxHP(){
            return this->max_hp;
        }

        bool getPokemoninPokeball() {
            return this->inPokeball;
        }

        std::vector<Ability *> getPokemonAbilities() {
            return this->abilities;
        }

        /* Print */
        friend std::ostream& operator<<(std::ostream &out,const Pokemon &pokemon) {
            out << "Name: " << pokemon.name << std::endl
                << "Type: " << pokemon.type << std::endl
                << "HP: " << pokemon.hp << std::endl
                << "inPokeball: " << (pokemon.inPokeball ? "Yes" : "No") << std::endl;

            return out;
        }

        void operator,(int value) {
            if (check == true) {
                Pokemon *attacker = (turn == 0 ? player1 : player2);
                int total_damage = value;

                // Damage increase
                if (attacker->getPokemonType() == "Fire") {
                    if (this->getPokemonType() == "Electric") {
                        total_damage = total_damage + static_cast<int>(std::round(0.2 * value));
                    } else {
                        total_damage = total_damage + static_cast<int>(std::round(0.15 * value));
                    }
                } else if (attacker->getPokemonType() == "Water") {
                    total_damage = total_damage + static_cast<int>(std::round(0.07 * value));
                } else if (attacker->getPokemonType() == "Grass") {
                    if (rounds->getCurrentRound() % 2 == 1) {
                        total_damage = total_damage + static_cast<int>(std::round(0.07 * value));
                    } else {
                        total_damage = total_damage;
                    }
                } else {
                    total_damage = total_damage;
                }

                // Resist
                if (this->getPokemonType() == "Water") {
                    total_damage = total_damage - static_cast<int>(std::round(0.07 * total_damage));
                } else if (this->getPokemonType() == "Electric") {
                    if (attacker->getPokemonType() == "Fire") {
                        total_damage = total_damage - static_cast<int>(std::round(0.3 * total_damage));
                    } else {
                        total_damage = total_damage - static_cast<int>(std::round(0.2 * total_damage));
                    }
                } else {
                    total_damage = total_damage;
                }

                if (isActive == 1) {
                    attacker->setPokemonHP(attacker->getPokemonHP() - total_damage);
                } else {
                    if (player1 == attacker) {
                        player2->setPokemonHP(player2->getPokemonHP() - total_damage);
                    } else {
                        player1->setPokemonHP(player1->getPokemonHP() - total_damage);
                    }
                }
            } else {
                Pokemon *attacker = (turn == 0 ? player1 : player2);
                int hp_val = value;
                 
                
                if (isActive == 1) {
                    if (attacker->getPokemonHP() + hp_val >= attacker->getPokemonMaxHP()) {
                        attacker->setPokemonHP(attacker->getPokemonMaxHP());
                    } else {
                        attacker->setPokemonHP(attacker->getPokemonHP() + hp_val);
                    }                
                } 
                else {
                    if (player1 == attacker) {
                        if (player2->getPokemonHP() + hp_val >= player2->getPokemonMaxHP()) {
                            player2->setPokemonHP(player2->getPokemonMaxHP());
                        } else {
                            player2->setPokemonHP(player2->getPokemonHP() + hp_val);
                        }
                    } else {
                        if (player1->getPokemonHP() + hp_val >= player1->getPokemonMaxHP()) {
                            player1->setPokemonHP(player1->getPokemonMaxHP());
                        } else {
                            player1->setPokemonHP(player1->getPokemonHP() + hp_val);
                        }
                    }
                }      
            }

        }

        /* POKEBALL ATTACKER/DEFENDER _ */
        void operator,(dummyClass x) {
            Pokemon *attacker = (turn == 0 ? player1 : player2);

            if (isActive == 1) {
                attacker->setPokemoninPokeball(true);
            } else {
                if (player1 == attacker) {
                    player2->setPokemoninPokeball(true);
                } else {
                    player1->setPokemoninPokeball(true);
                }
            }
        }

        /* POKEBALL ATTACKER/DEFENDER ---α */
        void operator,(dummyClassPokeball x) {
            Pokemon *attacker = (turn == 0 ? player1 : player2);

            if (isActive == 1) {
                attacker->setPokemoninPokeball(false);
            } else {
                if (player1 == attacker) {
                    player2->setPokemoninPokeball(false);
                } else {
                    player1->setPokemoninPokeball(false);
                }
            }
        }
};

class Pokemons {
    public:
        /* Constructor */
        Pokemons() {}

        /* [] overloading */
        void operator[](Pokemon *pokemon) {}
};

class Coutln {
    public:
        /* std::cout with new line at the end */
        template <typename T>
        Coutln &operator<<(const T& message) {
            std::cout << message << "\n";
            return *this;
        }

        /* #define coutln Coutln::output() */
        static Coutln& output() {
            static Coutln output;
            return output;
        }
};


Ability* select_ability_player1() {
    int index = -1;
    std::string input;

    do {
        std::cout << player1->getPokemonName() << "(Player 1) select ability:" << std::endl;
        std::cout << "------------------------------" << std::endl;
        
        for (size_t i=0; i<player1->getPokemonAbilities().size(); i++) {
            std::cout << player1->getPokemonAbilities().at(i)->getAbilityName() << std::endl;
        }
        std::cout << "------------------------------" << std::endl;
        std::cin >> input;
        
        for (size_t i=0; i<player1->getPokemonAbilities().size(); i++) {
            if (input == player1->getPokemonAbilities().at(i)->getAbilityName()) {
                index = i;
                break;
            }
        }
        std::cout << std::endl;

    } while(index == -1);

    return player1->getPokemonAbilities().at(index);
}

Ability* select_ability_player2() {
    int index = -1;
    std::string input;

    do {
        std::cout << player2->getPokemonName() << "(Player 2) select ability:" << std::endl;
        std::cout << "------------------------------" << std::endl;
        
        for (size_t i=0; i<player2->getPokemonAbilities().size(); i++) {
            std::cout << player2->getPokemonAbilities().at(i)->getAbilityName() << std::endl;
        }
        std::cout << "------------------------------" << std::endl;
        std::cin >> input;
        
        for (size_t i=0; i<player2->getPokemonAbilities().size(); i++) {
            if (input == player2->getPokemonAbilities().at(i)->getAbilityName()) {
                index = i;
                break;
            }
        }
        std::cout << std::endl;

    } while(index == -1);

    return player2->getPokemonAbilities().at(index);
}

void printStats() {
    std::cout << "##############################" << std::endl;
    std::cout << "Name: " << player1->getPokemonName() << std::endl;
    std::cout << "HP: " << player1->getPokemonHP() << std::endl;
    std::cout << "Pokemon " << (player1->getPokemoninPokeball() == true ? "in" : "out of") << " Pokeball" << std::endl;
    std::cout << "##############################" << std::endl << std::endl << std::endl;

    std::cout << "##############################" << std::endl;
    std::cout << "Name: " << player2->getPokemonName() << std::endl;
    std::cout << "HP: " << player2->getPokemonHP() << std::endl;
    std::cout << "Pokemon " << (player2->getPokemoninPokeball() == true ? "in" : "out of") << " Pokeball" << std::endl;
    std::cout << "##############################" << std::endl;
}

void clear() {
    for (size_t i=0; i<afterAbilities_p1.size(); i++) {
        if (afterIndex_p1.at(i) == 0) {
            afterAbilities_p1.erase(afterAbilities_p1.begin() + i);
            afterIndex_p1.erase(afterIndex_p1.begin() + i);
        }
    }

    for (size_t i=0; i<afterAbilities_p2.size(); i++) {
        if (afterIndex_p2.at(i) == 0) {
            afterAbilities_p2.erase(afterAbilities_p2.begin() + i);
            afterIndex_p2.erase(afterIndex_p2.begin() + i);
        }
    }

    for (size_t i=0; i<forAbilities_p1.size(); i++) {
        if (forIndex_p1.at(i) == 0) {
            forAbilities_p1.erase(forAbilities_p1.begin() + i);
            forIndex_p1.erase(forIndex_p1.begin() + i);
        }
    }

    for (size_t i=0; i<forAbilities_p2.size(); i++) {
        if (forIndex_p2.at(i) == 0) {
            forAbilities_p2.erase(forAbilities_p2.begin() + i);
            forIndex_p2.erase(forIndex_p2.begin() + i);
        }
    }
}

void duel() {
    Ability *ability;
    rounds = new Round();

    std::cout << "-------------------------------------POKEMON THE GAME-------------------------------------" << std::endl;
    
    std::string input;
    int index = -1;

    do {
        std::cout << std::endl;
        std::cout << "Player1 select pokemon:" << std::endl << "---------------------------" << std::endl;

        for (size_t i=0; i<allPokemons.size(); i++) {
            std::cout << allPokemons.at(i)->getPokemonName() << std::endl;
        }

        std::cout << "---------------------------" << std::endl;
        std::cin >> input;

        for (size_t i=0; i<allPokemons.size(); i++) {
            if (allPokemons.at(i)->getPokemonName() == input) {
                index = i;
                break;
            }
        }
    } while (index == -1);

    player1 = new Pokemon();
    player1->setPokemonName(allPokemons.at(index)->getPokemonName());
    player1->setPokemonType(allPokemons.at(index)->getPokemonType());
    player1->setPokemonHP(allPokemons.at(index)->getPokemonHP());
    player1->setPokemonMaxHP(allPokemons.at(index)->getPokemonMaxHP());

    if (allPokemons.at(index)->getPokemonAbilities().size() == 0) {
        std::cout << "Pokemon does not have abilities. Please add at least one ability." << std::endl;
        assert(false);
    }

    for (size_t i=0; i<allPokemons.at(index)->getPokemonAbilities().size(); i++) {
        player1->setPokemonAbility(allPokemons.at(index)->getPokemonAbilities().at(i));
    }

    player1->setPokemoninPokeball(false);

    input = "";
    index = -1;

    do {
        std::cout << std::endl;
        std::cout << "Player2 select pokemon:" << std::endl << "---------------------------" << std::endl;

        for (size_t i=0; i<allPokemons.size(); i++) {
            std::cout << allPokemons.at(i)->getPokemonName() << std::endl;
        }

        std::cout << "---------------------------" << std::endl;
        std::cin >> input;

        for (size_t i=0; i<allPokemons.size(); i++) {
            if (allPokemons.at(i)->getPokemonName() == input) {
                index = i;
                break;
            }
        }
    } while (index == -1);

    player2 = new Pokemon();
    player2->setPokemonName(allPokemons.at(index)->getPokemonName());
    player2->setPokemonType(allPokemons.at(index)->getPokemonType());
    player2->setPokemonHP(allPokemons.at(index)->getPokemonHP());
    player2->setPokemonMaxHP(allPokemons.at(index)->getPokemonMaxHP());
    
    if (allPokemons.at(index)->getPokemonAbilities().size() == 0) {
        std::cout << "Pokemon does not have abilities. Please add at least one ability." << std::endl;
        assert(false);
    }

    for (size_t i=0; i<allPokemons.at(index)->getPokemonAbilities().size(); i++) {
        player2->setPokemonAbility(allPokemons.at(index)->getPokemonAbilities().at(i));
    }

    player2->setPokemoninPokeball(false);

    std::cout << std::endl;

    while(player1->getPokemonHP() > 0 && player2->getPokemonHP() > 0) {
        coutln << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
        std::cout << "Round " << rounds->getCurrentRound() << std::endl;
        coutln << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

        /* Grass Type Effect */
        if ((rounds->getCurrentRound() != 1) && (rounds->getCurrentRound() % 2 == 0)) {
            if (player1->getPokemonType() == "Grass") {
                int hp_val = player1->getPokemonMaxHP() * 0.05;

                if (player1->getPokemonHP() + hp_val >= player1->getPokemonMaxHP()) {
                    player1->setPokemonHP(player1->getPokemonMaxHP());
                } else {
                    player1->setPokemonHP(player1->getPokemonHP() + hp_val);
                }
            } else if (player2->getPokemonType() == "Grass") {
                int hp_val = player2->getPokemonMaxHP() * 0.05;

                if (player2->getPokemonHP() + hp_val >= player2->getPokemonMaxHP()) {
                    player2->setPokemonHP(player2->getPokemonMaxHP());
                } else {
                    player2->setPokemonHP(player2->getPokemonHP() + hp_val);
                }
            }
        }

        /* Player 1*/        
        which = 0;

        if (player1->getPokemoninPokeball() == false) {
            ability = select_ability_player1();
            ability->getAbilityAction()();

            if (which == 1) {
                forIndex_p1.push_back(roundsss);
                forAbilities_p1.push_back(ability_tmp);
            } else if (which == 2) {
                afterIndex_p1.push_back(roundsss);
                afterAbilities_p1.push_back(ability_tmp);
            }

            printStats();
        } else {
            std::cout << player1->getPokemonName() << "(Player 1) has not a pokemon out of pokeball so he can't cast an ability." << std::endl;
        }
        std::cout << std::endl;

        if (player2->getPokemonHP() == 0 || player1->getPokemonHP() == 0) {
            break;
        }

        turn = 1;

        /* Player 2 */
        which = 0;
        
        if (player2->getPokemoninPokeball() == false) {
            ability = select_ability_player2();
            ability->getAbilityAction()();

            if (which == 1) {
                forIndex_p2.push_back(roundsss);
                forAbilities_p2.push_back(ability_tmp);
            } else if (which == 2) {
                afterIndex_p2.push_back(roundsss);
                afterAbilities_p2.push_back(ability_tmp);
            }

            printStats();
        } else {
            std::cout << player2->getPokemonName() << "(Player 2) has not a pokemon out of pokeball so he can't cast an ability." << std::endl;
        }
        std::cout << std::endl;

        /* After */
        turn = 0;

        for (size_t i=0; i<afterAbilities_p1.size(); i++) {
            if (afterIndex_p1.at(i) == 1) {
                afterAbilities_p1.at(i)();
            }

            afterIndex_p1.at(i)--;
        }

        turn = 1;

        for (size_t i=0; i<afterAbilities_p2.size(); i++) {
            if (afterIndex_p2.at(i) == 1) {
                afterAbilities_p2.at(i)();
            }

            afterIndex_p2.at(i)--;
        }

        /* For */
        turn = 0;

        for (size_t i=0; i<forAbilities_p1.size(); i++) {
            if (forIndex_p1.at(i) > 0) {
                forAbilities_p1.at(i)();
            }

            forIndex_p1.at(i)--;
        }

        turn = 1;

        for (size_t i=0; i<forAbilities_p2.size(); i++) {
            if (forIndex_p2.at(i) > 0) {
                forAbilities_p2.at(i)();
            }

            forIndex_p2.at(i)--;
        }

        turn = 0;
        rounds->nextRound();
    }

    clear();

    if (player1->getPokemonHP() > 0) {
        std::cout << "Player1 with " << player1->getPokemonName() << " Won!" <<std::endl << std::endl;
    } else {
        std::cout << "Player2 with " << player2->getPokemonName() << " Won!" <<std::endl << std::endl;
    }
}

/* List for AND */
template <typename T>
bool and_list(T arg) {
    return arg;
}

template <typename T,typename... Args>
bool and_list(T arg,Args... args) {
    return arg && and_list(args...);
}

/* Default 2 args */
template <typename T>
bool and_function(T arg1,T arg2) {
    return arg1 && arg2;
}

/* 3 or more Args */
template <typename T,typename... Args>
bool and_function(T arg1,T arg2,Args... args) {
    return arg1 && arg2 && and_list(args...);
}

/* List for OR */
template <typename T>
bool or_list(T arg) {
    return arg;
}

template <typename T,typename... Args>
bool or_list(T arg,Args... args) {
    return arg || or_list(args...);
}

/* Default 2 args */
template <typename T>
bool or_function(T arg1,T arg2) {
    return arg1 || arg2;
}

/* 3 or more Args */
template <typename T,typename... Args>
bool or_function(T arg1,T arg2,Args... args) {
    return arg1 || arg2 || or_list(args...);
}

Pokemon* search_pokemon(std::string name) {
    for (size_t i=0; i<allPokemons.size(); i++) {
        if (allPokemons.at(i)->getPokemonName() == name) {
            return allPokemons.at(i);
        }
    }

    std::cout << "Pokemon with name: " << name << " not found!" << std::endl;
    assert(false);
}

int index(std::string ability_name,Pokemon *pokemon) {
    for (size_t i=0; i<allAbilities.size(); i++) {
        if (allAbilities.at(i)->getAbilityName() == ability_name) {
            pokemon->setPokemonAbility(allAbilities.at(i));
            return 0;
        }
    }

    std::cout << "Ability with name: " << ability_name << " not found!" << std::endl;
    assert(false);
}

Pokemon* search_pokemon(Pokemon *pokemon,int x) {
    return pokemon;
}

Pokemon* getAttacker() {
    isActive = 1;

    if (turn == 0) {
        return player1;
    } else {
        return player2;
    }
}

Pokemon* getDefender() {
    isActive = 2;

    if (turn == 0) {
        return player2;
    } else {
        return player1;
    }
}

#endif