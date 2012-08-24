
# Importa a biblioteca serial
import serial

from XPLMDefs import *
from XPLMDataAccess import *
from XPLMProcessing import *

class PythonInterface:
	"""
	XPluginStart
	Inicializa o que for necessario para o plugin 
	"""
	def XPluginStart(self):
		"""
		O sistema de plugins necessita destas informacoes para uma descricao correta"""
		self.Name = "XPFreq"
		self.Sig =  "JOZ.Python.XPFreq"
		self.Desc = "Envia informacoes das frequencia dos radios via Serial"
		
		# Define porta e velocidade da comunicacao serial
		self.ser = serial.Serial('COM3', 115200, timeout = 12)
		
		# Inicializa os Datarefs necessarios
		self.DataRef = XPLMFindDataRef("sim/cockpit/radios/com1_freq_hz")
		self.DataRef2 = XPLMFindDataRef("sim/cockpit/radios/com1_stdby_freq_hz")
		self.DataRef3 = XPLMFindDataRef("sim/cockpit/radios/com2_freq_hz")
		self.DataRef4 = XPLMFindDataRef("sim/cockpit/radios/com2_stdby_freq_hz")
		self.DataRef5 = XPLMFindDataRef("sim/cockpit/radios/nav1_freq_hz")
		self.DataRef6 = XPLMFindDataRef("sim/cockpit/radios/nav1_stdby_freq_hz")
		self.DataRef7 = XPLMFindDataRef("sim/cockpit/radios/nav2_freq_hz")
		self.DataRef8 = XPLMFindDataRef("sim/cockpit/radios/nav2_stdby_freq_hz")
	
		self.atual_seq = ''
		self.serial_seq = ''
		
		# Nosso Callback 'funcao principal' baseado em tempo 
		self.FlightLoopCB = self.FlightLoopCallback
		XPLMRegisterFlightLoopCallback(self, self.FlightLoopCB, 1.0, 0)
		
		return self.Name, self.Sig, self.Desc

	"""
	XPluginStop
	Necessario. Utilizado para finalizar as rotinas iniciadas
	"""
	def XPluginStop(self):
		XPLMUnregisterFlightLoopCallback(self, self.FlightLoopCB, 0)
		self.ser.close()
		pass

	"""
	XPluginEnable.
	Necessario, mas nao precisa nenhuma inicializacao especifica. Indicando '1' para habilitar o plugin
	"""
	def XPluginEnable(self):
		return 1

	"""
	XPluginDisable
	Necessario. Basta indicar 'pass'
	"""
	def XPluginDisable(self):
		pass


	"""
	XPluginReceiveMessage
	Necessario. Alem dos parametros, basta indicar 'pass'
	"""
	def XPluginReceiveMessage(self, inFromWho, inMessage, inParam):
		pass

		
	#Funcao pincipal:
	def FlightLoopCallback(self, elapsedMe, elapsedSim, counter, refcon):
		# Armazena todas as frequencias numa string iniciada com 'F'
		self.atual_seq = ('F'+(str(XPLMGetDatai(self.DataRef)))+\
				(str(XPLMGetDatai(self.DataRef2)))+\
				(str(XPLMGetDatai(self.DataRef3)))+\
				(str(XPLMGetDatai(self.DataRef4)))+\
				(str(XPLMGetDatai(self.DataRef5)))+\
				(str(XPLMGetDatai(self.DataRef6)))+\
				(str(XPLMGetDatai(self.DataRef7)))+\
				(str(XPLMGetDatai(self.DataRef8))))
		
		# Comparamos a string, caso seja diferente da enviada via serial, enviamos novamente
		if (self.serial_seq != self.atual_seq):
			self.serial_seq = self.atual_seq
			self.ser.write(self.serial_seq)
		
		# A funcao devera ser chamada novamente em 0.5 sec
		return 0.5
