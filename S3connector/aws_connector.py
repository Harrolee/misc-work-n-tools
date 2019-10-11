import boto3
from json import loads, dump
import pandas as pd
import os
import sys 
from io import StringIO
from botocore.exceptions import ClientError
import logging


current_client = None
clients = {}

class AWS_Connector():
    '''
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
    '''

    def set_credentials(self, user, aws_id, aws_secret):
        '''First, set_credentials creates a client, allowing it the permissions of the associated user.
            Next, the client is stored in a dict for later access'''
        self.user = user
        self.aws_id = aws_id
        self.aws_secret = aws_secret
        client = boto3.client('s3', aws_access_key_id = aws_id, aws_secret_access_key = aws_secret)
        global clients
        clients[user] = client

    def select_credential(self, user):
        '''sets the instance variable "current_client"'''
        global current_client
        global clients
        self.user = user
        current_client = clients[user]

    def config_credentials(self):
        user = input("enter a user")
        aws_id = input("enter an aws_id")
        aws_secret = input("enter a secret id")
        self.set_credentials(user = user, aws_id = aws_id, aws_secret = aws_secret)
        self.select_credential(user = user)

    def upload_to_aws(self, s3_filename, bucket_name):
        try:
            current_client.upload_file(s3_filename, bucket_name, s3_filename)
            print(f'Successfully uploaded {s3_filename} to {bucket_name}')
        except ClientError as e:
            logging.error(e)
            return False
        os.remove(s3_filename)


    def read_csv(self, s3_filename, bucket_name, view_mode=False):
        '''
        Reads a csv from an s3 bucket. Returns a pandas dataframe.
        If view_mode is passed as True, read_json will both return and print the dataframe.
        '''
        self.s3_filename = s3_filename
        self.bucket_name = bucket_name
        self.view_mode = view_mode

        #If user has not set their credentials, allow them to.
        global current_client
        if current_client == None:
            self.config_credentials()

        #Uses the instance var current_client to get the csv object.
        csv_dict = current_client.get_object(Bucket = bucket_name, Key = s3_filename)
        csv_string = csv_dict['Body'].read().decode('utf-8')
        df = pd.read_csv(StringIO(csv_string))

        if view_mode:
            print(df)
        return df


    def read_json(self, s3_filename, bucket_name, view_mode=False):
        '''
        Reads a JSON from an s3 bucket. Returns a dictionary.
        If view_mode is passed as True, read_json will both return and print the dictionary.
        '''
        self.s3_filename = s3_filename
        self.bucket_name = bucket_name

        #If user has not set their credentials, allow them to.
        global current_client
        if current_client == None:
            self.config_credentials()

        client_obj = current_client.get_object(Bucket = bucket_name, Key = s3_filename)
        client_data = client_obj['Body'].read().decode('utf-8')
        client_dict = loads(client_data)

        if view_mode:
            print(client_dict)
        return client_dict


    def write_csv(self, df, s3_filename, bucket_name):
        '''Converts a dataframe to a CSV and uploads the result to an s3 bucket'''
        self.df = df
        self.s3_filename = s3_filename
        self.bucket_name = bucket_name

        global current_client
        if current_client == None:
            self.config_credentials()

        new_csv = df.to_csv(s3_filename)
        self.upload_to_aws(s3_filename, bucket_name)


    def write_json(self, dictionary, s3_filename, bucket_name):
        '''Converts a dictionary to a JSON and uploads the result to an s3 bucket'''
        self.dictionary = dictionary
        self.s3_filename = s3_filename
        self.bucket_name = bucket_name

        global current_client
        if current_client == None:
            self.config_credentials()

        with open(s3_filename, 'w') as file:  
            dump(dictionary, file)
        self.upload_to_aws(s3_filename, bucket_name)