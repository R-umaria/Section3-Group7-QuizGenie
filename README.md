# 🧞‍♂️ QuizGenie

**QuizGenie** is an AI-powered desktop application that helps students generate personalized quizzes directly from their course materials. Upload your class notes or PDFs, and QuizGenie will magically transform them into a set of multiple-choice questions using generative AI. Study smarter and test yourself faster!

---

## 🚀 Features

- 📤 Upload any PDF containing lecture notes or study material  
- 🤖 AI generates 10 MCQs using Gemini AI (1 correct + 3 wrong options)  
- 📊 Score calculation with instant feedback  
- 🖼️ Fun response system — Happy or Sad Genie images based on your score  
- 🖥️ Clean, interactive GUI built with Qt  
- 🧪 Unit tested client-server system with PDF parsing & JSON handling  

---

## 📁 How It Works

1. **Upload PDF** from the client app  
2. Client sends the file to the server  
3. Server processes the file using Python:  
   - Extracts text using PDF parsing  
   - Sends it to Gemini AI to generate quiz content  
4. AI responds with a JSON → converted to CSV  
5. CSV sent back to client and displayed in quiz UI  
6. User completes quiz → client calculates score  
7. Score sent to server → Genie image (happy/sad) is sent back for visual feedback  

---

## 🎥 Demo Video

Watch a quick demo of QuizGenie in action on YouTube:  
👉 [QuizGenie Demo](https://www.youtube.com/watch?v=D8euRwwoUuw)

---

## 📸 Screenshots

<p align="center">
  <img src="assets/Login_Screen.png" alt="Login Screen" width="45%"/>
  <img src="assets/Home_Screen.png" alt="Home Screen" width="45%"/>
</p>

<p align="center">
  <img src="assets/Quiz_Screen.png" alt="Quiz Screen" width="45%"/>
  <img src="assets/Result.png" alt="Result Screen" width="45%"/>
</p>

---

## 🧑‍💻 Tech Stack

- **C++** (Client-Server Architecture)  
- **Qt 6** for GUI development  
- **Python** for AI integration and PDF parsing  
- **Google Gemini API** for question generation  
- **MSTest / Qt Test** for Unit Testing  

---

## 🧪 Testing

- Unit tests are implemented for:  
  - Client-server packet handling  
  - File transmission  
  - AI integration and CSV generation  
- Detailed test logs and coverage report included  

---

## 👥 Team Members

- **Rishi Umaria** – Frontend, AI dev, integration, server testing, Git management  
- **Tyler Phillips** – Connection handling, Usability Testing, Unit Testing  

---

## 📜 License

MIT License

---

## 🙌 Acknowledgments

- Google for Gemini API access  
- Qt for providing an awesome GUI framework (but painful 😅)  
- Our amazing professors & the Project IV course team  

---
