import random

score = 10 

def guessNumber(userNumber, numberToGuess) : 

    global score 
    result = ""

    if score != 0 : 
      
        if userNumber < numberToGuess : 
            score -= 1 
            result = "The number you should find is higher than this."
        
        elif userNumber > numberToGuess : 
            score -= 1 
            result = "The number you should find is lower than this."
      
        elif userNumber < 0 or userNumber > 1000 : 
            result = "The value you entered is incorrect. Please enter en integer between 0 and 1000"

        return result 


numberToGuess = random.randint(0,1000)
x = input("Welcome to Guess the Number! Please enter an integer between 0 and 1000 : ")
print("You entered : " + x)

while int(x) != numberToGuess : 
    print(guessNumber(int(x), numberToGuess))
    x = input("Try again : ")
    print("Your score is : " + str(score) )

    if score == 0 : 
        print("Sorry, you lost!")
        break 

if score != 0 and int(x) == numberToGuess : 
    print("Well done, you found the number!")


    
