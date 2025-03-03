import pandas as pd

def save_questions_to_csv(questions, output_csv_path):
    """
    Saves the MCQs to a CSV file with proper formatting.
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

    df = pd.DataFrame(formatted_questions)
    df.to_csv(output_csv_path, index=False)
    print(f"✅ Questions saved successfully to {output_csv_path}")
