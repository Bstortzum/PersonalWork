#A5-1-Stortzum.py
def main():
    ## Calculate a pay raise.
    firstName = getFirstName()
    lastName = getLastName()
    currentSalary = getCurrentSalary()
    newSalary = calculateNewSalary(currentSalary)
    displayResult(firstName, lastName, newSalary) 

def getFirstName():
    firstName = input("Enter first name: ")
    return firstName

def getLastName():
    lastName = input("Enter last name: ")
    return lastName   

def getCurrentSalary():
    currentSalary = float(input("Enter current salary:"))
    return currentSalary

def calculateNewSalary(currentSalary):
    if currentSalary < 40000:
        currentSalary = (currentSalary * 1.05)
    else:
        currentSalary = (currentSalary * 1.02) + 2000

    return currentSalary

def displayResult(firstName, lastName, newSalary):
    print("New salary for {0} {1}: ${2:,.2f}"
          .format(firstName, lastName, newSalary))

main()
        
    

