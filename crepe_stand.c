// Assignment 2 24T1 COMP1511: Crepe Stand
// crepe_stand.c
//
// This program was written by z5258155 Ryan Tchan
// on 2024-04-12
//
// Version 1.0.0: Assignment released.
//
// This is a C program that details the amount/type of orders on given days
// at a crepe stand

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crepe_stand.h"

#define SIG_STRAWBERRY 's'
#define SIG_MATCHA 'm'
#define SIG_CHOCOLATE 'c'
#define NO_SIG_SOLD 'n'
#define NO_SIG_MOST_POP 'N'

// Add any extra #includes your code needs here.
#include <assert.h>

// Your enums go here:


// Add your own #defines here:


////////////////////////////////////////////////////////////////////////////////

// A single crepe
//      Stores all the information about a single crepe.
//      Forms a linked list of crepes by pointing to the next one (or NULL).
struct crepe {
    // Name of the customer who ordered the crepe
    char customer_name[MAX_STR_LEN];

    // The batter the crepe will be made out of
    // ORIGINAL, CHOCOLATE or MATCHA
    enum batter_type batter;

    // There can be no topping or one topping
    // NO_TOPPING, BANANA, STRAWBERRY, NUTELLA
    enum topping_type topping;

    // Whether or not the crepe is gluten free;
    // Can be 1 or 0
    int is_gluten_free;

    // Size of the crepe in centimeters
    int diameter_cm;

    // A pointer to the next crepe in the orders list
    // Is NULL if this crepe is the tail of the list.
    struct crepe *next;

    // Position of the crepe in the list of orders
    int position;
};

// A particular day’s list of orders
struct day {
    // Date of the day as a struct day, with fields year, month, day
    struct date date;

    // A pointer to the start of the list of this day's orders
    struct crepe *orders;

    // The total income for the day
    // i.e. the total summed price of all crepes
    double income;

    // A pointer to the next day's orders
    // Is NULL if this day is the tail of the list.
    struct day *next;
};

// Add any other structs you define here.

////////////////////////////////////////////////////////////////////////////////

// Add prototypes for any extra functions you create here.

// Stage 1


// Creates a new custom crepe
//
// Parameters:
//      customer_name - name of customer ordering
//      batter - batter base of crepe
//      topping - topping for the crepe
//      is_gluten_free - 1 if it is GF, 0 if not
//      diameter_cm - how large crepe is in cm
// Returns:
//      pointer to newly created struct crepe
//
struct crepe *create_crepe(char *customer_name,
                           enum batter_type batter,
                           enum topping_type topping,
                           int is_gluten_free,
                           int diameter_cm);

struct crepe *insert_at_tail(struct day *current_day,
                             struct crepe *crepe_order);
                            

// Stage 2
               
struct crepe *linked_list_check(struct crepe *insert_crepe,
                                struct day *current_day,
                                int placement);

double pricing_list(struct day *current_day,
                    struct crepe *current);

// Stage 3


// Stage 4


// You need to implement the following functions.
// You can find descriptions of what each function
// should do in crepe_stand.h

//////////////////////////////////////////////////////////////////////
//                        Stage 1 Functions                         //
//////////////////////////////////////////////////////////////////////

// Provided Function stubs:

struct day *create_day(struct date new_date) {
    // TODO: implement this function
    struct day *day_one = malloc(sizeof(struct day));
    day_one->date = new_date;
    day_one->orders = NULL;
    day_one->income = 0.0;
    day_one->next = NULL;

    return day_one;
}

struct crepe *create_crepe(char *customer_name,
                           enum batter_type batter,
                           enum topping_type topping,
                           int is_gluten_free,
                           int diameter_cm) {
    // TODO: implement this function
    struct crepe *new_crepe = malloc(sizeof(struct crepe));
    strcpy(new_crepe->customer_name, customer_name);
    new_crepe->batter = batter;
    new_crepe->topping = topping;
    new_crepe->is_gluten_free = is_gluten_free;
    new_crepe->diameter_cm = diameter_cm;
    new_crepe->next = NULL;
    new_crepe->position = 0;

    return new_crepe;
}

