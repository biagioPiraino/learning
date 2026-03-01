# pipelines connects a model with its necessary pre and post processing steps
# allowing a user to directly input a text and get an answer
from transformers import pipeline

# model downloaded from pipeline is cached

# availble text pipelines
#   text-generation
#   text-classification
#   summarization
#   translation
#   zero-shot-classification    -> classify text without prior training on specific labels
#   feature-extraction          -> extract vector representation of text

# available image pipelines
#   image-to-text
#   image-classification
#   object-detection

# audio pipelines
#   automatic-speech-recognition    -> speech to text
#   audio-classification            -> category classification for audio
#   text-to-speech

# multimodal pipelines
#   image-text-to-text -> respond to an image cased on a text prompt


### Example for sentiment analysis
classifier = pipeline("sentiment-analysis")

# text is preprocessed into a format the model can understand
# preprocessed inputs are passed to the model
# predictions are postprocessed so you can use them
results = classifier(["I am afraid ai will replace my ui job!", "I am happy to eat a Pizza"])
print(results)


### Example for text classification without prior training
classifier = pipeline("zero-shot-classification")
results = classifier("Inspire me to create a new outfit for a wedding", candidate_labels=["creative", "technical"])
print(results)
results = classifier("What is the price of a tshirt?", candidate_labels=["creative", "technical"])
print(results)


### Example for text generation with specific model usage
prompt = "This is wonderful weather! Perfect for a little"
generator = pipeline("text-generation", model="HuggingFaceTB/SmolLM2-360M")
results = generator(prompt)
print(results)