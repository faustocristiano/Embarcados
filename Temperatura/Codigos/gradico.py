import pandas as pd
import matplotlib.pyplot as plt

# Ler o arquivo CSV
meuSensor = pd.read_csv('temp.csv')
modeloSensor = pd.read_csv('tempAndrey.csv')

minhaMedia = meuSensor['Temperatura'].mean()
modeloMedia = modeloSensor['Temperatura'].mean()

fator = modeloMedia - minhaMedia
mediaAjustada = minhaMedia + fator

tempAjustada = meuSensor['Temperatura'] + fator
print(fator)

# Plotar o scatter plot das temperaturas e as linhas de médias
plt.figure(figsize=(10, 6))  # Cria uma nova figura com tamanho personalizado
plt.scatter(meuSensor.index, meuSensor['Temperatura'], color='r', label="Temperatura Medida °C")
plt.scatter(modeloSensor.index, modeloSensor['Temperatura'], color='b', label="Temperatura Modelo °C")
plt.axhline(y=minhaMedia, color='g', linestyle='--', label="Minha Média °C")
plt.axhline(y=modeloMedia, color='orange', linestyle='--', label="Modelo Média °C")
plt.xlabel('Amostra')
plt.ylabel('Temperatura')
plt.title('Scatter Plot da Temperatura - Comparação com Médias')
plt.legend()
plt.show()

# Plotar o scatter plot da Temperatura Corrigida em uma nova figura
plt.figure(figsize=(10, 6))  # Cria uma nova figura com tamanho personalizado
plt.plot(tempAjustada, color='y', label="Temperatura Corrigida °C")
plt.axhline(y=mediaAjustada, color='purple', linestyle='--', label="Média Ajustada °C")
plt.xlabel('Amostra')
plt.ylabel('Temperatura Corrigida')
plt.title('Temperatura Corrigida')
plt.legend()
plt.show()
