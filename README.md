<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
  <title>OOP in C++</title>
  <link href="https://fonts.googleapis.com/css2?family=JetBrains+Mono:wght@400;700&family=Inter:wght@400;600&display=swap" rel="stylesheet"/>
  <style>
    *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }

    :root {
      --bg: #0d1117;
      --surface: #161b22;
      --border: #21262d;
      --accent: #58a6ff;
      --green: #3fb950;
      --text: #e6edf3;
      --muted: #8b949e;
      --mono: 'JetBrains Mono', monospace;
      --sans: 'Inter', sans-serif;
    }

    body {
      background: var(--bg);
      color: var(--text);
      font-family: var(--sans);
      min-height: 100vh;
      display: flex;
      justify-content: center;
      padding: 3rem 1rem;
    }

    .container { max-width: 720px; width: 100%; }

    .hero {
      border: 1px solid var(--border);
      border-radius: 12px;
      padding: 2rem;
      background: var(--surface);
      margin-bottom: 1.5rem;
    }

    .badge {
      display: inline-block;
      background: rgba(88,166,255,0.12);
      color: var(--accent);
      font-family: var(--mono);
      font-size: 0.72rem;
      padding: 3px 10px;
      border-radius: 20px;
      border: 1px solid rgba(88,166,255,0.25);
      margin-bottom: 1rem;
    }

    h1 {
      font-family: var(--mono);
      font-size: 1.8rem;
      font-weight: 700;
      letter-spacing: -0.5px;
      color: var(--text);
    }

    h1 span { color: var(--accent); }

    .subtitle {
      color: var(--muted);
      font-size: 0.9rem;
      margin-top: 0.5rem;
      line-height: 1.6;
    }

    .section { margin-bottom: 1.5rem; }

    .section-label {
      font-family: var(--mono);
      font-size: 0.7rem;
      color: var(--muted);
      text-transform: uppercase;
      letter-spacing: 1.5px;
      margin-bottom: 0.75rem;
    }

    .tags { display: flex; flex-wrap: wrap; gap: 0.5rem; }

    .tag {
      background: var(--surface);
      border: 1px solid var(--border);
      border-radius: 6px;
      padding: 5px 12px;
      font-family: var(--mono);
      font-size: 0.78rem;
      color: var(--green);
    }

    .code-block {
      background: var(--surface);
      border: 1px solid var(--border);
      border-radius: 10px;
      overflow: hidden;
      margin-bottom: 1.5rem;
    }

    .code-header {
      display: flex;
      align-items: center;
      gap: 6px;
      padding: 0.6rem 1rem;
      border-bottom: 1px solid var(--border);
    }

    .dot { width: 10px; height: 10px; border-radius: 50%; }
    .dot.r { background: #ff5f56; }
    .dot.y { background: #ffbd2e; }
    .dot.g { background: #27c93f; }

    .code-label {
      margin-left: auto;
      font-family: var(--mono);
      font-size: 0.7rem;
      color: var(--muted);
    }

    pre {
      padding: 1.25rem;
      font-family: var(--mono);
      font-size: 0.8rem;
      line-height: 1.7;
      color: var(--text);
      overflow-x: auto;
    }

    .kw  { color: #ff7b72; }
    .typ { color: #79c0ff; }
    .str { color: #a5d6ff; }
    .cmt { color: #8b949e; font-style: italic; }
    .fn  { color: #d2a8ff; }

    .run-box {
      background: var(--surface);
      border: 1px solid var(--border);
      border-radius: 10px;
      padding: 1rem 1.25rem;
      margin-bottom: 1.5rem;
      display: flex;
      align-items: center;
      gap: 0.75rem;
    }

    .prompt { color: var(--green); font-family: var(--mono); font-size: 0.85rem; }
    .cmd    { color: var(--accent); font-family: var(--mono); font-size: 0.85rem; }

    footer {
      text-align: center;
      font-size: 0.78rem;
      color: var(--muted);
      padding-top: 1rem;
      border-top: 1px solid var(--border);
    }

    footer a { color: var(--accent); text-decoration: none; }
  </style>
</head>
<body>
<div class="container">

  <div class="hero">
    <div class="badge">C++ · OOP</div>
    <h1>Object-Oriented<br><span>Programming</span></h1>
    <p class="subtitle">Core OOP concepts in C++ — classes, inheritance, polymorphism, templates, and more. Built for learning and exam reference.</p>
  </div>

  <div class="section">
    <div class="section-label">Topics Covered</div>
    <div class="tags">
      <span class="tag">Classes & Objects</span>
      <span class="tag">Inheritance</span>
      <span class="tag">Polymorphism</span>
      <span class="tag">Templates</span>
      <span class="tag">Friend Functions</span>
      <span class="tag">Dynamic Memory</span>
      <span class="tag">Operator Overloading</span>
      <span class="tag">STL</span>
    </div>
  </div>

  <div class="code-block">
    <div class="code-header">
      <div class="dot r"></div><div class="dot y"></div><div class="dot g"></div>
      <span class="code-label">example.cpp</span>
   

  <div class="run-box">
    <span class="prompt">$</span>
    <span class="cmd">g++ -std=c++17 -o out main.cpp && ./out</span>
  </div>

  <footer>
    Open source · MIT License · Made with  by <a href="#">Saba</a>
  </footer>

</div>
</body>
</html>
