# This is a sample Python script.

# Press Mayús+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.
from flask import Flask,request, render_template,jsonify
import dbiot as dbase
from sensor import Sensor
from datetime import date
from datetime import datetime


db = dbase.db_conexion()
app = Flask(__name__)

@app.route("/")
def inicio():
    sensores = db['sensores']
    sensoresReceived = sensores.find()
    print(type(sensoresReceived))
    for sensor in sensoresReceived:
        print(sensor.get("sensor"))
        print(sensor["sensor"])
    return render_template("consultasensor.html", sensores = sensoresReceived)

@app.route("/sensor",methods=["POST"])
def sensor():
    fecha = datetime.now()
    if request.is_json:
        data = request.get_json()
        #print(data)
        nombre = data.get("sensor")
        temperatura = data.get("temp")
        humedad = data.get("hum")
        sensores = db['sensores']
        sensor = Sensor(nombre, temperatura, humedad, fecha)
        sensores.insert_one(sensor.toDBCollection())
        response = jsonify({
            'sensor': nombre,
            'valor1': temperatura,
            'valor2': humedad,
            'fecha': fecha
        })

        #registro = sensor_bd.insertar_iot(sensor, temperatura, humedad)
        return response

    else:
        data = "Error al obtener el json"
    return data
    # Use a breakpoint in the code line below to debug your script.
   #return "Hola mundo"  # Press Ctrl+F8 to toggle the breakpoint.


# Press the green button in the gutter to run the script.
if __name__ == '__main__':

    app.run(host="0.0.0.0", port="8090", debug=True)

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
