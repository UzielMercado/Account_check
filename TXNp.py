import random
import time
from random import randint

class TXNsPendientes:
	x = 0
	y = 0
	z = 0

	def __init__(self, number, balance, seconds):
		self.x = number
		self.y = balance
		self.z = seconds

	def __str__ (self):	
		return str(self.x) + " " + str(self.y) + " " + str(self.z)

TXN_list = []
balance = []
string_TXN_list = []
int_TXN_list = []
TXNsPendiente = []

timer = 1

with open ('TXNs.txt', 'rt') as TXN_file:
    for line in TXN_file:
        TXN_list.append(line)

while True:

	with open ('Balance.txt', 'rt') as Balfile:
	    for lines in Balfile:
	        balance.append(lines)
	print('Current balance:')
	print(balance)
	print('')

	print('New account in...')
	print(timer)
	print('')
	timer -= 1
	if timer <= 0:

		string_TXN_list.append(random.choice(TXN_list))
		for word in string_TXN_list:
				TXN_convertion_list = word.split(" ")

		for string in TXN_convertion_list:
		    convertion_string = string.replace("\n", "")

		    int_TXN_list.append(convertion_string)

		change = float(balance[0]) + float(int_TXN_list[2])

		final_balance = open("Balance.txt", "w")
		final_balance.writelines(str(change))
		final_balance = open("Balance.txt")

		print("New account.\n")

		list_element = TXNsPendientes(int(TXN_convertion_list[0]), float(int_TXN_list[2]), randint(5, 15))
		TXNsPendiente.append(list_element)
		timer = randint(5, 15)

	for account in TXNsPendiente:
		account.z = account.z - 1
		print('Approved in...')
		print(account)
		print('')
		if account.z == 0:
			print("Account approved !\n")
			my_file = open('ApprovedTXNs.txt', 'a')
			my_file.write(str(account.x) + " " + str(account.y) + "\n")
			my_file = open('ApprovedTXNs.txt')

			del TXNsPendiente[0]
			TXN_convertion_list.clear()

	time.sleep(1)


	balance.clear()
	string_TXN_list.clear()
	int_TXN_list.clear()