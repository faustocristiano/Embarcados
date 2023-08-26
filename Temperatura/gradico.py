import pandas as pd
import matplotlib.pyplot as plt

# Ler o arquivo CSV
data = pd.read_csv('temp.csv')
media_temperatura = data['Temperatura'].mean()
variaveis=data['Temperatura'].describe()
print(variaveis)

print(f'Média da temperatura: {media_temperatura:.2f}')

# Plotar o gráfico de linha da coluna "temperatura"
plt.plot(data['Temperatura'])
plt.xlabel('Amostra')
plt.ylabel('Temperatura')
plt.title('Gráfico da Temperatura')
plt.show()