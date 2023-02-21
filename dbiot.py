"""Instalar
pip install pymongo
--pip install certifi
---pip install pymongo[srv]
pip install flask
"""

from pymongo import MongoClient


#MONGO_URI='mongodb+srv://elisa:mongoRojo@cluster0.qwbcqpm.mongodb.net'
#ca = certifi.where()

client = MongoClient()


def db_conexion():
    try:

        client = MongoClient('mongodb+srv://21300193:1234@cluster0.j8vxhfv.mongodb.net')
        #el cliente se conecta a la base de datos dbiot
        #db = client['dbiot']
        db = client['PRACTICA']

    except ConnectionError:
        print("Error al conectar a la bd")
    return db


if __name__ == "__main__":
    base = db_conexion()
    print(base)











