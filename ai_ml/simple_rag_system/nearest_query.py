import os, json
from shared import connectToDatabase

weaviate_url = os.environ["REST_ENDPOINT"]
weaviate_api_key = os.environ["API_KEY_CONTRIBUTOR"]
client = connectToDatabase(weaviate_url, weaviate_api_key)

questions = client.collections.use("Questions")

response = questions.query.near_text(
    query="kitchen",
    limit=2
)

for obj in response.objects:
    print(json.dumps(obj.properties, indent=2))

client.close()