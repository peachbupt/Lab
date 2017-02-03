# Restful Demo

## What's in the demo
* user registration with user name and password
* user login with user name and password
* get token after login
* access the resource with token

## How to Test

### add a new user
~~~
🐶 # curl -i -X POST -H "Content-Type: application/json" -d '{"username":"peach","password":"python"}' http://127.0.0.1:5000/demo/api/v1/users
HTTP/1.0 201 CREATED
Content-Type: application/json
Location: http://127.0.0.1:5000/demo/api/v1/users/0
Content-Length: 27
Server: Werkzeug/0.11.15 Python/2.7.10
Date: Fri, 03 Feb 2017 12:05:48 GMT

{
  "username": "peach"
}
~~~

### access resource with username and password

~~~
🐶 # curl -i http://127.0.0.1:5000/demo/api/v1/websites -u peach:python
HTTP/1.0 200 OK
Content-Type: application/json
Content-Length: 183
Server: Werkzeug/0.11.15 Python/2.7.10
Date: Fri, 03 Feb 2017 12:05:51 GMT

{
  "websites": [
    {
      "id": 1, 
      "time": 10, 
      "title": "www.google.com"
    }, 
    {
      "id": 2, 
      "time": 20, 
      "title": "www.baidu.com"
    }
  ]
}
~~~

### get token with username/password

~~~
🐶 # curl -i http://127.0.0.1:5000/demo/api/v1/token -u peach:python
HTTP/1.0 200 OK
Content-Type: application/json
Content-Length: 140
Server: Werkzeug/0.11.15 Python/2.7.10
Date: Fri, 03 Feb 2017 12:06:14 GMT

{
  "token": "eyJhbGciOiJIUzI1NiIsImV4cCI6MTQ4NjEyNDE3NCwiaWF0IjoxNDg2MTIzNTc0fQ.eyJpZCI6MH0.lpezH7EbMC0A4zQuVLleeWdbBv83lRZ4a8Gwrl72pvw"
}
~~~

### access resource with token

~~~
🐶 # curl -i http://127.0.0.1:5000/demo/api/v1/websites -u eyJhbGciOiJIUzI1NiIsImV4cCI6MTQ4NjEyNDE3NCwiaWF0IjoxNDg2MTIzNTc0fQ.eyJpZCI6MH0.lpezH7EbMC0A4zQuVLleeWdbBv83lRZ4a8Gwrl72pvw:unused
HTTP/1.0 200 OK
Content-Type: application/json
Content-Length: 183
Server: Werkzeug/0.11.15 Python/2.7.10
Date: Fri, 03 Feb 2017 12:06:57 GMT

{
  "websites": [
    {
      "id": 1, 
      "time": 10, 
      "title": "www.google.com"
    }, 
    {
      "id": 2, 
      "time": 20, 
      "title": "www.baidu.com"
    }
  ]
}
~~~