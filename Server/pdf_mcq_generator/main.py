import os
import sys
from src.pdf_extractor import extract_text_from_pdf
from src.mcq_generator import generate_mcq_questions
from src.csv_writer import save_questions_to_csv

def process_pdf_and_generate_mcqs(pdf_path, output_folder):
    """
    Main function to extract text from PDF, generate MCQs, and save them as CSV.
    
    Parameters:
    pdf_path (str): The path to the PDF file.
    output_folder (str): The folder where the output CSV file will be saved.
    """
    # Check if the PDF file exists
    if not os.path.exists(pdf_path):
        print("❌ Error: PDF file not found.")
        return

    # Extract text from the PDF
    print("🔍 Extracting text from PDF...")
    text = extract_text_from_pdf(pdf_path)

    # Check if any text was extracted
    if not text:
        print("❌ Error: No text extracted from PDF.")
        return

    # Generate MCQ questions from the extracted text
    print("🤖 Generating MCQs using Gemini API...")
    questions = generate_mcq_questions(text)

    # Save the generated questions to a CSV file
    if questions:
        os.makedirs(output_folder, exist_ok=True)
        output_csv_path = os.path.join(output_folder, "mcq_output.csv")
        print("📁 Saving questions to CSV...")
        save_questions_to_csv(questions, output_csv_path)
    else:
        print("❌ No questions generated.")

if __name__ == "__main__":
    # Debug print to show received arguments
    print(f"Arguments received: {sys.argv}")
    
    # Check if the correct number of arguments are provided
    if len(sys.argv) != 3:
        print("Usage: python main.py <pdf_path> <output_folder>")
    else:
        pdf_path = sys.argv[1]
        output_folder = sys.argv[2]
        process_pdf_and_generate_mcqs(pdf_path, output_folder)
