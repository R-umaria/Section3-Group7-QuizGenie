import pandas as pd

def save_questions_to_csv(questions, output_csv_path):
    """
    Saves the MCQs to a CSV file with proper formatting.
    Ensures questions and options with commas are properly quoted.
    """
    formatted_questions = []

    for q in questions:
        formatted_questions.append({
            "Question": q["question"],
            "Option 1": q["options"][0],
            "Option 2": q["options"][1],
            "Option 3": q["options"][2],
            "Option 4": q["options"][3],
            "Correct Answer": q["answer"]
        })

    # Convert the list of formatted questions into a DataFrame
    df = pd.DataFrame(formatted_questions)
    
    # Save to CSV with quoting enabled to handle commas inside fields
    df.to_csv(output_csv_path, index=False, quotechar='"', quoting=1)  # quoting=1 ensures non-numeric fields are quoted
    
    print(f"✅ Questions saved successfully to {output_csv_path}")
