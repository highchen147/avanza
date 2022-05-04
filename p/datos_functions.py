from ROOT import TProfile
from ROOT import *
import pandas as pd

def data(Doc):				# Crea los data frame y hace la correción de datos necesaria
	col_n = ["Tiempo", "Voltaje", "Corriente"]
	Doc.pop(0)
	Doc = pd.DataFrame(Doc)
	Doc.columns = col_n
	Doc = Doc.astype("float")
	Doc["Tiempo"][abs(Doc["Tiempo"])>2.5] = round(Doc["Tiempo"]/1000,3)
	'''Doc["Voltaje"] = -Doc["Voltaje"]			# Invertir el voltaje si es necesario
	Doc["Corriente"] = -Doc["Corriente"]'''
	return Doc

def style(Profile, Doc, texto1, texto2, color):		# Variables de estilo de Root
	for i in range(0, len(Doc[texto1]) ):
		Profile.Fill(Doc[texto1][i], Doc[texto2][i])	# Ingresa los puntos
	Profile.SetMarkerSize(0.75)							# Tamaño y forma de los puntos
	Profile.SetMarkerStyle(kFullCircle)		
	Profile.SetMarkerColorAlpha(color,0.25)				# Color
	Profile.GetXaxis().SetTitle(texto1)					# Nombre eje X
	Profile.GetYaxis().SetTitle(texto2)					# Nombre eje Y

def grafs(Doc, color, r_min, r_max, bin):
	Time_Volt = TProfile("T vs  V","Tiempo vs Voltaje", 100, -2.5, 2.5)			# Gráfica 1
	style(Time_Volt, Doc, "Tiempo", "Voltaje", color)

	Time_Curr = TProfile("T vs C", "Tiempo vs Corriente", 100, -2.5, 2.5)		# Gráfica 2
	style(Time_Curr, Doc, "Tiempo", "Corriente", color)

	Volt_Curr = TProfile("V vs C", "Voltaje vs Corriente", bin, -3.1, 2.0)		# Gráfica 3
	style(Volt_Curr, Doc, "Voltaje", "Corriente", color)

	rango = [0.65, 0.94]
	Volt_Curr_fit = TProfile("V vs C", "Voltaje vs Corriente", bin, r_min, r_max)	# Gráfica fit
	style(Volt_Curr_fit, Doc, "Voltaje", "Corriente", color)

	line = TF1("line", "[0]+[1]*x", r_min, r_max )					# Ecuación a ajustar con su rango
	line.SetParNames("b","m")
	line.SetLineColor(kAzure-3)

	return Time_Volt, Time_Curr, Volt_Curr, Volt_Curr_fit, line
	
def color_s(nombre):            # Selecciona el color de los puntos dependiendo el archivo leido
    if nombre == "rojo":
        color = kRed
    elif nombre == "azul":
        color = kBlue -3
    elif nombre == "acqua":
        color == kCyan +1
    elif nombre == "uv":
        color = kMagenta
    elif nombre == "naranja":
        color = kOrange +7
    elif nombre == "verde":
        color = kGreen +1
    else:
        color = kPink +9
        
    return color

#####################################################################################################