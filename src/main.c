#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <string.h>


#define DRUGS 6

unsigned int day = 1;

typedef enum {
    EASY,
    MEDIUM,
    HARD,
    SUPER_HARD
} Game_Modes;


typedef enum {
    DRUG_WEED,
    DRUG_COCAINE,
    DRUG_HEROIN,
    DRUG_ACID,
    DRUG_SPEED,
    DRUG_LUDES,
    NUM_DRUGS
} Drug;

typedef struct{
    uint32_t drugs[DRUGS];
    int bank;
    int debt;
} Stash;

typedef struct{
    uint32_t drugs[DRUGS];
    int cash;
    int guns;
} TrenchCoat;


void loan_shark_loan(Stash *s, int amount) {
    s->bank += amount;
    s->debt += amount;
};

void loan_shark_repayment(TrenchCoat *tc, Stash *s,int amount) {
   s->debt -= amount;
   tc->cash -= amount;
};




void purchase_drug(TrenchCoat *tc, Drug drug, int quantity, int price) {
    int total_cost = quantity * price;

    if (tc->cash < total_cost) {
        printf("Not enough cash\n");
        return;
    }

    tc->cash -= total_cost;

    tc->drugs[drug] += quantity;

    printf("Purchased %d units of drug %d\n", quantity, drug);
}



enum Reputation {
    TERRIBLE,
    BAD,
    NEUTRAL,
    GOOD,
    EXCELLENT
};


typedef struct{
    char town[40];
    enum Reputation rp;
} location;



int increment_day() {
    day += 1;
}

typedef enum {
    PRICE_CHEAP,
    PRICE_NORMAL,
    PRICE_EXPENSIVE,
    PRICE_LUXURY
} PriceTier;


void purchase_travel(TrenchCoat *tc,  location l) {

    int total_cost = rand() % 500;


    if ( tc->cash < total_cost ) {
        printf("Not enough cash\n");
        return;
    }

    tc->cash -= total_cost;
    increment_day();
    printf("Traveling to %s\n", l.town); 
};

    






int get_random_price(PriceTier tier) {
    switch(tier) {
        case PRICE_CHEAP:
            return rand() % 50 + 50;
        case PRICE_NORMAL:
            return rand() % 100 + 100;
    }
}

typedef struct {
    char event[20];
    int (*action) (TrenchCoat *tc);
} PoliceEvent;

int police_encounter(TrenchCoat *tc, Stash *s) {
    memset(&tc, 0, sizeof(tc));
    int fine = 500 + rand() % 500;
    s->debt += fine;
    printf("You are released from jail. You owe $%d in fine.\n", fine);

}

int arrest(TrenchCoat *tc, Stash *s) {
    memset(&tc, 0, sizeof(tc));
    int fine = 500 + rand() % 500;
    s->debt += fine;
};
    


int print_rule() {
    FILE *rlptr;
    rlptr = fopen("rules.txt", "r");

    if (rlptr == NULL) {
        perror("Not able to find rules.txt");
        return EXIT_FAILURE;
    }

    char rules[100];
    
    while(fgets(rules, 100, rlptr)) {
        printf("%s", rules);
    }

    fclose(rlptr);
}


void game_mode_map(Game_Modes gm) {
    
    switch(gm) {

        case EASY:
            printf("easy");
            break;
        case MEDIUM:
            printf("medium");
            break;
        case HARD:
            printf("hard");
            break;
        case SUPER_HARD:
            printf("super hard");
        default:
            break;
    }
}















int main() {
    Stash s;
    TrenchCoat tc;
    Game_Modes gm = EASY;

    game_mode_map(gm);


    tc.cash = 1000000000;

    location l; 
    strcpy(l.town, "Broward");

    purchase_drug(&tc, DRUG_COCAINE, 5, 1200);

    purchase_travel(&tc, l); 

    print_rule();

}
