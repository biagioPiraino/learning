import weaviate
import os

weaviate_url = os.environ["REST_ENDPOINT"]
weaviate_api_key = os.environ["API_KEY_CONTRIBUTOR"]

client = weaviate.connect_to_weaviate_cloud(
    cluster_url=weaviate_url,
    auth_credentials=weaviate_api_key
)

print(client.is_ready())

client.close()