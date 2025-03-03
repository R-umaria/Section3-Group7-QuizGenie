import unittest
import os
from src.csv_writer import save_questions_to_csv

class TestCSVWriter(unittest.TestCase):
    def test_save_csv(self):
        questions = [
            {"question": "What is 2+2?", "options": ["3", "4", "5", "6"], "answer": "4"}
        ]
        output_path = "output/test_mcqs.csv"
        save_questions_to_csv(questions, output_path)
        self.assertTrue(os.path.exists(output_path), "CSV file should be created")

if __name__ == "__main__":
    unittest.main()
