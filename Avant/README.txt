I assume the user has the credentials for an IAM account with 
access to the bucket(s) they want to read from or add to.


To use AWS_Connector, import the module.
        ex: import aws_connector as ac
First, make an instance of class Connector()
        ex: c = ac.AWS_Connector()
Second, use set_credentials to set the credentials for a bucket you intend to access.
    This will add the credentials you provided to a dictionary.
    You will have to call this method for as many accounts as you need to use.
        ex: c.set_credentials(userName, aws_id, aws_secret)
Third, use select_credential to specify which user you would like to use for a method call.
        ex: c.select_credential(userName)
Finally, perform your bucket operations with the r/w csv and json methods.


Read to a bucket:
    c.read_csv
    c.read_json
Write to a bucket:
    c.write_csv
    c.write_json

Handling multiple accounts:
    If I have 3 accounts, then I should run "set_credentials()" 3 times
        ex:
        c.set_credentials(userName1, aws_id1, aws_secret1)
        c.set_credentials(userName1, aws_id1, aws_secret1)
        c.set_credentials(userName1, aws_id1, aws_secret1)
    For operations requiring the first account, I should call "select_credential(userName1)"
        ex:
        c.select_credential(userName1)
        c.read_csv()
        c.write_json()
    I should call "select_credential(_____)" every time I want to switch accounts
        ex:
        c.select_credential(userName2)
        df = c.read_csv("puppy_photos.csv", "bucket-two")
        c.select_credential(userName3)
        c.write_csv(df, "puppy_photos.csv", "bucket-three")

Check out test_connector.py for an example.


Feel free to contact leeharrold.connect@gmail.com for questions and suggestions.