int append_crepe_custom(struct day *current_day,
                        char *customer_name,
                        enum batter_type batter,
                        enum topping_type topping,
                        int is_gluten_free,
                        int diameter_cm) {
    // TODO: implement this function
    struct crepe *crepe_order = create_crepe(customer_name, batter, 
        topping, is_gluten_free, diameter_cm);
    crepe_order->is_gluten_free = is_gluten_free;
    crepe_order->diameter_cm = diameter_cm;

    if (batter > 3 || batter < 0) {

        return -2;
    } else if (topping > 3 || batter < 0) {

        return -3;
    } else if (is_gluten_free < 0 || is_gluten_free > 1) {

        return -4;
    } else if (diameter_cm < 10 || !(diameter_cm <= 40)) {

        return -5;
    } else {
        crepe_order = insert_at_tail(current_day, crepe_order);

        return 0;
    }
}

int append_crepe_signature(struct day *current_day,
                           char *customer_name,
                           char *crepe_type) {
    // TODO: implement this function
    if (strcmp(crepe_type, "matcha") == 0) {
        struct crepe *crepe_order = create_crepe(customer_name, 
            MATCHA, STRAWBERRY, 0, 25);
        crepe_order = insert_at_tail(current_day, crepe_order);
    
    } else if (strcmp(crepe_type, "strawberry") == 0) {
        struct crepe *crepe_order = create_crepe(customer_name, 
            ORIGINAL, STRAWBERRY, 1, 25);
        crepe_order = insert_at_tail(current_day, crepe_order);

    } else if (strcmp(crepe_type, "chocolate") == 0) {
        struct crepe *crepe_order = create_crepe(customer_name, 
            CHOCOLATE, NUTELLA, 0, 25);
        crepe_order = insert_at_tail(current_day, crepe_order);
    } 

    return VALID_CREPE;
}

void print_crepes(struct day *current_day) {
    // TODO: implement this function
    
    if (current_day->orders == NULL) {
        print_no_crepes();
    } else {
        struct crepe *current = current_day->orders;                               
        int count = 1;
        while (current != NULL) {
            print_single_crepe(current, current->position);
            if (current->next != NULL) {
                print_arrow();
            }
            count++;
            current = current->next;
        }
    }   
}

int count_crepes(struct day *current_day) {
    // TODO: implement this function
    if (current_day->orders == NULL) {
        return 0;
    } else {
        int count = 1;
        struct crepe *curr = current_day->orders;
        while (curr->next != NULL) {
            count++;
            curr = curr->next;
        }

        return count;
    }
}

// Your functions go here (include function comments):

// a function that traverses the linked list until next = NULL
struct crepe *insert_at_tail(struct day *current_day,
                             struct crepe *crepe_order) {
        
    if (current_day->orders == NULL) {
        current_day->orders = crepe_order;
        crepe_order->position = 1;
        return current_day->orders; 
    } 
    struct crepe *current = current_day->orders;
    while (current->next != NULL) {
        current = current->next;
    }
    crepe_order->position = current->position + 1;
    current->next = crepe_order;

    return current_day->orders;
}


//////////////////////////////////////////////////////////////////////
//                        Stage 2 Functions                         //
//////////////////////////////////////////////////////////////////////

// Provided function stubs:

int insert_crepe_custom(struct day *current_day,
                        int position,
                        char *customer_name,
                        enum batter_type batter,
                        enum topping_type topping,
                        int is_gluten_free,
                        int diameter_cm) {
    // TODO: implement this function
    struct crepe *insert_crepe = create_crepe(customer_name, batter, 
        topping, is_gluten_free, diameter_cm);
    

    if (position < 1) {

        return -6;
    } else if (batter > 3 || batter < 0) {

        return -2;
    } else if (topping > 3 || batter < 0) {

        return -3;
    } else if (is_gluten_free < 0 || is_gluten_free > 1) {

        return -4;
    } else if (diameter_cm < 10 || !(diameter_cm <= 40)) {

        return -5;
    } else {
        insert_crepe = linked_list_check(insert_crepe, current_day, position);

        return 0;
    }
}

