import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
from datetime import datetime

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    name = db.execute("select username from users where id = ?", session["user_id"])[0]["username"]
    balance = float(db.execute("select cash from users where id = ?", session["user_id"])[0]["cash"])
    print(balance)

    value = 0
    data = db.execute("select * from sharehold where user_id = ?", session["user_id"])
    for item in data:
        result = lookup(item["symbol"])
        item["price"] = result["price"]
        item["total"] = item["price"] * item["share"]
        value += item["total"]
    value += balance
    return render_template("index.html", name = name, data = data, balance=balance, value = value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol=request.form.get("symbol")
        if symbol:
            symbol = symbol.lower()
        else:
            return apology("No symbol")
        try:
            shares=int(request.form.get("shares"))
            if shares <= 0:
                return apology("\"Share\" is not an positive integer.")
        except ValueError:
            return apology("\"Share\" is not a positive integer.")
        if symbol and shares:
            result = lookup(symbol)
            if result != None:
                price = result["price"]
                cash = db.execute("select cash from users where id = ?", session["user_id"])
                left = float(cash[0]["cash"]) - price * float(shares)
                if left>=0:
                    db.execute("insert into transactions (user_id, symbol, action, price, share, time) values(?, ?, ?, ?, ?, ?)", session["user_id"], symbol, "buy", price, shares, datetime.now().strftime('%Y-%m-%d %H:%M:%S'))
                    db.execute("update users set cash = ? where id = ?", left, session["user_id"])
                    exist = db.execute("select share from sharehold where user_id = ? and symbol = ?", session["user_id"], symbol)
                    print(exist)
                    if exist:
                        db.execute("update sharehold set share = ? where user_id = ? and symbol = ?", exist[0]["share"]+shares, session["user_id"], symbol)
                    else:
                        db.execute("insert into sharehold (user_id, symbol, share) values (?, ?, ?)", session["user_id"], symbol, shares)
                    return redirect("/")
                else:
                    return apology("cannot afford the number of shares at the current price")
            else:
                return apology("Symbol not found")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    name = db.execute("select username from users where id = ?", session["user_id"])[0]["username"]
    data = db.execute("select * from transactions where user_id = ?", session["user_id"])
    return render_template("history.html", data=data, name = name)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if symbol:
            result = lookup(symbol)
            print(result)
            if result != None:
                flash("symbol  found!")
                name = result["name"]
                price = result["price"]
                return render_template("quoted.html", name = name, price = price)
            else:
                return apology("")
        else:
            return apology("")
    return render_template("quote.html")


    #return apology("TODO")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    else:
        username=request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if not username or not password:
            return apology("no username or password")
        if password != confirmation:
            return apology("fail to confirm your password")
        try:
            db.execute("insert into users (username, hash) values(?, ?)", username, generate_password_hash(password))
            return redirect("/login")
        except ValueError:
            return apology("username already existed")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    data = db.execute("select * from sharehold where user_id = ?", session["user_id"])
    if request.method == "POST":
        symbols = [item["symbol"] for item in data]
        symbol = request.form.get("symbol")
        if not symbol or symbol not in symbols:
            return apology("Invalid symbol.")

        try:
            shares = int(request.form.get("shares"))
            if shares <= 0:
                return apology("\"Share\" is not a positive integer.")
        except ValueError:
            return apology("\"Share\" is not a positive integer.")

        result = lookup(symbol)
        if result is None:
            return apology("Something went wrong.")

        share_before = db.execute("select share from sharehold where user_id = ? and symbol = ?", session["user_id"], symbol)[0]["share"]
        if share_before >= shares:
            price = result["price"]
            cash = db.execute("select cash from users where id = ?", session["user_id"])[0]["cash"]
            left = float(cash + price * shares)
            db.execute("insert into transactions (user_id, symbol, action, price, share, time) values(?, ?, ?, ?, ?, ?)", session["user_id"], symbol, "sell", price, shares, datetime.now().strftime('%Y-%m-%d %H:%M:%S'))
            db.execute("update users set cash = ? where id = ?", left, session["user_id"])
            share_now = share_before - shares

            if share_now == 0:
                db.execute("delete from sharehold where user_id = ? and symbol = ?", session["user_id"], symbol)
            else:
                db.execute("update sharehold set share = ? where user_id = ? and symbol = ?", share_now, session["user_id"], symbol)

            return redirect("/")
        else:
            return apology("Not enough shares.")
    else:
        return render_template("sell.html", data=data)
