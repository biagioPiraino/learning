from fastapi import FastAPI 
from routers import prompt

app = FastAPI()
app.include_router(prompt.router)

@app.get("/")
async def root():
    return {"message": "System ready."}