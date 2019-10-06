import aws_connector as ac

c = ac.AWS_Connector()

c.set_credentials('lee', 'AKIAUQWTAUZKKUJTY54J', '5ij3CeQikrx6vvJS+B3L6BOqVoKhaSPjTp6lrFiF')
c.set_credentials('not-lee', 'AKIAUQWTAUZKFEK2IMUC','VHwX77s1+56Q5pQa0UUymC/xrcz01mILABNmHjLr')

file_to_move = 'titanic-cleaned.csv'

c.select_credential('lee')
df = c.read_csv(file_to_move, 'avant-demo')

c.select_credential('not-lee')
c.write_csv(df, file_to_move,'bucket-two-cool')