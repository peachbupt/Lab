from flask import Flask, jsonify, request

app = Flask(__name__)

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

@app.route('/')
def index():
    return 'hello world'

@app.route('/demo/api/v1/websites', methods=['GET'])
def get_website():
    return jsonify({'websites': websites})

@app.route('/demo/api/v1/websites', methods=['POST'])
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