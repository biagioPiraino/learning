from weaviate.classes.init import Auth
import requests, json, os
from shared import connectToDatabase

weaviate_url = os.environ["REST_ENDPOINT"]
weaviate_api_key = os.environ["API_KEY_CONTRIBUTOR"]

client = connectToDatabase(weaviate_url, weaviate_api_key)

resp = requests.get(
    "https://raw.githubusercontent.com/weaviate-tutorials/quickstart/main/data/jeopardy_tiny.json"
)
data = json.loads(resp.text)

# loading questions
questions = client.collections.use("Questions")

with questions.batch.fixed_size(batch_size=200) as batch:
    for d in data:
        batch.add_object({
            "answer": d["Answer"],
            "question": d["Question"],
            "category": d["Category"]
        })
        if batch.number_errors > 10:
            print("Batch import full of error")
            break

failed_obj = questions.batch.failed_objects
if failed_obj:
    print(f"Failed for {len(failed_obj)} objects")
else:
    print("Success, closing connection")

client.close()