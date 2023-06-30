from flask import Flask
from fibonacci import fib

app = Flask(__name__)

@app.route('/')
def index():
    return "<p>Fibonacci function<p>"

@app.route('/<int:cnt>')
def number(cnt):
    fib_gen = fib(cnt)
    res = [next(fib_gen) for i in range(cnt)]
    return res

@app.errorhandler(404)
def not_found_error(error):
    return "Error, try to enter an int number"


if __name__ == "__main__":
    app.run(debug = True)