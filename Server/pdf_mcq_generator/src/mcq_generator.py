import google.generativeai as genai
import json
from config import API_KEY

# Configure the generative AI with the provided API key
genai.configure(api_key=API_KEY)

def generate_mcq_questions(text):
    """
    Sends extracted text to Gemini API to generate multiple-choice questions (MCQs).
    
    Args:
        text (str): The input text from which to generate MCQs.
        
    Returns:
        list: A list of dictionaries, each containing a question, options, and the correct answer.
    """
    # Define the prompt for the generative model
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

    # Initialize the generative model
    model = genai.GenerativeModel("gemini-1.5-flash-latest")
    
    try:
        # Generate content using the model
        response = model.generate_content(prompt)
        print("Gemini API raw response:", response)  # Debug print to check raw response
        json_response = response.text.strip()  # Get the text response
        print("Gemini API JSON response:", json_response)  # Debug print to check JSON response
        
        # Remove the code block markers if present
        if json_response.startswith("```json") and json_response.endswith("```"):
            json_response = json_response[7:-3].strip()
        
        # Convert the JSON response to a dictionary
        questions_json = json.loads(json_response)
        return questions_json.get("questions", [])
    except json.JSONDecodeError:
        # Handle JSON decoding errors
        print("Error: Gemini API response is not in the expected format.")
        return []
    except Exception as e:
        # Handle any other exceptions
        print(f"Error in API call: {e}")
        return []