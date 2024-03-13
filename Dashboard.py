import json
import datetime
#from datetime import datetime
import requests
import numpy as np
import matplotlib.pyplot as plt

def get_request(url,proxy, auth):

    req = requests.get(url, proxies=proxy, auth=auth)

    if req.status_code != 200: #200 bem sucedido 404 site nao encontrado 207 erro relacionado a proxy.
        raise Exception ("Erro na requisição")
    
    return req.content

url = "https://iiot-dta-default-rtdb.firebaseio.com/avaliacao.json" #depois do /barra coloca a "pasta" que estão os dados.

proxy = {
        "http":"http://disrct:ets%40bosch207@rb-proxy-ca1.bosch.com:8080", # proteção para textos.
        "https": "http://disrct:ets%40bosch207@rb-proxy-ca1.bosch.com:8080"} # implementação segura do http.
   
auth = requests.auth.HTTPProxyAuth("disrct", "ets@bosch207")

def update_data():
    dados = json.loads(get_request(url, proxy, auth))

    print(dados)
    try:
        media = dados["subsys_04"]["mean_temperature"]
        desvio_padrao = dados["subsys_04"]["standard_deviation"]

    
    except KeyError:
        media = 0
        desvio_padrao = 0

    return desvio_padrao, media

      

fig, axs = plt.subplots(2,1, sharex=True, figsize=(16, 8), gridspec_kw={"hspace":0.4}) #gridspec_kw = espaçamento entre os graficos.
# subplots serve para colocar quantos graficos eu quiser em uma imagem enquanto o plot é um grafico por imagem.

fig.supxlabel("Avaliação")
ax_desvio_padrao, ax_media = axs

ax_desvio_padrao.grid()
ax_desvio_padrao.set_ylabel("Desvio padrão temperatura")


ax_media.grid()
ax_media.set_ylabel("Média Temperatura")


plt.ion() # vai ter uma figura interativa
fig.show() 
fig.canvas.draw() #desenha a imagem sem nenhum dado, apenas inicializar

while True:

    tempo_atual = datetime.datetime.now()

    desvio_padrao, media = update_data()

    ax_desvio_padrao.plot(tempo_atual, desvio_padrao, linestyle='', marker="o", markersize = 5, color='b')
    ax_media.plot(tempo_atual, media, linestyle='', marker="o", markersize = 5, color='b')

    fig.canvas.draw()
    plt.pause(1)