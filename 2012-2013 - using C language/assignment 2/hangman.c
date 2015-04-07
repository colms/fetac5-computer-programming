
#include <stdbool.h> // bool
#include <stdio.h> // FILE
#include <string.h> // strcpy, strlen
#include <time.h> // time
#include <stdlib.h> // rand
#include <ctype.h> // tolower

bool has_no_lives(int lives);
bool are_all_letters_visible(char visible_word[]);
int load_random_word_from_file(char correct_word_buffer[], char file_name[]);
bool is_guess_in_word(char guess, char correct_word[]);
char ask_user_for_guess();
void make_letter_visible(char guess, char visible_word[],
                         char correct_word[]);
void setup_visible_word(char visible_word_buffer[], char correct_word[]);
void display_end_game_message(char correct_word[],
                              char error_message[], char visible_word[],
                              char incorrect_guesses[], int lives);
bool is_input_valid(char guess, char incorrect_guesses[],
                    char error_message_buffer[]);
bool already_guessed_letter(char guess, char all_guess_taken[]);
bool is_a_letter(char guess);
void display_interface(char correct_word[],
                       char error_message[], char visible_word[],
                       char incorrect_guesses[], int lives);
void select_line_from_file(int line_number, FILE *my_file, char correct_word_buffer[]);
int count_lines_in_file(FILE *my_file);
int select_random_line_number_from_file(FILE *my_file);

int main() {
    char guess;
    bool guessed_correctly;
    int num_guesses_taken = 0;
    int num_incorrect_guesses = 0;
    int lives = 3;
    char incorrect_guesses[4] = {'\0'};
    char all_guess_taken[30] = {'\0'};
    char correct_word[50];
    char visible_word[50];
    char error_message[100] = "\n";
    bool game_over = false;
    bool input_is_valid;
    int file_error;

    file_error = load_random_word_from_file(correct_word, "C:\\animals.txt");
    if (file_error != 0) {
        printf("Error: File not found.");
        return file_error;
    }

    setup_visible_word(visible_word, correct_word);
    while(game_over == false) {
        display_interface(correct_word, error_message, visible_word,
                          incorrect_guesses, lives);
        guess = ask_user_for_guess();
        input_is_valid = is_input_valid(guess, all_guess_taken, error_message);
        if (!input_is_valid){
            continue;
        }
        guess = tolower(guess);
        all_guess_taken[num_guesses_taken] = guess;
        ++num_guesses_taken;
        guessed_correctly = is_guess_in_word(guess, correct_word);
        if (guessed_correctly == true) {
            make_letter_visible(guess, visible_word, correct_word);
            game_over = are_all_letters_visible(visible_word);
        } else {
            incorrect_guesses[num_incorrect_guesses] = guess;
            ++num_incorrect_guesses;
            --lives;
            game_over = has_no_lives(lives);
        }
    }
    display_end_game_message(correct_word, error_message, visible_word,
                      incorrect_guesses, lives);
    return 0;
}

void display_interface(char correct_word[],
                       char error_message[], char visible_word[],
                       char incorrect_guesses[], int lives) {
    system("cls");
    printf("correct word: %s\n", correct_word);
    printf("%s\n", error_message);
    printf("%s\n", visible_word);
    printf("incorrect guesses: %s\n", incorrect_guesses);
    printf("lives: %d\n", lives);
}

bool is_input_valid(char guess, char all_guess_taken[], char error_message_buffer[]) {
    if (is_a_letter(guess) == false) {
        strcpy(error_message_buffer,
               "ERROR: You can only letter a letter from a to z.\n");
        return false;
    }
    if (already_guessed_letter(guess, all_guess_taken)) {
        strcpy(error_message_buffer,
               "ERROR: You already guessed that letter\n");
        return false;
    }
    strcpy(error_message_buffer, "\n");
    return true;
}

bool is_a_letter(char guess) {
    if (guess >= 'A' && guess <= 'Z') {
        return true;
    } else if (guess >= 'a' && guess <= 'z') {
        return true;
    }
    return false;
}

bool already_guessed_letter(char guess, char all_guess_taken[]) {
    int i;
    guess = tolower(guess); // it's a letter but it might be uppercase
    for (i = 0; i < strlen(all_guess_taken); ++i) {
        if (all_guess_taken[i] == guess) {
            return true;
        }
    }
    return false;
}

void display_end_game_message(char correct_word[],
                              char error_message[], char visible_word[],
                              char incorrect_guesses[], int lives) {
    display_interface(correct_word, error_message, visible_word,
                      incorrect_guesses, lives);
    if (lives == 0) {
        printf("You lose!");
    } else {
        printf("You win!");
    }
}

bool has_no_lives(int lives) {
    return lives == 0;
}

bool are_all_letters_visible(char visible_word[]) {
    int i;
    for (i = 0; i < strlen(visible_word); ++i) {
        if (visible_word[i] == '-') {
            return false;
        }
    }
    return true;
}

int load_random_word_from_file(char correct_word_buffer[],
                               char file_name[]) {
    int random_line_number;
    FILE *my_file = fopen(file_name, "r"); // open the file for reading
    if (my_file == NULL) {
        return 2; // file not found error code
    }
    random_line_number = select_random_line_number_from_file(my_file);
    select_line_from_file(random_line_number, my_file, correct_word_buffer);
    fclose(my_file); // close the file
    return 0; // everything went well
}

int select_random_line_number_from_file(FILE *my_file) {
    srand(time(NULL));
    int num_lines_in_file = count_lines_in_file(my_file);
    int random_number = rand() % num_lines_in_file + 1;
    return random_number;
}

int count_lines_in_file(FILE *my_file) {
    int num_lines_in_file = 0;
    char line[50];
    while(fgets(line, 50, my_file) != NULL) { // NULL terminates the reading
        ++num_lines_in_file;
    }
    return num_lines_in_file;
}

void select_line_from_file(int line_number, FILE *my_file,
                           char correct_word_buffer[]) {
    char line[50];
    int num_lines_read = 0;
    rewind(my_file); // move back to the beginning of the file
    while(fgets(line, 50, my_file) != NULL) { // NULL terminates the reading
        ++num_lines_read;
        if (num_lines_read == line_number) {
            strcpy(correct_word_buffer, line);
            int null_index = strlen(correct_word_buffer) - 1;
            correct_word_buffer[null_index] = '\0';
            break;
        }
    }
}

bool is_guess_in_word(char guess, char correct_word[]) {
    int i;
    for (i = 0; i < strlen(correct_word); ++i) {
        if (correct_word[i] == guess) {
            return true;
        }
    }
    return false;
}

char ask_user_for_guess() {
    char guess;
    printf("Please enter your guess character: ");
    scanf("%c", &guess);
    _flushall();
    return guess;
}

void make_letter_visible(char guess, char visible_word[], char correct_word[]) {
    int i;
    for (i = 0; i < strlen(visible_word); ++i) {
        if (correct_word[i] == guess) {
            visible_word[i] = guess;
        }
    }
}

void setup_visible_word(char visible_word_buffer[], char correct_word[]) {
    int i;
    strcpy(visible_word_buffer, correct_word);
    for (i = 0; i < strlen(correct_word); ++i) {
        visible_word_buffer[i] = '-';
    }
    visible_word_buffer[i] = '\0';
}
