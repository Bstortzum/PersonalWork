# A1-4-Stortzum.py

bill = float(input("Enter amount of bill: "))

tipPerc = float(input("Enter percentage tip: "))

tipCash = (bill *(tipPerc/100))

tipMoney = round(tipCash, 2)

print("Tip =", "${:,.2f}" .format(tipMoney))
