from datos_functions import *
from ROOT import TCanvas
from ROOT import *
import sys

#####################################################################################################

name = sys.argv[1]				# Nombre del archivo a analizar
r_min = float(sys.argv[2]) 		# rango mínimo del fit
r_max = float(sys.argv[3]) 		# rango máximo del fit
bin = int(sys.argv[4])			# Número de bines

docs = ["toma-"+name+".csv","offset-"+name+".csv"]
escale_toma = [500, 100]
escale_offs = [500, 100]
color = color_s(name)					# Color de los puntos
Doc1 = []
Doc2 = []
i = 0

for doc in docs:
	f1 = open(doc, "r")
	lines = f1.readlines()
	for line in lines:
		line = line.replace("\n","")
		line = line.replace(" ","")
		line = line.split(",")
		if i == 0:
			Doc1.append(line)
		elif i == 1:
			Doc2.append(line)
	i += 1

Doc1 = data(Doc1)				# Dataframe de todos los datos toma
Doc2 = data(Doc2)				# Dataframe de todos los datos offset

Doc3 = Doc1.copy()			# Copia manipulable de Doc1
Doc3["Corriente"] = Doc3["Corriente"] - Doc2["Corriente"]

#####################################################################################################

#Time_Volt, Time_Curr, Volt_Curr, Volt_Curr_fit, line = grafs(Doc1, color, r_min, r_max, bin)
Time_Volt, Time_Curr, Volt_Curr, Volt_Curr_fit, line = grafs(Doc3, color, r_min, r_max, bin)

gStyle.GetName()
gStyle.SetOptStat(11)
gStyle.SetOptFit(1)

dpi = 200
dpi = int(dpi/72)

a = TCanvas("ac", "Datos", 1600*dpi, 600*dpi)					# Crear el canvas
a.Divide(2,2)
a.cd(1)						# Asignar la posición 1
Time_Volt.Draw()
a.cd(2)
Time_Curr.Draw()
a.cd(3)
Volt_Curr.Draw()
a.cd(4)
Volt_Curr_fit.Fit("line")
a.Draw()

a.SaveAs("out"+name + ".jpg")		# Guardar la imagen
input()						# Presionar enter para dejar de ver la gráfica.

#####################################################################################################
