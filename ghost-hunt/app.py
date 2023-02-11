from flask import Flask, render_template
from ghosts import *

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
    backstory = getBackstory(first_name, last_name, age, occupation)
    return render_template("scan.html", name=name, age=age,
                           occupation=occupation, backstory=backstory)

@app.route('/test')
def test_page():
    first_name = getRandomFirstName()
    last_name = getRandomLastName()
    age = getRandomAge()
    occupation = getRandomOccupation()
    backstory = getBackstory(first_name, last_name, age, occupation)

    return render_template("test.html", story=backstory)

if __name__ == '__main__':
    app.run(debug=True)