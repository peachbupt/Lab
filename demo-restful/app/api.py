from flask import Flask, jsonify, request, abort, url_for, g
from flask.ext.httpauth import HTTPBasicAuth
from app import models, app

websites = [
    {
        'id' : 1,
        'title': "www.google.com",
        'time' : 10
    },
    {
        'id' : 2,
        'title' : "www.baidu.com",
        'time' : 20
    }
]

auth = HTTPBasicAuth()

@app.route("/demo/api/v1/users", methods = ['POST'])
def new_user():
    username = request.json.get('username')
    password = request.json.get('password')
    print username, password
    if username is None or password is None:
        abort(400)
    if models.User.find_byname(username):
        abort(400)
    else:
        user = models.User(username)
        user.hash_password(password)
        user.save()
        return jsonify({'username':user.username}), 201, \
        {'Location': url_for('get_user', username = user.username, _external = True)}

@app.route('/')
def index():
    return 'hello world'

#render a page
@auth.verify_password
@app.route('/demo/api/v1/users/<string:username>')
def get_user(username):
    user = models.User.find_byname(username)
    if not user:
        abort(400)
    return jsonify({'username' : user.username})

@auth.verify_password
def verify_password(username_or_token, password):
    user = models.User.verify_auth_token(username_or_token)
    if not user:
        user = models.User.find_byname(username_or_token)
        if not user or not user.verify_password(password):
            return False
    g.user = user
    return True

@app.route('/demo/api/v1/token')
@auth.login_required
def get_auth_token():
    token = g.user.generate_auth_token()
    return jsonify({'token':token.decode('ascii')})

@app.route('/demo/api/v1/websites', methods=['GET'])
@auth.login_required
def get_website():
    return jsonify({'websites': websites})

@app.route('/demo/api/v1/websites', methods=['POST'])
@auth.login_required
def create_website():
    if not request.json or not 'title' in request.json:
        abort(400)
    website = {
        'id' : websites[-1]['id'] + 1,
        'title' : request.json['title'],
        'time' : request.json['time']
    }
    websites.append(website)
    return jsonify({"website" : website}), 201
