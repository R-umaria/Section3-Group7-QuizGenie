import unittest
from src.mcq_generator import generate_mcq_questions

class TestMCQGenerator(unittest.TestCase):
    def test_generate_mcq(self):
        sample_text = "Paris is the capital of France."
        questions = generate_mcq_questions(sample_text)
        self.assertEqual(len(questions), 10, "Should generate 10 MCQs")

if __name__ == "__main__":
    unittest.main()
