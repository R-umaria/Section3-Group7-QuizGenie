import google.generativeai as genai
import json
from config import API_KEY

genai.configure(api_key=API_KEY)

def generate_mcq_questions(text):
    """
    Sends extracted text to Gemini API to generate multiple-choice questions.
    """
    prompt = f"""
    Based on the given text, generate exactly 10 multiple-choice questions (MCQs).
    Each MCQ should have:
    - A question
    - Four answer choices
    - The correct answer
    Output as JSON in this format:
    {{
        "questions": [
            {{
                "question": "What is the capital of France?",
                "options": ["Paris", "Berlin", "Madrid", "Rome"],
                "answer": "Paris"
            }},
            ...
        ]
    }}

    Text: {text[:3000]}  # Truncate to avoid exceeding API limits
    """

    model = genai.GenerativeModel("gemini-1.5-flash-latest")
    
    try:
        response = model.generate_content(prompt)
        print("Gemini API raw response:", response)  # Debug print
        json_response = response.text.strip()  # Get the text response
        print("Gemini API JSON response:", json_response)  # Debug print
        
        # Remove the code block markers if present
        if json_response.startswith("```json") and json_response.endswith("```"):
            json_response = json_response[7:-3].strip()
        
        questions_json = json.loads(json_response)  # Convert to dictionary
        return questions_json.get("questions", [])
    except json.JSONDecodeError:
        print("Error: Gemini API response is not in the expected format.")
        return []
    except Exception as e:
        print(f"Error in API call: {e}")
        return []