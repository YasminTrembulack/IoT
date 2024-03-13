import json
import datetime
import requests
import numpy as np
import matplotlib.pyplot as plt

def get_request(url,proxy, auth):
#def get_request(url,proxy):

    #req = requests.get(url, proxies=proxy) #pegar um dado a apartir de um url
    req = requests.get(url, proxies=proxy, auth=auth)

    if req.status_code != 200: #200 bem sucedido 404 site nao encontrado 207 erro relacionado a proxy.
        raise Exception ("Erro na requisição")
    
    return req.content

url = "https://iiot-dta-default-rtdb.firebaseio.com/challenge02.json" 

proxy = {
        "http":"http://disrct:ets%40bosch207@rb-proxy-ca1.bosch.com:8080", # proteção para textos.
        "https": "http://disrct:ets%40bosch207@rb-proxy-ca1.bosch.com:8080"} # implementação segura do http.
   
auth = requests.auth.HTTPProxyAuth("disrct", "ets@bosch207")

def update_data():
    #dados = json.loads(get_request(url, proxy))
    dados = json.loads(get_request(url, proxy, auth))
    dados_len = len(dados)

    indices = np.array([int(x[-2:]) for x in dados.keys()])

    temperature = np.full(dados_len, np.nan, dtype=np.float64) # faz um vetor do tamanho que falar.
    humidity = np.full(dados_len, np.nan, dtype=np.float64)
    

    for i, j in zip(range(dados_len), indices):
        try:
            temperature[i] = dados[f"subsys_{j:02}"]["temperature"]
            humidity[i] = dados[f"subsys_{j:02}"]["humidity"]

        except KeyError:
            pass

    temperature_min = np.min(temperature[~np.isnan(temperature)]) # minimo
    temperature_max = np.max(temperature[~np.isnan(temperature)]) # maximo
    temperature_mean = np.mean(temperature[~np.isnan(temperature)])    # ~np.isnan(luminosity) funciona para verificar se o valor
                                                                    # (nesse caso da luminosidade) é = a nan.

    humidity_min = np.min(humidity[~np.isnan(humidity)]) # minimo
    humidity_max = np.max(humidity[~np.isnan(humidity)]) # maximo                                                                
    humidity_mean = np.mean(humidity[~np.isnan(humidity)])
    



    return temperature_mean, temperature_min, temperature_max, humidity_mean, humidity_min, humidity_max


fig, axs = plt.subplots(2,1, sharex=True, figsize=(16, 8), gridspec_kw={"hspace":0.4}) #gridspec_kw = espaçamento entre os graficos.
# subplots serve para colocar quantos graficos eu quiser em uma imagem enquanto o plot é um grafico por imagem.
fig.supxlabel("Tempo")
ax_temperature, ax_humidity = axs

ax_temperature.grid()
ax_temperature.set_ylabel("Temperatura")

ax_humidity.grid()
ax_humidity.set_ylabel("Humidade")

plt.ion() # vai ter uma figura interativa
fig.show() 
fig.canvas.draw() #desenha a imagem sem nenhum dado, apenas inicializar

while True:
    tempo_atual = datetime.datetime.now()

    temperature_mean, temperature_min, temperature_max, humidity_mean, humidity_min, humidity_max = update_data()

    ax_humidity.plot(tempo_atual, humidity_max, linestyle='', marker="o", markersize = 5, color='r')
    ax_humidity.plot(tempo_atual, humidity_min, linestyle='', marker="o", markersize = 5, color='b')
    ax_humidity.plot(tempo_atual, humidity_mean, linestyle='', marker="o", markersize = 5, color='m')

    ax_temperature.plot(tempo_atual, temperature_max, linestyle='', marker="o", markersize = 5, color='r')
    ax_temperature.plot(tempo_atual, temperature_min, linestyle='', marker="o", markersize = 5, color='b')
    ax_temperature.plot(tempo_atual, temperature_mean, linestyle='', marker="o", markersize = 5, color='m')

    fig.canvas.draw()
    plt.pause(1)
    

# plt.show()

# plt.plot(indices, luminosity, linestyle='', marker="o", markersize=5, color='p')
# plt.grid()
# plt.xlabel("Indices")
# plt.ylabel("Luminosidade")
# plt.show()

# plt.plot(indices, temp_sensor_00, linestyle='', marker="o", markersize=5, color='p')
# plt.grid()
# plt.xlabel("Indices")
# plt.ylabel
# plt.show()

# plt.plot(indices, temp_sensor_01, linestyle='', marker="o", markersize=5, color='p')
# plt.grid()
# plt.xlabel("Indices")
# plt.ylabel("Temperatura sensor 1")
# plt.show()