int insert_crepe_signature(struct day *current_day,
                           int position,
                           char *customer_name,
                           char *crepe_type) {
    // TODO: implement this function
    if (strcmp(crepe_type, "matcha") == 0) {
        struct crepe *insert_crepe = create_crepe(customer_name, MATCHA, 
            STRAWBERRY, 0, 25);

        if (position < 1) {

            return -6;
        }
        insert_crepe = linked_list_check(insert_crepe, current_day, position);
        insert_crepe->position = position;
    } else if (strcmp(crepe_type, "strawberry") == 0) {
        struct crepe *insert_crepe = create_crepe(customer_name, ORIGINAL, 
            STRAWBERRY, 1, 25);

        if (position < 1) {

            return -6;
        }
        insert_crepe = linked_list_check(insert_crepe, current_day, position);
        insert_crepe->position = position;
    } else if (strcmp(crepe_type, "chocolate") == 0) {
        struct crepe *insert_crepe = create_crepe(customer_name, CHOCOLATE, 
            NUTELLA, 0, 25);

        if (position < 1) {

            return -6;
        }
        insert_crepe = linked_list_check(insert_crepe, current_day, position);
        insert_crepe->position = position;
           
    }

    return 0;
}

struct stats get_stats(struct day *current_day) {
    // TODO: implement this function
    struct crepe *current = current_day->orders;
    struct stats *current_stats = malloc(sizeof(struct stats));
    current_stats->total_crepes = 0;
    current_stats->original = 0;
    current_stats->chocolate = 0;
    current_stats->matcha = 0;
    current_stats->gluten_free = 0;
    current_stats->popular_topping = NO_TOPPING;
    current_stats->small = 0;
    current_stats->medium = 0;
    current_stats->large = 0;
    
    int banana = 0;
    int strawberry = 0;
    int nutella = 0;
    int none = 0;

    if (current_day->orders == NULL) {
        return *current_stats;
    }
    while (current != NULL) {
        if (current->batter == ORIGINAL) {
            current_stats->original++;
        } else if (current->batter == CHOCOLATE) {
            current_stats->chocolate++;
        } else if (current->batter == MATCHA) {
            current_stats->matcha++;
        }
        if (current->is_gluten_free == 1) {
            current_stats->gluten_free++;
        }
        if (current->topping == BANANA) {
            banana++;
        } else if (current->topping == STRAWBERRY) {
            strawberry++;
        } else if (current->topping == NUTELLA) {
            nutella++;
        } else if (current->topping == NO_TOPPING) {
            none++;
        } 
        if (current->next == NULL) {
            if (none > banana && none > nutella && none > strawberry) {
                current_stats->popular_topping = NO_TOPPING;
            } else if (banana > strawberry && banana > nutella && 
                       banana > none) {
                current_stats->popular_topping = BANANA;
            } else if (strawberry > banana && strawberry > nutella && 
                       strawberry > none) {
                current_stats->popular_topping = STRAWBERRY;
            } else if (nutella > strawberry && nutella > banana && 
                       nutella > none) {
                current_stats->popular_topping = NUTELLA;
            } 
        }
        if (current->diameter_cm >= 10 && current->diameter_cm < 20) {
            current_stats->small++;
        } else if (current->diameter_cm >= 20 && current->diameter_cm < 30) {
            current_stats->medium++;
        } else if (current->diameter_cm >= 30 && current->diameter_cm < 40) {
            current_stats->large++;
        }
        current_stats->total_crepes++;
        current = current->next;
    }
    
    return *current_stats;
}

double calculate_price(struct day *current_day, int position) {
    // TODO: implement this function
    struct crepe *current = current_day->orders;
    double price = 0.0;
    
    if (position < 1) {
        return -6;
    } else if (position == 1) {
        price = pricing_list(current_day, current);
        return price;
    }
    int counter = 1;
    while (current->next != NULL && counter != position) {
        counter++; 
        current = current->next;
    }
    if (counter == position) {
        price = pricing_list(current_day, current);    
    } else if (counter != position || current == NULL) {
        return -6;
    } 

    return price;
}   

