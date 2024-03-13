import json
import datetime
#from datetime import datetime
import requests
import numpy as np
import matplotlib.pyplot as plt

"bem2ct"
"gaussKronrod754"

def get_request(url,proxy, auth):
#def get_request(url,proxy):

    #req = requests.get(url, proxies=proxy) #pegar um dado a apartir de um url
    req = requests.get(url, proxies=proxy, auth=auth)

    if req.status_code != 200: #200 bem sucedido 404 site nao encontrado 207 erro relacionado a proxy.
        raise Exception ("Erro na requisição")
    
    return req.content

url = "https://iiot-dta-default-rtdb.firebaseio.com/challenge02.json" #depois do /barra coloca a "pasta" que estão os dados.

proxy = {
        "http":"http://disrct:ets%40bosch207@rb-proxy-ca1.bosch.com:8080", # proteção para textos.
        "https": "http://disrct:ets%40bosch207@rb-proxy-ca1.bosch.com:8080"} # implementação segura do http.
   
auth = requests.auth.HTTPProxyAuth("disrct", "ets@bosch207")

def update_data():
    #dados = json.loads(get_request(url, proxy))
    dados = json.loads(get_request(url, proxy, auth))
    dados_len = len(dados) #pega o tamano do data/a quantidade de dados no vetor.

    indices = np.array([int(x[-2:]) for x in dados.keys()]) #pega os dois ultimos digitos dos subsys.
    #para todo x que ta em dados, que é um dicionario, ou seja ele vai pegar os 2 ultimos caract. de cada subsys.

    temperature = np.full(dados_len, np.nan, dtype=np.float64) # faz um vetor do tamanho que falar.
    humidity = np.full(dados_len, np.nan, dtype=np.float64)
    

    for i, j in zip(range(dados_len), indices):
        #precisa do i e j pq nem sempre os dados subsys estão em ordem(1, 2, 3...).
        try:
            temperature[i] = dados[f"subsys_{j:02}"]["temperature"]
            humidity[i] = dados[f"subsys_{j:02}"]["humidity"]

        except KeyError:
            pass

    temperature_min = np.min(temperature[~np.isnan(temperature)]) # minimo
    temperature_max = np.max(temperature[~np.isnan(temperature)]) # maximo
    temperature_mean = np.mean(temperature[~np.isnan(temperature)])    # ~np.isnan(luminosity) funciona para verificar se o valor
                                                                    # (nesse caso da luminosidade) é igual a nan.

    humidity_min = np.min(humidity[~np.isnan(humidity)]) # minimo
    humidity_max = np.max(humidity[~np.isnan(humidity)]) # maximo                                                                
    humidity_mean = np.mean(humidity[~np.isnan(humidity)])
    



    return temperature_mean, temperature_min, temperature_max, humidity_mean, humidity_min, humidity_max

def update_plot():
    tempo_atual = datetime.datetime.now()

    temperature_mean, temperature_min, temperature_max, humidity_mean, humidity_min, humidity_max = update_data()

    ax_humidity.plot(tempo_atual, humidity_max, linestyle='', marker="o", markersize = 5, color='r', label= "max")
    ax_humidity.plot(tempo_atual, humidity_mean, linestyle='', marker="o", markersize = 5, color='b', label= "mean")
    ax_humidity.plot(tempo_atual, humidity_min, linestyle='', marker="o", markersize = 5, color='c', label= "min")

    
    ax_temperature.plot(tempo_atual, temperature_max, linestyle='', marker="o", markersize = 5, color='r', label= "max")
    ax_temperature.plot(tempo_atual, temperature_mean, linestyle='', marker="o", markersize = 5, color='b', label= "mean")
    ax_temperature.plot(tempo_atual, temperature_min, linestyle='', marker="o", markersize = 5, color='c', label= "min")
    

fig, axs = plt.subplots(2,1, sharex=True, figsize=(16, 8), gridspec_kw={"hspace":0.4}) #gridspec_kw = espaçamento entre os graficos.
# subplots serve para colocar quantos graficos eu quiser em uma imagem enquanto o plot é um grafico por imagem.

fig.supxlabel("DHT Data")
ax_temperature, ax_humidity = axs

update_plot()

ax_temperature.grid()
ax_temperature.set_ylabel("Temperatura")
ax_humidity.legend(loc='upper right')

ax_humidity.grid()
ax_humidity.set_ylabel("Umidade")
ax_temperature.legend(loc='upper right')

plt.ion() # vai ter uma figura interativa
fig.show() 
fig.canvas.draw() #desenha a imagem sem nenhum dado, apenas inicializar

while True:

    update_plot()

    fig.canvas.draw()
    plt.pause(1)