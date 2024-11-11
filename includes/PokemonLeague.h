#ifndef POKEMON_LEAGUE_H
#define POKEMON_LEAGUE_H

#include "Data.h"

Pokemon temp;
dummyClass _;
dummyClassPokeball α;

#define BEGIN_GAME              \
        int main() {            \
        Pokemons pokemons_tmp;  \
        Abilities abilities_tmp

#define DUEL     \
        ;        \
        duel();

#define END_GAME                                       \
        ;                                              \
        delete player1;                                \
        delete player2;                                \
        for (Pokemon *ptr : allPokemons) {delete ptr;} \
        return 0;                                      \
        }

#define CREATE ;
#define POKEMON new Pokemon
#define POKEMONS pokemons_tmp
#define NAME 0 ? "?"
#define TYPE 0 ? "?"
#define HP 0 ? 0
#define ABILITY new Ability
#define ABILITIES abilities_tmp
#define ACTION 0 ? [](){}
#define START [](){
#define END ; }

#define DAMAGE          \
        ; check = true; temp = *

#define HEAL        \
        ; check = false; temp = *

#define POKEBALL    \
        ; temp = *

#define GET_HP(pokemon) search_pokemon(pokemon 0)->getPokemonHP()
#define GET_NAME(pokemon) search_pokemon(pokemon 0)->getPokemonName()
#define GET_TYPE(pokemon) search_pokemon(pokemon 0)->getPokemonType()
#define IS_IN_POKEBALL(pokemon) search_pokemon(pokemon 0)->getPokemoninPokeball()
#define ATTACKER (getAttacker()),
#define DEFENDER (getDefender()),
#define IF if (
#define DO ) {
#define ELSE_IF \
            ;   \
            } else if (
#define ELSE    \
            ;   \
            } else {

#define SHOW               \
    ;                      \
    coutln <<         

#define AND(...) and_function(__VA_ARGS__)
#define OR(...) or_function(__VA_ARGS__)
#define NOT(x) (!x)
#define DEAR ; learn = search_pokemon(
#define LEARN ); x
#define ABILITY_NAME(ability) +index(#ability,learn)
#define FOR ; which = 1; roundsss =
#define AFTER ; which = 2; roundsss =
#define ROUNDS ; ability_tmp = [](

#endif