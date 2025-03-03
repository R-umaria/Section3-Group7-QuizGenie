import google.generativeai as genai
from config import API_KEY

genai.configure(api_key=API_KEY)

model = genai.GenerativeModel("gemini-1.5-flash-latest")  # Change model name here
response = model.generate_content("Tell me a fun fact about space.")

print(response.text)
