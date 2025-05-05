# A1-3-Stortzum.py

wattage = float(input("Enter Wattage: "))

hrsUsed = float(input("Enter Number of hours used: "))

priceUSD = float(input("Enter price per kWh in cents: "))

costOfElectricityUSD = wattage * hrsUsed / 1000 * priceUSD

monthlyBillofEle = round(costOfElectricityUSD , 2)

print("Monthly cost =" , "${:,.2f}" .format(monthlyBillofEle))
