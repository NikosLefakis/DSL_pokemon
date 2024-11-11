#include "../includes/PokemonLeague.h"

BEGIN_GAME

CREATE ABILITY {
    NAME: "Bite",
    ACTION: START
        POKEBALL DEFENDER _
        AFTER 2 ROUNDS DO
            POKEBALL DEFENDER ---α
        END
    END
}

CREATE ABILITY {
    NAME: "Solar_Power",
    ACTION: START
        FOR 5 ROUNDS DO
            DAMAGE DEFENDER 8
        END
    END
}

CREATE ABILITIES [
    ABILITY {
        NAME: "Slash",
        ACTION: START
            DAMAGE DEFENDER 22
        END
    },
    ABILITY {
        NAME: "Blaze",
        ACTION: START
            HEAL ATTACKER 30
        END
    }
]

CREATE POKEMON {
    NAME: "Charizard",
    TYPE: "Fire",
    HP: 130
}

CREATE POKEMON {
    NAME: "Pikachu",
    TYPE: "Electric",
    HP: 100
}

CREATE POKEMONS [
    POKEMON {
        NAME: "Treecko",
        TYPE: "Grass",
        HP: 103
    },
    POKEMON {
        NAME: "Feraligatr",
        TYPE: "Water",
        HP: 120
    }
]

DEAR "Charizard" LEARN [
    ABILITY_NAME(Slash)
    ABILITY_NAME(Blaze)
    ABILITY_NAME(Bite)
    ABILITY_NAME(Solar_Power)
]

DEAR "Pikachu" LEARN [
    ABILITY_NAME(Slash)
    ABILITY_NAME(Blaze)
    ABILITY_NAME(Bite)
    ABILITY_NAME(Solar_Power)
]

DEAR "Treecko" LEARN [
    ABILITY_NAME(Slash)
    ABILITY_NAME(Blaze)
    ABILITY_NAME(Bite)
    ABILITY_NAME(Solar_Power)
]

DEAR "Feraligatr" LEARN [
    ABILITY_NAME(Slash)
    ABILITY_NAME(Blaze)
    ABILITY_NAME(Bite)
    ABILITY_NAME(Solar_Power)
]

DUEL

END_GAME