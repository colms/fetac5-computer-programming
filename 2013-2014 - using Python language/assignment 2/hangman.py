import random # to select a random line from file
import string # to check if guess is a letter
import os # to clear the screen with "cls"

def main():
    lives = 3 # number of chances for incorrect guesses
    incorrect_guesses = "" # incorrect guesses throughout game
    all_guesses_taken = "" # all guesses taken throughout game
    hidden_word = None # the answer word e.g. "ox"
    visible_word = None # what the user sees of correct word
    game_over = False # should we continue playing?
    is_valid_guess = True # is user input valid i.e. a single letter
    unknown_letter_symbol = "-" # our symbol in place of unknown letters
    
    hidden_word = load_random_line("animals.txt")
    visible_word = setup_visible_word(unknown_letter_symbol, len(hidden_word))
        
    while game_over == False:
        display_interface(visible_word, hidden_word, incorrect_guesses, lives, is_valid_guess)
        guess = ask_user_for_guess()
        is_valid_guess = validate_guess(guess, all_guesses_taken)
        if not is_valid_guess:
            continue
        all_guesses_taken += guess
        if guess in hidden_word:
            visible_word = reveal_letter(guess, visible_word, hidden_word)
            game_over = not unknown_letter_symbol in visible_word
        else:
            incorrect_guesses += guess
            lives -= 1
            game_over = lives == 0
            
    display_interface(visible_word, hidden_word, incorrect_guesses, lives, is_valid_guess)
    if lives == 0:
        print("Game over. You lost!")
    else:
        print("Congratulations! You guessed correctly!")

# selects a random word from file, e.g. "ox"
def load_random_line(file_name):
    file = open(file_name, "r")
    text = file.read()
    lines = text.splitlines()
    return random.choice(lines)

# returns word the user will see, e.g. "--"
def setup_visible_word(symbol, num_symbols):
    return symbol * num_symbols

# our pretty display of informtion
def display_interface(visible_word, hidden_word, incorrect_guesses, lives, is_valid_guess):
    os.system("cls")
    if is_valid_guess:
        print("")
    else:
        print("Guess must be a single letter from a to z that hasn't already been guessed")
    print("hidden word:", hidden_word)
    print("visible word:", visible_word)
    print("incorrect guesses:", incorrect_guesses)
    print("lives:", lives)
    draw_hangman(lives)

# our ASCII gallows and hangman
def draw_hangman(lives):
    #if lives == 3, draw first stage ... etc
    pass

# take input from user and lowercase it
def ask_user_for_guess():
    return input("Guess a letter: ").lower()
    
# check if the guess meets all criteria to be valid, 
# i.e. is a single, previously unguessed letter
def validate_guess(guess, all_guesses_taken):
    if not guess in string.ascii_lowercase:
        return False
    elif guess in all_guesses_taken:
        return False
    elif len(guess) != 1:
        return False
    else:
        return True

# reveal guessed letter e.g. "--" => "ox" if guess is "o"
# and correct word is "ox"
def reveal_letter(guess, visible_word, hidden_word):
    new_word = ""
    for index, letter in enumerate(hidden_word):
        if letter == guess:
            new_word += guess
        else:
            new_word += visible_word[index]
    return new_word
    
if __name__ == "__main__":
    main()