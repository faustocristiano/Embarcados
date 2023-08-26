import pandas as pd
import matplotlib.pyplot as plt

# Ler o arquivo CSV
meuSensor = pd.read_csv('temp.csv')
modeloSensor= pd.read_csv('tempAndrey.csv')

minhaMedia = meuSensor['Temperatura'].mean()
modeloMedia = modeloSensor['Temperatura'].mean()

fator=modeloMedia-minhaMedia
print(fator)

tempAjustada= meuSensor['Temperatura'] + fator
#tempAjustada= (meuSensor['Temperatura'] + modeloSensor['Temperatura'])/2


# Plotar o gráfico de linha da coluna "temperatura"
plt.plot(meuSensor['Temperatura'],color='r',label="Temperatura Medida °C")
plt.plot(modeloSensor['Temperatura'],color='b',label="Temperatura Modelo °C")
plt.plot(tempAjustada,color='m',label="Temperatura Corrigida °C")

plt.xlabel('Amostra')
plt.ylabel('Temperatura')
plt.title('Gráfico da Temperatura')
plt.legend()
plt.show()