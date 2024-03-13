"bem2ct"
"gaussKronrod754"


import json
import requests

url = "https://random.dog/woof.json"

proxy = {
    "http":"http://disrct:ets%40bosch207@rb-proxy-ca1.bosch.com:8080", # proteção para textos
    "https": "http://disrct:ets%40bosch207@rb-proxy-ca1.bosch.com:8080" # implementação segura do http
}

auth = requests.auth.HTTPProxyAuth("disrct", "ets@bosch207")

req = requests.get(url, proxies=proxy, auth=auth) #pegar um dado a apartir de um url

if req.status_code != 200: #200 bem sucedido 404 site nao encontrado 207 erro relacionado a proxy
    raise Exception ("Erro na requisição")

dados = json.loads(req.content)

url_imagem = dados["url"] # pegou a url da imagem

with open("cachorro0.jpg", "wb") as image:
    req_image = requests.get(url_imagem, proxies=proxy, auth=auth) 
    #solicitar imagem para o url da imagem que foi pego do site
    image.write(req_image.content)
