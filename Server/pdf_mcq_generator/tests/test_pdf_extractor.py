import unittest
import sys
import os

# Add the parent directory of 'src' to the Python path
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))

from src.pdf_extractor import extract_text_from_pdf

class TestPDFExtractor(unittest.TestCase):
    def test_extract_text(self):
        text = extract_text_from_pdf("sample.pdf")
        self.assertTrue(len(text) > 0, "Extracted text should not be empty")

if __name__ == "__main__":
    unittest.main()
