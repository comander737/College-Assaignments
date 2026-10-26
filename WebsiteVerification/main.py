#Andre Bieller. CYBR-260-40. This program takes a URl from the user, and checks to see if it is valid. First through a regular expression check, and then cross-checking with a list
#of valid sites. It also has the option to scrape the HTML of a page and save it for review.

import csv #Imports csv functions, internet protocol functions, regular expression functions, and beautifulsoup.
import http.client
import re
from bs4 import BeautifulSoup

def checkURL(): #Function for checking the text of a given URL
    print("Please enter a URL. It should not contain HTTPS or www. For example, youtube.com is correct, but www.youtube.com is not.") #Prompts for a URL
    url = str(input())

    reCheck = re.findall("^[a-zA-Z0-9]+\.[a-z]+", url) #Checks the given URL against a standard layout. If it matches, continue with checks. If not, notify user and return to menu.
    if reCheck:
        print("URL matches a url format. Checking against approved sites...")
    else:
        print("URL does not follow a url format. Check for misleading characters.")
        return

    with open("ApprovedList.csv", newline='') as csvfile: #If regular expression check passed, check the url against approved sites. If site is not found, notify user. If not, return to menu.
        csvreader = csv.reader(csvfile, delimiter=',')
        for row in csvreader:
            if url in row:
                print("URL matches a verified site!")
                return
    print("URL does not match any verified site. Would you like to add it to the list?")
    choice = str(input("y/n:")) #Offers the user the ability to append the approved list with the newly entered URL. If not, return to menu.

    if choice == "y":
        with open("ApprovedList.csv", "a", newline='') as csvfile:
            csvwriter = csv.writer(csvfile, delimiter=' ')
            csvwriter.writerow([url])
            print(url + " added to the approved list.")
            return
    else:
        return

def getHTML(): #HTML scraper. Connects to the given site and saves it's HTML to output.html for review.
    print("Please enter a URL. It should not contain HTTPS or www. For example, youtube.com is correct, but www.youtube.com is not.")
    url = str(input())
    connection = http.client.HTTPSConnection(url)
    connection.request("GET", "/")
    response = connection.getresponse()
    soup = BeautifulSoup(response.read(), features="html.parser")

    with open("output.html", "w") as file:
        file.write(str(soup))

    print("output.html file update. Open in a text editor to safely review.")



while 1: #Main menu. Offers the user relevant choices, executing the needed function depending on input, otherwise exits the program.
    print("Greetings! Would you like to check a URL, or save a webpage's HTML? Please enter the corresponding number:")
    print("1. Check URL")
    print("2. Save a webpage")
    print("3. Exit")
    choice = int(input("Enter your choice: "))
    match choice:
        case 1:
            checkURL()
        case 2:
            getHTML()
        case 3:
            exit(0)