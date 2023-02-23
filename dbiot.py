"""Instalar
pip install pymongo
--pip install certifi
---pip install pymongo[srv]
pip install flask
"""

from pymongo import MongoClient


#MONGO_URI=''
#ca = certifi.where()

client = MongoClient()


def db_conexion():
    try:

        client = MongoClient('aqui va el nombre del servidor al que te conectas')
        #el cliente se conecta a la base de datos dbiot
        db = client['dbiot']
        #db = client['PRACTICA']

    except ConnectionError:
        print("Error al conectar a la bd")
    return db


if __name__ == "__main__":
    base = db_conexion()
    print(base)











