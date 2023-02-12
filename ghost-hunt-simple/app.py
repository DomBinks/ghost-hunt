import socket
from flask import Flask, render_template
from ghosts import *
import time

app = Flask(__name__)


@app.route('/')
def index_page():
    return render_template("index.html")

@app.route('/scan')
def scan_page():
    first_name = getRandomFirstName()
    last_name = getRandomLastName()
    name = first_name + " " + last_name
    age = getRandomAge()
    occupation = getRandomOccupation()
    gtype = getRandomType()
    backstory = getBackstory(first_name, last_name, age, occupation)
    location = getRandomLocation()
    activity = randint(0, 255)

    ip = "192.168.115.194"
    conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    conn.connect((ip,80))
    #r = f"{'Type': {gtype},'Name': {name}, 'Location': {location}, 'Activity': {activity}}\r"
    r = "{'Type': '" + gtype + "','Name': '" + name +"', 'Location': '" + location + "', 'Activity': '" + str(activity) + "'}\r"
    print(r)

    conn.send(r.encode())
    time.sleep(0.2)

    return render_template("scan.html", name=name, age=age,
                           occupation=occupation, backstory=backstory,
                           gtype=gtype)

if __name__ == '__main__':
    app.run(debug=True)