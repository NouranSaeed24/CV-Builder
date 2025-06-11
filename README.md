# CV-Builder
# 📌 Overview
  A GTK-based application for creating professional resumes with HTML/CSS output.

# ✨ Features
  Multi-section form (Personal Info, Education, Experience, Skills, Languages)

  Clean HTML/CSS resume generation

  Add/Delete functionality for entries

  Windows/Linux compatible

# 🛠️ Technologies
  C + GTK3 (GUI)

  HTML/CSS (Output)
 
  Glade (Interface Designer)

# 📦 Project Structure
cv-builder/
├── src/               # Source code
│   ├── cv.c          # Main application
│   └── design.glade  # GUI layout
├── output/           # Generated resumes
└── README.md         # Documentation

# ⚙️ Installation
  # Linux
  gcc cv.c -o cv_builder `pkg-config --cflags --libs gtk+-3.0`

  # Windows
  Pre-compiled .exe available in Releases

# 🚀 Usage
  Fill all sections

  Click "Generate CV"

  Find resume as index.html + style.css
