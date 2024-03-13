import json
import requests
import numpy as np
import matplotlib.pyplot as plt

def get_request(url,proxy, auth):
#def get_request(url,proxy):

    #req = requests.get(url, proxies=proxy) #pegar um dado a apartir de um url
    req = requests.get(url, proxies=proxy, auth=auth)

    if req.status_code != 200: #200 bem sucedido 404 site nao encontrado 207 erro relacionado a proxy
        raise Exception ("Erro na requisição")
    
    return req.content

url = "https://iiot-dta-default-rtdb.firebaseio.com/iiot-dta.json"

proxy = {
        "http":"http://disrct:ets%40bosch207@rb-proxy-ca1.bosch.com:8080", # proteção para textos
        "https": "http://disrct:ets%40bosch207@rb-proxy-ca1.bosch.com:8080"} # implementação segura do http
   
auth = requests.auth.HTTPProxyAuth("disrct", "ets@bosch207")

#dados = json.loads(get_request(url, proxy))
dados = json.loads(get_request(url, proxy, auth))
dados_len = len(dados)
indices = np.array([int(x[-2:]) for x in dados.keys()])

luminosity = np.full(dados_len, np.nan, dtype=np.float64) # faz um vetor do tamanho que falar
temp_sensor_00 = np.full(dados_len, np.nan, dtype=np.float64)
temp_sensor_01 = np.full(dados_len, np.nan, dtype=np.float64)

for i, j in zip(range(dados_len), indices):
    try:
        luminosity[i] = dados[f"subsys_{j:02}"]["luminosity"]
        temp_sensor_00[i] = dados[f"subsys_{j:02}"]["temperature"]["temp_sensor_00"]
        temp_sensor_01[i] = dados[f"subsys_{j:02}"]["temperature"]["temp_sensor_01"]
    except KeyError:
        pass


fig, axs = plt.subplots(3,1, figsize=(16, 8), gridspec_kw={"hspace":0.4}) #gridspec_kw = espaçamento entre os graficos
fig.supxlabel("Indices")
ax_luminosity, ax_temp_sensor_00, ax_temp_sensor_01 = axs

ax_luminosity.grid()
ax_luminosity.set_ylabel("Luminosidade")

ax_temp_sensor_00.grid()
ax_temp_sensor_00.set_ylabel("Temperatura sensor 0")

ax_temp_sensor_01.grid()
ax_temp_sensor_01.set_ylabel("Temperatura sensor 1")

ax_luminosity.plot(indices, luminosity, linestyle='-', marker="o", markersize = 5, color='m')
ax_temp_sensor_00.plot(indices, temp_sensor_00, linestyle='-', marker="o", markersize = 5, color='c')
ax_temp_sensor_01.plot(indices, temp_sensor_01, linestyle='-', marker="o", markersize = 5, color='b')

plt.show()

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
