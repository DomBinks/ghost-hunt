from flask import Flask, render_template, request
import requests
import re
import ghosts

app = Flask(__name__)

ghostType = ghosts.getType()
ghostFName = ghosts.getRandomFirstName()
ghostSName = ghosts.getRandomLastName()
suggestedLocation = ghosts.getLocation()
ghostActivity = ghosts.getActivity()
ghostBackstory = ghosts.getBackstory(ghostFName,ghostSName,ghosts.getRandomAge,ghosts.getRandomOccupation)

@app.route('/')
def index_page():
    
    return render_template("ghostTerminal.html", ghostFName=ghostFName, ghostSName=ghostSName, suggestedLocation=suggestedLocation, ghostActivity=ghostActivity, ghostActivity=ghostActivity, )

@app.route("/", methods=["POST"])
def parseString():
    
    command = request.form.get("command")
    command = command.split(" ")
    match command[0]:
        case "connect":
            pat = re.compile("^\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}$")
            if not pat.match(command[1]):
                return
            ip = command[1]
            r = requests.post(command[1], {
                'Type': ghostType, 
                'Name': ghostSName, 
                'Location':suggestedLocation, 
                'Activity': ghostActivity 
                }) 
            if r.text == "Valid Text":
                pass
                

        case "hi lol":
            pass
        case _:
            print("Unknown Command")
            return

    pat = re.compile("^\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}$")
    if pat.match(command):
        return


if __name__ == '__main__':
    app.run(debug=True, port=8024)


    