This assignment will test your ability to create, use, manipulate and solve problems using linked lists. To do this, you will be implementing a crepe stand order manager using a linked list of business days, each containing a list of crepe orders.

We have defined some structs in the provided code to get you started. You may add fields to any of the structs if you wish.


struct day;

  Purpose: To store all the information about a single business day's orders of crepes. This will form a linked list of business days by pointing to the next day (or NULL).

struct crepe;

  Purpose: To store all the information about a single crepe. This will form a linked list of crepes by pointing to the next one (or NULL).

struct date;

  Purpose: Stores a date as 3 different numbers, the year, month and date.

The following enum definitions are also provided for you. You can create your own enums if you would like, but you should not modify the provided enums.

enum batter_type { ORIGINAL, CHOCOLATE, MATCHA };

  Purpose: To represent the different types of batter a crepe can have.

enum topping_type { NO_TOPPING, BANANA, STRAWBERRY, NUTELLA };

  Purpose: To represent the different types of topping a crepe can have.
