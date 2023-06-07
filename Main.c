#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Defing all the maximum capacities at various places
#define MAX_WAITING 3
#define MAX_EATING 3
#define MAX_CAPACITY 10

//Defining the characteristics of the customer after he ate at the restaurant
typedef struct
{
  char name[50];
  long unsigned mobile_no;
  char ordered_food[20];
}
customer_after;

//Defining the arrays
char waiting_customers[MAX_WAITING][50];
customer_after eating_customers[MAX_EATING], previous_customers[MAX_CAPACITY];
int user_type;
int frontw = -1, rearw = -1, fronte = -1, reare = -1, top = -1;

//Function Prototypes
void enqueue_into_waiting_area(char *name_of_customer);  
char* deque_waiting_customer(); 
void display_no_of_waiting_customers();
void display_eating_customers();  
void display_previous_customers();  
void remove_an_eating_customer();  
void serve_customer(char customer[]); 
void display_menu();   
char* food_item(int food_choice);  
void enqueue_into_eating_area(char *customer, long unsigned mobile_no, char *food);  
bool waiting_area_has_place();  
bool eating_area_has_place();  
void push_into_previous_customers(char *satisfied_customer_name, long unsigned satisfied_customer_mobile_no, char *food_eaten_by_satisfied_customer); 

//Main function starts******************************************************************************************
int main()
{
  int repeat1 = 1, repeat2 = 1, ch1, ch2, flag;
  int password;
  char name_of_customer[50];

  //Get to know if the user is customer or manager
  do
  {  
    do
    {
      printf("Please choose an option\n\n");
      printf("1. I am the manager\n");
      printf("2. I am a customer\n");
      printf("\nEnter option: ");

      scanf("%d", &ch1);

      switch(ch1)
      {
        case 1:
          printf("\nPlease enter password: ");
          scanf("%d", &password);

          if (password == 2004)
          {
            user_type = 1;
            repeat1 = 2;
          }
          else
          {
            printf("Invalid password\n");
          }
          break;

        case 2:
          printf("Welcome to Maharasoi\n");
          user_type = 2;
          repeat1 = 2;
          break;

        default:
          printf("Invalid input. Please try again.\n");
          break;
      }
    }
    while(repeat1 == 1);

    if (user_type == 1)
    {
      do
      {
        printf("Please enter an option\n\n");
        printf("1. See no. of waiting customers\n");
        printf("2. See customers currently being served\n");
        printf("3. See previous customers\n");
        printf("4. Make a customer complete his food.\n");
        printf("5. Exit\n");
        printf("\nEnter option: ");
        scanf("%d", &ch2);

        switch(ch2)
        {
          case 1:
            display_no_of_waiting_customers();
            break;

          case 2:
            display_eating_customers();
            break;

          case 3:
            display_previous_customers();
            break;

          case 4:
            remove_an_eating_customer();
            break;

          case 5:
            printf("Exiting....\n");
            break;

          default:
            printf("Invalid Input");
        }

        printf("\n\nWould you like to see some other data?\n1. Yes\n2. No\n\nPlease enter option: ");
        scanf("%d", &repeat2);
      }
      while (repeat2 == 1);
    }

    else if(user_type == 2)
    {
      if(waiting_area_has_place())
      {
        if(eating_area_has_place())
        {
          printf("Please have a seat. May I know your name, please: ");
          scanf("%s", name_of_customer);

          serve_customer(name_of_customer);       
        }
        else
        {
          printf("Our eating area is currently full. Please wait for some time.\n\n");
          printf("Time is but an illusion  --  Albert Einstein\n\n");

          printf("May I know your name, please: ");
          scanf("%s", name_of_customer);
          printf("Thank you. We will soon call you when our eating area has place.\n");
          enqueue_into_waiting_area(name_of_customer);
        }
      }
      else
      {
        printf("We are sorry but our servers are down :(");
      }
    }

    printf("\n\n\nWould you like to go to start?\n1. Yes\n2. No\n\nPlease choose an option: ");
    scanf("%d", &flag);
  }
  while(flag == 1);
}
//Main function ends********************************************************************************************

//People entering the waiting room
void enqueue_into_waiting_area(char *name_of_customer)
{
  if(frontw==-1)
  {
    frontw = 0;
  }
  if(rearw == MAX_WAITING - 1)
  {
    rearw = 0;
    strcpy(waiting_customers[rearw], name_of_customer);
    return;
  }
  else
  {
    rearw++;
    strcpy(waiting_customers[rearw], name_of_customer);
    return;
  }
}

//Removes a customer from the waiting area
char* deque_waiting_customer()
{
  char* wait_customer = (char*)malloc(50 * sizeof(char));

  if (frontw == -1)
  {
    printf("No customers in waiting area\n");
    return NULL;
  }

  strcpy(wait_customer, waiting_customers[frontw]);

  if (frontw == rearw)
  {
    frontw = -1;
    rearw = -1;
  }
  else if (frontw == MAX_WAITING - 1)
  {
    frontw = 0;
  }
  else
  {
    frontw++;
  }

  return wait_customer;
  free(wait_customer);
}

//Displays the number of customers in waiting area
void display_no_of_waiting_customers()
{
  int count = 0;

  int i = frontw;
  
  if (i <= rearw)
  {
    for (i = frontw; i <= rearw; i++)
    {
      count++;
    }
  }
  else
  {
    while(i <= MAX_WAITING - 1)
    {
      count++;
      i++;
    }
    
    i = 0;
    
    while (i <= rearw)
    {
      count++;
      i++;
    }
  }

  printf("\n%d people are in waiting area.", count);
  return;
}

