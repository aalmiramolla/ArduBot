# Lectura de datos desde un Arduino
#
# Basado en el ejemplo AnalogInOutSerial de Arduino (CC-BY-SA 3.0)
# http://arduino.cc/en/Tutorial/AnalogInOutSerial
#
# 2014 Juan Luis Cano <juanlu001@gmail.com>
import io 
import time
serialPort = '/dev/rfcomm2' 
baudios = 19200

try:
	import serial
	arduino = serial.Serial(serialPort, baudrate=baudios, timeout=1.0)
 
	# Nota: provocamos un reseteo manual de la placa para leer desde
    	# el principio, ver http://stackoverflow.com/a/21082531/554319
	arduino.setDTR(False)
	time.sleep(1)
	arduino.flushInput()
	arduino.setDTR(True)
	print ('\n Datos generales de la comuniación serial establecida con BT-328')
	print ('\n Estado del puerto: %s ' % (arduino.isOpen()))
	print ('\n Nombre del dispositivo conectado: %s ' % (arduino.name))
	print ('\n Puerto de comuniación: %s ' % (serialPort))
	print ('\n##############################################################\n')
except (ImportError, serial.SerialException):
    # No hay módulo serial o placa Arduino disponibles
    import io
 
    class FakeArduino(io.RawIOBase):
        """Clase para representar un "falso Arduino"

        """
        def readline(self):
            time.sleep(0.1)
            return b''
 
    arduino = FakeArduino()
 
 
# Con la sentencia with el arduino se cierra automáticamente, ver
# http://docs.python.org/3/reference/datamodel.html#context-managers
with arduino:
	while True:
		try:
            # En Python 3 esta función devuelve un objeto bytes, ver
            # http://docs.python.org/3/library/stdtypes.html#typebytes
			arduino.write(b'44')
			time.sleep(3)
			line = arduino.readline()
            # Con errors='replace' se evitan problemas con bytes erróneos, ver
            # http://docs.python.org/3/library/stdtypes.html#bytes.decode
            # Con end='' se evita un doble salto de línea
			print(line.decode('ascii', errors='replace'), end='')
 
		except KeyboardInterrupt:
			print("Exiting")
			break
