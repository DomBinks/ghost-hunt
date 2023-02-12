from flask import Flask, render_template, request
import requests
import re
import ghosts
import socket

app = Flask(__name__)

ghostType = ghosts.getType()
ghostFName = ghosts.getRandomFirstName()
ghostSName = ghosts.getRandomLastName()
suggestedLocation = ghosts.getLocation()
ghostActivity = ghosts.getActivity()
ghostBackstory = ghosts.getBackstory(ghostFName,ghostSName,ghosts.getRandomAge,ghosts.getRandomOccupation)

@app.route('/')
def index_page():
    
    return render_template("ghostTerminal.html", ghostFName=ghostFName, ghostSName=ghostSName, suggestedLocation=suggestedLocation, ghostActivity=ghostActivity)

@app.route("/", methods=["POST"])
def parseString():
    
    data = request.get_json
    command = data.get("userInput")
    print("1")
    match command[0]:
        case "connect":
            print("2")
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
                

        case "hi":
            print("hello")
            pass
        case _:
            print("Unknown Command")
            return

    pat = re.compile("^\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}$")
    if pat.match(command):
        return


if __name__ == '__main__':
    #app.run(debug=True, port=8024)
    ip = "192.168.115.59"
    import time
    conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    conn.connect((ip,80))
    r = "{'Type': 'test','Name': 'Dom Bimkf', 'Location':'a', 'Activity': 100, 'Code':20}\r"
    while(1):
        conn.send(r.encode())
        
        time.sleep(0.2)
        


    