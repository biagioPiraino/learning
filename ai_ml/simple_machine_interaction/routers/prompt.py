from fastapi import APIRouter, status
from transformers import pipeline
from pydantic import BaseModel

class PromptRequest(BaseModel):
    prompt: str

class Response(BaseModel):
    statusCode: int
    message: str

class PromptResponse(Response):
    response: str
    confidence: float

router = APIRouter(
    prefix="/prompts",
    tags=["prompts"],
    responses={500: {"description": "Internal Server Error"}},
)

@router.post("/", status_code=status.HTTP_200_OK)
async def prompt_ai(prompt: PromptRequest) -> PromptResponse:
    # model distilbert-base-uncased, fast model for zero-shot classification
    router = pipeline("zero-shot-classification", model="distilbert-base-uncased")
    
    augmented_prompt = f"""
        You are an AI agent designed to classify user prompts into categories for routing.
        Routing is crucial for Retrieval Augmented Generation because it helps determine which knowledge base to query for relevant information.

        Categories Available:
        - Customers: Prompts related to customer information, support, or inquiries.
        - Products: Prompts related to product details, specifications, or availability.
        - None: Prompts that do not fit into the above categories.
        
        Examples:
        - "How can I reset my password?" -> Customers
        - "What are the features of the new smartphone?" -> Products
        - "Tell me a joke." -> None

        Classify now the following prompt: {prompt.prompt}"""
    results = router(augmented_prompt, candidate_labels=["customers", "products", None])
    return PromptResponse( response= results["labels"][0], confidence= results["scores"][0], statusCode=200, message="Success")