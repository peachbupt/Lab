import os
import unittest

from config import basedir
from app import app, db
from app.models import User

class TestCase(unittest.TestCase):
    
    def setUp(self):
        app.config['TESTING'] = True
        app.config['WTF_CSRF_ENABLED'] = False
        app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///' + os.path.join(basedir, 'test.db')
        self.app = app.test_client()
        db.create_all()

    def tearDown(self):
        db.session.remove()
        db.drop_all()

    def test_make_unique_nickname(self):
        u = User(nickname = 'peach', email = 'peach@gmail.com')
        db.session.add(u)
        db.session.commit()
        nickname = User.make_unique_nickname('peach')
        assert nickname != 'peach'
        u = User(nickname = nickname, email = "peach@qq.com")
        db.session.add(u)
        db.session.commit()
        nickname2 = User.make_unique_nickname('peach')
        assert nickname2 != 'peach'
        assert nickname2 != nickname

if __name__ == '__main__':
    unittest.main()