double total_income(struct day *current_day) {
    // TODO: implement this function
    struct crepe *current = current_day->orders;
    struct crepe *counter = current_day->orders;
    double total_income = 0;
    int count = 0;
    while (counter != NULL) {
        count++;
        counter = counter->next;
    }
    int position = 0;
    while (current != NULL && count != position) {
        double crepe_price = 0.0;
        position++;
        crepe_price = calculate_price(current_day, position);
        total_income = total_income + crepe_price;
        current = current->next;
    }

    return total_income;
}

struct bill customer_bill(struct day *current_day, char *customer_name) {
    // TODO: implement this function
    struct crepe *current = current_day->orders;
    struct bill *order = malloc(sizeof(struct bill));
    double customer_bill = 0.0;
    int crepe_count = 0;

    while (current != NULL) {
        if (strcmp(current->customer_name, customer_name) == 0) {
            double crepe_price = 0.0;
            crepe_price = calculate_price(current_day, current->position);
            customer_bill = customer_bill + crepe_price;
            crepe_count++;
        }
        current = current->next;
    }
    order->total_price = customer_bill;
    order->crepe_count = crepe_count;

    return *order;
}

// Your functions go here (include function comments):

// a function that checks if the linked list is empty and/or if the list 
// contains only 1 node. if the position is after the linked list ends then 
// the struct is added to the end of the list
struct crepe *linked_list_check(struct crepe *insert_crepe,
                                struct day *current_day,
                                int position) {
    insert_crepe->position = position;
    int counter = 1;
    int inserted_flag = 0;

    if (current_day->orders == NULL && position == 1) {
        current_day->orders = insert_crepe;

        return insert_crepe;
    }
    if (current_day->orders != NULL && position == 1) {
        insert_crepe->next = current_day->orders;
        current_day->orders = insert_crepe;
        inserted_flag = 1;
    }
    struct crepe *current = current_day->orders;
    while (current != NULL) {
        if (counter + 1 == position) {
            
            insert_crepe->next = current->next;
            current->next = insert_crepe;
            inserted_flag = 1;
        }
        current->position = counter;
        current = current->next;
        counter++;
    }
    if (inserted_flag == 0) {
        insert_at_tail(current_day, insert_crepe);
    }

    return insert_crepe;
}

// a function that calculates the price of a particular crepe order
double pricing_list(struct day *current_day,
                    struct crepe *current) {

    double price = 0.0;
    if (current->batter == ORIGINAL) {
        price += 8.0;
    } else if (current->batter == CHOCOLATE) {
        price += 8.0;
    } else if (current->batter == MATCHA) {
        price += 9.5;
    }
    if (current->is_gluten_free == 1) {
        price += 0.6;
    }
    if (current->topping == BANANA) {
        price += 2.0;
    } else if (current->topping == STRAWBERRY) {
        price += 2.0;
    } else if (current->topping == NUTELLA) {
        price += 3.5;
    } 
    if (current->diameter_cm >= 20 && current->diameter_cm < 30) {
        price += 2.5;
    } else if (current->diameter_cm >= 30 && current->diameter_cm < 40) {
        price += 3.5;
    }
    
    return price;
}
//////////////////////////////////////////////////////////////////////
//                        Stage 3 Functions                         //
//////////////////////////////////////////////////////////////////////

// Provided function stubs:

struct day *new_day(struct day *day_one, struct date date) {
    // TODO: implement this function
    struct day *current_day = day_one;
    struct day *new_day = create_day(date);

    if (current_day->date.year > new_day->date.year) {
        new_day->next = current_day;
    } else if (current_day->date.year < new_day->date.year) {
        current_day->next = new_day;
    } else if (current_day->date.year == new_day->date.year) {
        if (current_day->date.month > new_day->date.month) {
            new_day->next = current_day;
        } else if (current_day->date.month < new_day->date.month) {
            current_day->next = new_day;
        } else if (current_day->date.month == new_day->date.month) {
            if (current_day->date.day > new_day->date.day) {
                new_day->next = current_day;
            } else if (current_day->date.day < new_day->date.day) {
                current_day->next = new_day;
            } else if (current_day->date.day == new_day->date.day) {

                return NULL;
            }
        } 
    }

