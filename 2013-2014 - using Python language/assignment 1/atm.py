import sys

def enter_pin():
	pin_attempts_left = 3
	correct_pin = 1234
	pin = int(input("Please enter your PIN: "))
	while (pin != correct_pin):
		pin_attempts_left -= 1
		print("Incorrect PIN entered.")
		if pin_attempts_left == 0:
			print("Too many wrong PIN attempts. Please contact your nearest branch for assistance.")
			sys.exit()
		print("You have", pin_attempts_left, "attempts left.")
		pin = int(input("Please enter your PIN: "))

def action_selection():
	select_message = "Please enter the number corresponding to the action you wish to take: "
	action = None
	while True:
		print("1. Check balance")
		print("2. Withdraw")
		action = int(input(select_message))
		if action != 1 and action != 2:
			print("Select either option 1 or 2")
		else:
			break
	return action

def ask_withdrawal_amount():
	amounts = [20, 50, 60, 90, 120, 150, 180, "custom"]
	while True:
		for index, amount in enumerate(amounts):
			print(index + 1, ". ", amount, sep="")
		action = int(input("Please select an amount to withdraw: "))
		if action < 1 and action > 8:
			print("Select an option from 1 to 8")
		else:
			break
	return amounts[action - 1]

def withdraw_from_account(withdrawal_amount, account_balance, atm_balance):
	if (withdrawal_amount > atm_balance):
		print("The withdrawal amount cannot be greater than the ATM balance.")
		return 0
	elif (withdrawal_amount > account_balance):
		print("The withdrawal amount cannot be greater than your account balance.")
		return 0
	else:
		return account_balance - withdrawal_amount

def display_exit_screen(account_balance, atm_balance):
	print("Your account balance is now", account_balance, "dollars")
	print("The ATM balance is now", atm_balance, "dollars")
	print("Good bye!")

def main():
	check_balance = 1
	withdraw = 2
	account_balance = 200
	atm_balance = 250
	withdrawal_amount = None
	print("Welcome to the ATM.")
	#enter_pin()
	action = action_selection()
	if (action == check_balance):
		print("Your current account balance is", account_balance)
		print("Good bye!")
		sys.exit()
	elif (action == withdraw):
		withdrawal_amount = ask_withdrawal_amount()
		if withdrawal_amount == "custom":
			withdrawal_amount = int(input("Input custom amount to withdraw: "))
		account_balance = withdraw_from_account(withdrawal_amount, account_balance, atm_balance)
		display_exit_screen(account_balance, atm_balance)

if __name__ == '__main__':
	main()

