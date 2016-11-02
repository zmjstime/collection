# encoding: utf-8
import sqlite3
import sys

reload(sys)
sys.setdefaultencoding('utf8') 

connect = sqlite3.connect('data.db')

# creat table
# connect.execute('''create table company (id int primary key not null, 
# 	name text not null, age int not null, address char(50),salary real);''')

# insert data
# connect.execute('''insert into company values(101, 'apple', 18, 'haven', 10)''')
# connect.commit()

select = connect.execute('select * from urinalysisInfo')

for x in select:
	for y in x:
		print y
connect.close()