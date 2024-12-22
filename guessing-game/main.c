#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MIN_NUM 1
#define MAX_NUM 100
#define MAX_GSS 10

int gen_rand() {
  srand(time(NULL));
  return (rand() % MAX_NUM) + MIN_NUM;
}

char *f_num(int num){
  char *formatted = (char *)malloc(10 * sizeof(char));
  if (formatted == NULL) return NULL;

  if (num < 0) {
    sprintf(formatted, "  ---  ");
    return formatted;
  }

  int tmp_num = num;
  int num_len = 0;

  while (tmp_num != 0) {
    tmp_num /= 10;
    num_len++;
  }

  switch (num_len) {
    case 1:
      sprintf(formatted, "  %d    ", num);
      break;
    case 2:
      sprintf(formatted, "  %d   ", num);
      break;
    case 3:
      sprintf(formatted, "  %d  ", num);
      break;
    default:
      sprintf(formatted, "  %d ", num);
      break;
  }

  return formatted;
}

int get_uin() {
  int user_input;

  printf("Your guess: ");
  scanf("%d", &user_input);

  return user_input;
}

int c_gss(int gss, int num) {
  if (gss == -1) return 0;

  if (gss < num) return 1;
  else if (gss > num) return 2;
  else return 3;
}

void dsp_cl() {
  system("clear");
}

void dsp_wlcm() {
  printf("Welcome to the Guessing Game!\n");
  printf("I'm thinking of a number between 1 and 100. Can you guess it?\n");
  printf("You have %d attempts. Good luck!\n\n", MAX_GSS);
}

void dsp_gss(int gss[], int rand_n) {
  char gss_st[4][10] = {"  ---  ", "  low  ", "  high ", "  hit  "};

  printf("┌───────┬───────┐\n");
  printf("│ guess │  too  │\n");
  printf("├───────┼───────┤\n");
  for (int i = 0; i < MAX_GSS; i++) {
    int gss_sti = c_gss(gss[i], rand_n);
    printf("│%s│%s│\n", f_num(gss[i]), gss_st[gss_sti]);
  }
  printf("└───────┴───────┘\n");
}

int main() {
  int gss_n[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
  int attmp = 0;
  int rand_n = gen_rand();
  int gss_in;

  while (attmp < MAX_GSS) {
    char temp;
    char inv_msg[100];

    dsp_cl();                  // clear screen
    dsp_wlcm();                // welcome messages
    dsp_gss(gss_n, rand_n);    // guess table
    
    printf("\n");
    printf("You have %d attempts left!\n", MAX_GSS - attmp);

    if (strlen(inv_msg) > 0) printf(inv_msg);                       // check if inv_msg available

    printf("Your guess: ");
    if (scanf("%d", &gss_in) == 1) {
      if (gss_in >= MIN_NUM && gss_in <= MAX_NUM) {                 // check if input are in range
        gss_n[attmp] = gss_in;
        attmp++;
        inv_msg[0] = '\0';
      } else {
        snprintf(inv_msg, sizeof(inv_msg), "Invalid input! Please enter a number between %d and %d.\n", MIN_NUM, MAX_NUM);
      }
    } else {
      snprintf(inv_msg, sizeof(inv_msg), "Invalid input! Please enter a valid number.\n");
      while ((temp = getchar()) != '\n' && temp != EOF);            // clear invalid input from the buffer
    }
    
    if (gss_in == rand_n) break;
  }

  dsp_cl();                   // clear screen
  dsp_wlcm();                 // welcome messages
  dsp_gss(gss_n, rand_n);     // guess table

  printf("\n%s ", (gss_in == rand_n) ? "Congratulations! You've guessed right!" : "Game Over!");
  printf("My number are %d.\n", rand_n);

  return 0;
}