//Displays the name of eating customers
void display_eating_customers()
{
  int count = 0;
  
  if(fronte == -1)
  {
    printf("There are no customers in the eating area\n");
    return;
  }
  
  int i = fronte;

  if (i <= reare)
  {
    for (int i = fronte; i <= reare; i++)
    {
      puts(eating_customers[i].name);
    }
  }
  else
  {
    while(i <= MAX_EATING - 1)
    {
      puts(eating_customers[i].name);
      i++;
    }
    
    i = 0;
    
    while (i <= reare)
    {
      puts(eating_customers[i].name);
      i++;
    }
  }
}

//Displays the details of previous customers
void display_previous_customers()
{
  if(top == -1)
  {
    printf("No previous customers.\n");
    return;
  }
  else
  {
    for (int i = 0; i <= top; i++)
    {
      puts(previous_customers[i].name);
      printf("%lu", previous_customers[i].mobile_no);
      printf("\n");
      puts(previous_customers[i].ordered_food);
      printf("\n");
    }
    return;
  }
}
 
//Dequeues an eating customer
void remove_an_eating_customer()
{
  char satisfied_customer_name[50];
  long unsigned satisfied_customer_mobile_no;
  char food_eaten_by_satisfied_customer[20];
  char* waited_customer = (char*)malloc(50 * sizeof(char));

  if (fronte == -1)
  {
    printf("There are no customers in the eating area");
    return;
  }

  strcpy(satisfied_customer_name, eating_customers[fronte].name);
  satisfied_customer_mobile_no = eating_customers[fronte].mobile_no;
  strcpy(food_eaten_by_satisfied_customer, eating_customers[fronte].ordered_food);

  if (fronte == reare)
  {
    fronte = -1;
    reare = -1;
  }
  else if (fronte == MAX_EATING - 1)
  {
    fronte = 0;
  }
  else
  {
    fronte++;
  }

  push_into_previous_customers(satisfied_customer_name, satisfied_customer_mobile_no, food_eaten_by_satisfied_customer);
  printf("One customer left\n");
  waited_customer = deque_waiting_customer();

  printf("\n\nWelcome to our restaurant, %s", waited_customer);

  serve_customer(waited_customer);
}

//Function to serve customers
void serve_customer(char customer[])
{
  int food_choice;
  char* food = (char*) malloc (50 * sizeof(char));
  long unsigned  mobile_no;

  printf("\nPlease enter your contact number: ");
  scanf("%lu", &mobile_no);
     
  printf("Thank you very much. What would you like to order?\n");
  display_menu();
  printf("\nPlease enter your choice: ");
  scanf("%d", &food_choice);
  food = food_item(food_choice);
  printf("Thank you for the order. Here is your %s", food);

  enqueue_into_eating_area(customer, mobile_no, food);
}

//Shows the menu to customers
void display_menu()
{
  printf("Menu of Maharasoi\n\n\n");
  printf("1. Thali\n2. Dal roti\n3. Masala Dosa\n4. Idli Sambar\n\n\n");
  return;
}

//Returns the chosen food item
char* food_item(int food_choice)
{
  int check = 0;

  do
  {
    switch(food_choice)
    {
      case 1:
        check = 1;
        return "Thali";
      case 2:
        check = 1;
        return "Dal-roti";
      case 3:
        check = 1;
        return "Masala Dosa";
      case 4:
        check = 1;
        return "Idli Sambar";
      default:
        printf("Incorrect option\nChoose again.");
        break;
    }
  }
  while(check == 0);
}

//Enqueues the eating area
void enqueue_into_eating_area(char *customer, long unsigned mobile_no, char *food)
{
  if(fronte == -1)
  {
    fronte = 0;
  }

  if(reare == MAX_EATING - 1)
  {
    reare = 0;
    strcpy(eating_customers[reare].name, customer);
    strcpy(eating_customers[reare].ordered_food, food);
    eating_customers[reare].mobile_no = mobile_no;
  }
  else
  {
    reare++;
    strcpy(eating_customers[reare].name, customer);
    strcpy(eating_customers[reare].ordered_food, food);
    eating_customers[reare].mobile_no = mobile_no;
  }
  return;
}

//Checks if waiting area has place
bool waiting_area_has_place()
{
  if(rearw == MAX_WAITING - 1 && frontw == 0 || frontw == rearw + 1)
  {
    return false;
  }
  else
  {
    return true;
  }
}

//Checks if eating area has place
bool eating_area_has_place()
{
  if(fronte == 0 && reare == MAX_EATING - 1 || fronte == reare + 1)
  {
    return false;
  }
  else
  {
    return true;
  }
}

void push_into_previous_customers(char *satisfied_customer_name, long unsigned satisfied_customer_mobile_no, char *food_eaten_by_satisfied_customer)
{
   if(top == MAX_CAPACITY - 1)
   {
      printf("Capacity breach\n");
      return;
   }
   else
   {
      top++;
      strcpy(previous_customers[top].name, satisfied_customer_name);
      strcpy(previous_customers[top].ordered_food,  food_eaten_by_satisfied_customer);
      previous_customers[top].mobile_no = satisfied_customer_mobile_no;
   }
}
