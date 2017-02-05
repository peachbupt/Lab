#MicroBlog

## Flask Mega-Tutorial
https://blog.miguelgrinberg.com/post/the-flask-mega-tutorial-part-i-hello-world

## Enviroment

* install virtualenv
	* pip install virtualenv
* create a virtual env
	* virutalenv flask
* install pip libraries

	~~~
$ flask/bin/pip install flask
$ flask/bin/pip install flask-login
$ flask/bin/pip install flask-openid
$ flask/bin/pip install flask-mail
$ flask/bin/pip install flask-sqlalchemy
$ flask/bin/pip install sqlalchemy-migrate
$ flask/bin/pip install flask-whooshalchemy
$ flask/bin/pip install flask-wtf
$ flask/bin/pip install flask-babel
$ flask/bin/pip install guess_language
$ flask/bin/pip install flipflop
$ flask/bin/pip install coverage
~~~ 	

## DB operation

* create DB

	~~~
db_create.py
~~~

* migrate DB

	~~~
	db_migrate.py
~~~

* create two users

	~~~
>>> u = models.User(nickname='john', email='john@email.com')
>>> db.session.add(u)
>>> db.session.commit()
~~~
	
	~~~
>>> u = models.User(nickname='susan', email='susan@email.com')
>>> db.session.add(u)
>>> db.session.commit()
~~~

* create post

	~~~
>>> import datetime
>>> u = models.User.query.get(1)
>>> p = models.Post(body='my first post!', timestamp=datetime.datetime.utcnow(), author=u)
>>> db.session.add(p)
>>> db.session.commit()
~~~