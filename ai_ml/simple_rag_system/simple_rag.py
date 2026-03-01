import os, json
from shared import connectToDatabase
from transformers import pipeline

weaviate_url = os.environ["REST_ENDPOINT"]
weaviate_api_key = os.environ["API_KEY_CONTRIBUTOR"]
client = connectToDatabase(weaviate_url, weaviate_api_key)

questions = client.collections.use("Questions")

response = questions.query.near_text(
    query="living beings",
    limit=3
)

context_parts = []
for obj in response.objects:
    context_parts.append(json.dumps(obj.properties, indent=2))

# Combine the list of texts into a single string for the model
context_for_oracle = " ".join(context_parts)

oracle = pipeline(model="gpt2")
results = oracle(
    "Given these facts: " + context_for_oracle + ". Write a tweet with emojis about them.",
    max_length=50,
    do_sample=True # Set appropriate generation parameters
)

print(results)

client.close()