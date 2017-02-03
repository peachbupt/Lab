from flask import Flask, jsonify, request, abort, url_for, g
from flask.ext.httpauth import HTTPBasicAuth
from passlib.apps import custom_app_context as pwd_context
from itsdangerous import (TimedJSONWebSignatureSerializer
                          as Serializer, BadSignature, SignatureExpired)

app = Flask(__name__)
app.config['SECRET_KEY'] = 'the quick brown fox jumps over the lazy dog'
IDtoName = {}
UserDB = {}

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

class User():
    index = 0
    def __init__(self, username):
        self.username = username
        self.id = User.index
        IDtoName[self.id] = self.username
        User.index += 1
    def hash_password(self, password):
        self.password = pwd_context.encrypt(password)

    def verify_password(self, password):
        return pwd_context.verify(password, self.password)

    def generate_auth_token(self, expiration = 600):
        s = Serializer(app.config['SECRET_KEY'], expires_in = expiration)
        return s.dumps({'id': self.id})

    @staticmethod
    def verify_auth_token(token):
        s = Serializer(app.config['SECRET_KEY'])
        try:
            data = s.loads(token)
        except SignatureExpired:
            return None
        except BadSignature:
            return None
        user = UserDB[IDtoName[data['id']]]
        return user

@app.route("/demo/api/v1/users", methods = ['POST'])
def new_user():
    username = request.json.get('username')
    password = request.json.get('password')
    print username, password
    if username is None or password is None:
        abort(400)
    if UserDB.has_key(username):
        abort(400)
    else:
        user = User(username)
        user.hash_password(password)
        UserDB[username] = user
        return jsonify({'username':user.username}), 201, \
        {'Location': url_for('get_user', id = user.id, _external = True)}
@app.route('/')
def index():
    return 'hello world'

@auth.verify_password
@app.route('/demo/api/v1/users/<int:id>')
def get_user(id):
    user = UserDB[IDtoName[id]]
    if not user:
        abort(400)
    return jsonify({'username' : user.username})

@auth.verify_password
def verify_password(username_or_token, password):
    user = User.verify_auth_token(username_or_token)
    if not user:
        user = UserDB[username_or_token]
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

if __name__ == "__main__":
    app.run(host = '0.0.0.0', debug = True)