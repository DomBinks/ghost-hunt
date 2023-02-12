import socket
from flask import Flask, render_template, request
from ghosts import *
import time

app = Flask(__name__)
first_name = ""
last_name = ""
name = ""
age = ""
occupation = ""
gtype = ""
backstory = ""
code = 0
location = ''
activity = 0
code = 0

@app.route('/')
def index_page():
    return render_template("index.html")

@app.route('/scan')
def scan_page():
    global first_name
    global last_name
    global name
    global age
    global occupation
    global gtype
    global backstory
    global code
    global location
    global activity
    global code

    first_name = getRandomFirstName()
    last_name = getRandomLastName()
    name = first_name + " " + last_name
    age = getRandomAge()
    occupation = getRandomOccupation()
    gtype = getRandomType()
    backstory = getBackstory(first_name, last_name, age, occupation)
    location = 'a' #getRandomLocation()
    activity = randint(0, 255)
    code = randint(0, 128)

    ip = "192.168.115.59"
    conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    conn.connect((ip,80))
    #r = f"{'Type': {gtype},'Name': {name}, 'Location': {location}, 'Activity': {activity}}\r"
    r = "{'Type': '" + gtype + "','Name': '" + name +"', 'Location': '" + location + "', 'Activity': " + str(activity) + ", 'Code': " + str(code) + "}\r"
    print(r)

    conn.send(r.encode())
    time.sleep(0.2)

    print(str(code))
    return render_template("scan.html", name=name, age=age,
                           occupation=occupation, backstory=backstory,
                           gtype=gtype)

@app.route('/capture', methods=['POST'])
def capture():
    global name
    global age
    global occupation
    global backstory
    global gtype

    print(str(code) + " " + request.form['Code'])
    if request.form['Code'] == str(code):
        return render_template("captured.html")
    else:
     return render_template("scan.html", name=name, age=age,
                           occupation=occupation, backstory=backstory,
                           gtype=gtype)


if __name__ == '__main__':
    app.run(debug=True)