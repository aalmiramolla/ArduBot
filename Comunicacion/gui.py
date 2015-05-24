#!/usr/bin/python
# -*- coding: utf-8 -*-
#librería que permite la interacción con Octave.
#Librería para poder generar la Interfaz Gráfica.
from tkinter import *
from tkinter.messagebox import *
from tkinter import ttk
import tkinter
from tkinter.filedialog import *
import io
import time
import serial

class App(Frame):
    def __init__(self,root):
        Frame.__init__(self,root,background="white")
        self.root = root
        self.createWidgets()
        ttk.Frame(self.root).pack()
        self.canvasOriginal = Canvas()
        self.canvasTurn = Canvas()
        self.left = Label()
        self.right = Label()
        self.serialPort = '/dev/rfcomm2'
        self.baudios = 19200
        
    #Iniciación de la interfaz gráfica utilizando dos Frames: OptionsFrame y root
    def createWidgets(self):
        self.createMenubar()
        self.createOptionFrames()
    # Crea el menu superior en el que podemos abrir la imagen y lo guardar.
    def createMenubar(self):
        menubar = Menu(self.root)
        filemenu = Menu(menubar, tearoff=0)
        filemenu.add_command(label="Guardar", command=self.save_image)
        filemenu.add_separator()
        filemenu.add_command(label="Salir", command=self.root.quit)
        menubar.add_cascade(label="Archivo", menu=filemenu)
        editmenu = Menu(menubar, tearoff=0)
        helpmenu = Menu(menubar, tearoff=0)
        helpmenu.add_command(label="About...", command=self.show_info)
        menubar.add_cascade(label="Ayuda", menu=helpmenu)
   
        root.config(menu = menubar)
    #Crea el frame Option para todos los parámetros que se pueden emplear en la imagen.
        #Crea el frame Option para todos los parámetros que se pueden emplear en la imagen.
    def createOptionFrames(self):
        self.optionsFrame = LabelFrame(self.root, text="Options")
        self.optionsFrame.pack(side = LEFT,fill="both", expand="yes")
        #Combobox de Simetría.
        self.countryvarSimetria = StringVar()
        labelSimetria = Label(self.optionsFrame, text = "Misiones Disponibles:")
        labelSimetria.pack(fill="both")
        self.countrySimetria = ttk.Combobox(self.optionsFrame,text=self.countryvarSimetria)
        self.countrySimetria['values'] = ('--------', 'Mision1_1','Mision1_1_1', 'Mision1_1_2', 'Mision1_2')
        self.countrySimetria.pack(fill="both")
        #Combobox de los grados.
        # labelGrados = Label(self.optionsFrame, text = "Grados: ")
        # labelGrados.pack()
        # self.countryvarGrados = StringVar()
        # self.countryGrados = ttk.Combobox(self.optionsFrame, text=self.countryvarGrados)
        # self.countryGrados['values'] = ('--------', '90', '180', '270')
        # self.countryGrados.pack()
        # # Combobox del color.
        # labelColor = Label(self.optionsFrame, text = "¿A color?")
        # labelColor.pack()
        # self.countryvarColor = StringVar()
        # self.countryColor = ttk.Combobox(self.optionsFrame, text = self.countryvarColor)
        # self.countryColor['values'] = ('A escala de grises', 'A color')
        # self.countryColor.pack()
        #boton Aplicar
        self.BotonAplicar = Button(self.optionsFrame,text="Conectar", command = self.connect)
        self.BotonAplicar.pack(side=LEFT,anchor = "ne")
        #Boton Guardar.
        self.BotonGuardar = Button(self.optionsFrame, text ="Desconectar")
        self.BotonGuardar.pack(side=LEFT,anchor = "ne")

        self.BotonArriba = Button(self.optionsFrame, text = "Arriba", command = self.arduinoArriba)
        self.BotonArriba.pack(side= RIGHT,anchor = "ne")

        self.BotonAbajo = Button(self.optionsFrame, text = "Abajo")
        self.BotonAbajo.pack(side= RIGHT,anchor = "ne")

        self.BotonDerecha = Button(self.optionsFrame, text = "Derecha")
        self.BotonDerecha.pack(side= RIGHT,anchor = "ne")

        self.BotonIzquierda = Button(self.optionsFrame, text = "Izquierda")
        self.BotonIzquierda.pack(side= RIGHT,anchor = "ne")

        self.BotonSuma = Button(self.optionsFrame, text = "Suma")
        self.BotonSuma.pack(side= RIGHT,anchor = "ne")

        self.BotonResta = Button(self.optionsFrame, text = "Resta")
        self.BotonResta.pack(side= RIGHT,anchor = "ne")
        
        self.BotonEspacio = Button(self.optionsFrame, text = "Espacio")
        self.BotonEspacio.pack(side= RIGHT,anchor = "ne")

        self.BotonU = Button(self.optionsFrame, text = "U")
        self.BotonU.pack(side= RIGHT,anchor = "ne")

        self.BotonD = Button(self.optionsFrame, text = "D")
        self.BotonD.pack(side= RIGHT,anchor = "ne")
    #Modulo encargado de mostrar la información sobre el desarrollo cuando se
    #accede desde el menú superior.
    def show_info(self):
        showinfo("Info", "Programa desarrollado por\nfmgb3@alu.ua.es\npara la asignatura\nTecnología y Arquitectura Robótica. \nCon la colaboración del compañero: aam107@alu.ua.es")
        
    #Aviso cuando guarda la imagen.
    def save_image(self):
        showinfo("Imagen guardada", "Imagen guardada en la ruta: " + "/tmp/newImageTAR.png")

    def connect(self):
        try:
            self.arduino = serial.Serial(self.serialPort, baudrate=self.baudios,timeout=1.0)
            self.arduino.setDTR(False)
            time.sleep(1)
            self.arduino.flushInput()
            self.arduino.setDTR(True)
            # with self.arduino:
            #     while True:
            #         try:
            #             self.arduino.write(b'10')
            #             time.sleep(3)
            #             line = self.arduino.readline()
            #             print(line.decode('ascii',errors='replace'), end='')

            #         except KeyboardInterrupt:
            #             print("Exiting")
            #             break
        except(ImportError, serial.SerialExpception):
            class FakeArduino(io.RawIOBase):

                def readline(self):
                    time.sleep(0.1)
                    return b''
            self.arduino = FakeArduino()

    def arduinoArriba(self):
        self.arduino.write(b'10')
    # def disconnect(self):
    #     with self.arduino:
    #         while True:
    #             try:
                    
    #                 time.sleep(3)
    #                 line = self.arduino.readline()
    #             except KeyboardInterrupt:
    #                 print("Exiting")
    #                 break
        
# create the application
root = tkinter.Tk()
root.geometry("250x150+300+300")
myapp = App(root)

#
# Llamamos a los métodos para crear la interfaz
#
myapp.root.title("Control del robot de TAR")
myapp.root.resizable(width=TRUE, height = TRUE)

# Empezamos el programa
root.mainloop()
