import weaviate
from weaviate.classes.init import Auth  
from weaviate import WeaviateClient

def connectToDatabase(url: str, api_key:str) -> WeaviateClient: 
    client = weaviate.connect_to_weaviate_cloud(
        cluster_url=url,
        auth_credentials=Auth.api_key(api_key),   )
    return client