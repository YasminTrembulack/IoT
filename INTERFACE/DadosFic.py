import firebase_admin
from firebase_admin import credentials, db

# Baixe a chave privada do Firebase Admin SDK e salve-a como 'serviceAccountKey.json'
# Configure as informações do seu projeto Firebase
cred = credentials.Certificate("Francesco.json")
firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://francesco-5cdcb-default-rtdb.firebaseio.com/'
})

# Referência para o nó no Realtime Database
ref = db.reference('carro')

# Dados que você deseja enviar
dados_para_enviar = {
    'X': '0',
    'Y': '0',
}

# Envie os dados para o Realtime Database
ref.update(dados_para_enviar)

# Encerre a aplicação Firebase
firebase_admin.delete_app(firebase_admin.get_app())
