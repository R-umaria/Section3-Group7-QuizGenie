import pdfplumber

def extract_text_from_pdf(pdf_path, max_chars=3000):
    """
    Extracts text from a given PDF file and limits to max_chars to prevent API overload.
    """
    text = ""
    with pdfplumber.open(pdf_path) as pdf:
        for page in pdf.pages:
            page_text = page.extract_text()
            if page_text:
                text += page_text + "\n"
            if len(text) >= max_chars:
                break  # Stop if max characters are reached
    return text.strip()
