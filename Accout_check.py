import time
from datetime import datetime

Current_balance = 0
Balance_change = 0
Base_Origin_balance = 0
Non_Approved = 0
Approved = 0
Non_Approved_Origin = 0

Approved_list = []
with open ('ApprovedTXNs.txt', 'rt') as Approved_file:
	for Lines in Approved_file:
		Approved_list.append(Lines)
Approved_origin = len(Approved_list)
Approved_list.clear()

with open ('Balance.txt', 'rt') as Balance_file:
	for amount in Balance_file:
		Base_Origin_balance = amount
Base_Origin_balance_S = Base_Origin_balance.rstrip()
Origin_balance = round(float(Base_Origin_balance_S) * 100)

while True:

	with open ('ApprovedTXNs.txt', 'rt') as Approved_file:
		for lines in Approved_file:
			Approved_list.append(lines)

	print("----------------------------------------------\n"
	"		Account status\n"
	"		--------------\n")

	with open ('Balance.txt', 'rt') as Balance_file:
		for Amount in Balance_file:
			Base_Current_balance = Amount
	Base_Current_balance_S = Base_Current_balance.rstrip()
	Current_balance = round(float(Base_Current_balance_S) * 100)

	if Current_balance != Origin_balance:
		Balance_change = abs(Current_balance - Origin_balance)
		Non_Approved += Balance_change
		Origin_balance = Current_balance

	if Approved_origin < len(Approved_list):
		New_accounts1 = Approved_list[Approved_origin]
		New_accounts2 = New_accounts1.split('\n')
		New_accounts3 = New_accounts2[0].split(' ')

		Approved += round(float(New_accounts3[1]) * 100)
		Account = New_accounts3[0]
		if Approved < 0:
			signals = "----------------------------------------------\nCash out of:" + str(abs(Approved/100)) + " From: " + str(Account) + "\n----------------------------------------------\n"
			print(signals)
			signals_file = open('Signals.txt', 'a')
			signals_file.write(signals)
		else:
			signals = "----------------------------------------------\nSent: " + str(Approved/100) + " To: " + str(Account) + "\n----------------------------------------------\n"
			print(signals)
			signals_file = open('Signals.txt', 'a')
			signals_file.write(signals)
	
	print("\nCurrent balance:")
	print(Current_balance)

	print("\nLast Balance change:")
	print(Balance_change)

	if Approved_origin < len(Approved_list):
		print("\nNon Approved:")
		Non_Approved -= abs(Approved)
		print(Non_Approved)
	elif Non_Approved == 0:
		Non_Approved = 0
		print("\nNon Approved:")
		print(Non_Approved)
	else:
		print("\nNon Approved:")
		print(Non_Approved)

	if Approved_origin < len(Approved_list):
		print("\nApproved:")
		print(Approved)
		Approved_origin += 1
		Approved_list.clear()
		Approved -= Approved
	elif Approved == 0:
		Approved = 0
		print("\nApproved:")
		print(Approved)
		Approved_list.clear()

	print("\n----------------------------------------------\n")
	time.sleep(.5)