    return day_one;
}

void display_days(struct day *day_one, struct day *current_day) {
    // TODO: implement this function
/*
    struct day *curr_day = day_one;
    while (curr_day != NULL) {
        if ()
    }

    while (current_day != NULL) {
        print_single_day(current_day, current_day->date, , 
                         current_day->income);
        if (current_day->next != NULL) {
            print_arrow();
        }
        current_day = current_day->next;
    }

*/
    exit(1);
}

struct day *cycle_days(char command,
                       struct day *day_one,
                       struct day *current_day) {
    // TODO: implement this function
    printf("Cycle Days not yet implemented.\n");
    exit(1);
}

int remove_crepe(struct day *current_day, int position) {
    // TODO: implement this function
    printf("Remove Crepe not yet implemented.\n");
    exit(1);
}

struct day *remove_day(struct day *day_one,
                       struct day **current_day,
                       struct date date) {
    // TODO: implement this function
    printf("Remove Day not yet implemented.\n");
    exit(1);
}

void free_crepe_stand(struct day *day_one) {
    // TODO: implement this function
}

// Your functions here (include function comments):


//////////////////////////////////////////////////////////////////////
//                        Stage 4 Functions                         //
//////////////////////////////////////////////////////////////////////

// Provided function stubs:

struct profits compare_weekday_end(struct day *day_one) {
    // TODO: implement this function
    printf("Compare Weekday end not yet implemented.\n");
    exit(1);
}

struct max_profit max_profit_period(struct day *day_one, int year) {
    // TODO: implement this function
    printf("Max Profit Period not yet implemented.\n");
    exit(1);
}

// Your functions here (include function comments):


//////////////////////////////////////////////////////////////////////
//                         Helper Functions                         //
//////////////////////////////////////////////////////////////////////

void print_single_crepe(struct crepe *crepe, int position) {
    printf("---------------------\n");
    printf("%d. %s's crepe\n", position, crepe->customer_name);

    if (crepe->batter == ORIGINAL) {
        printf("Original flavour\n");
    } else if (crepe->batter == MATCHA) {
        printf("Matcha flavour\n");
    } else {
        printf("Chocolate flavour\n");
    }

    printf("Toppings: ");
    if (crepe->topping == NO_TOPPING) {
        printf("none\n");
    } else if (crepe->topping == BANANA) {
        printf("bananas\n");
    } else if (crepe->topping == STRAWBERRY) {
        printf("strawberries\n");
    } else if (crepe->topping == NUTELLA) {
        printf("nutella\n");
    }

    printf("gluten free? ");
    if (crepe->is_gluten_free) {
        printf("yes\n");
    } else {
        printf("no\n");
    }

    printf("Size: %dcm\n", crepe->diameter_cm);
    printf("---------------------\n");
}

void print_arrow(void) {
    printf("\t|\n\tv\n");
}

void print_no_crepes(void) {
    printf("No crepes have been ordered yet!\n");
}

void print_single_day(int is_current_day,
                      struct date date,
                      char most_pop,
                      double income) {
    printf("---------------------\n");
    if (is_current_day) {
        printf("!CURRENT DAY!\n");
    }
    printf("Date: %04d-%02d-%02d\n", date.year, date.month, date.day);
    if (most_pop == SIG_STRAWBERRY) {
        printf("Most popular signature crepe: Strawberry Special\n");
    } else if (most_pop == SIG_MATCHA) {
        printf("Most popular signature crepe: Matcha Madness\n");
    } else if (most_pop == SIG_CHOCOLATE) {
        printf("Most popular signature crepe: Chocolate Connoisseur\n");
    } else if (most_pop == NO_SIG_SOLD) {
        printf("There were no signature crepes sold!\n");
    } else if (most_pop == NO_SIG_MOST_POP) {
        printf("No signature crepe was more popular than another!\n");
    } else {
        printf("ERROR: %c, unknown most popular character\n", most_pop);
    }
    printf("Total income: $%.2lf\n", income);
    printf("---------------------\n");
}
