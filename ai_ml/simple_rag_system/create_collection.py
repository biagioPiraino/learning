import weaviate
from weaviate import WeaviateClient
from weaviate.classes.init import Auth
from weaviate.classes.config import Configure
from weaviate.collections import Collection
import os

weaviate_url = os.environ["REST_ENDPOINT"]
weaviate_api_key = os.environ["API_KEY_CONTRIBUTOR"]

def connectToDatabase() -> WeaviateClient: 
    client = weaviate.connect_to_weaviate_cloud(
        cluster_url=weaviate_url,
        auth_credentials=weaviate_api_key)
    return client

def createCollection(name: str, client: WeaviateClient) -> Collection:
    collection = client.collections.create(
        name=name,
        vector_config=Configure.Vectors.text2vec_weaviate(), 
    )
    return collection

client = connectToDatabase()
collection = createCollection("Questions", client)

print(client.is_ready())

client.close()