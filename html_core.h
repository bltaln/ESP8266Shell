// www.linecode.ro
// html_core.h
#ifndef HTML_CORE_H
#define HTML_CORE_H

String getHTML() {
  return R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <title>LineCode Shell</title>
      <style>
        body {
          font-family: monospace;
          background-color: #000;
          color: #0f0;
          margin: 0;
          display: flex;
          justify-content: center;
          align-items: center;
          height: 100vh;
          overflow: hidden;
        }
        .terminal-container {
          width: 80%;
          max-width: 800px;
          height: 80%;
          max-height: 600px;
          background-color: #003366;
          color: #0f0;
          padding: 20px;
          border: 2px solid #404040;
          overflow-y: auto;
        }
        .input-line {
          display: flex;
          align-items: center;
          margin-top: 10px;
        }
        .input-line span {
          color: #0f0;
          margin-right: 5px;
          display: inline-block; 
          animation: rotateSymbol 2s linear infinite; 
        }
        .input-line input {
          background: transparent;
          border: none;
          color: #0f0;
          outline: none;
          flex: 1;
        }

        /* Animația de rotație */
        @keyframes rotateSymbol {
          0% {
            transform: rotate(0deg); 
          }
          100% {
            transform: rotate(360deg); 
          }
        }
      </style>
      <script>
        function setupTerminal() {
          const terminal = document.getElementById('terminal');
          const input = document.getElementById('input');
          const prompt = document.getElementById('prompt');
          
          input.focus();

          // Afișăm mesajul de bun venit și comenzile disponibile
          const welcomeMessage = [
            "LineCode Shell - www.linecode.ro -",
            "Coded : B. Alin Gabriel ",
            "MIT License",
            "________________________________________",
            "Type 'help' to see the list of available commands.",
            ""
          ];
          welcomeMessage.forEach(msg => appendOutput(msg));

          function appendOutput(text) {
            const line = document.createElement('div');
            line.textContent = text;
            terminal.insertBefore(line, prompt);
            terminal.scrollTop = terminal.scrollHeight;
          }

          input.addEventListener('keydown', function(event) {
            if (event.key === 'Enter') {
              const command = input.value.trim();
              appendOutput('$ ' + command);
              input.value = '';
              
              fetch(`/cmd?command=${encodeURIComponent(command)}`)
                .then(response => response.text())
                .then(data => appendOutput(data))
                .catch(err => appendOutput('Error: ' + err.message));
            }
          });

          terminal.addEventListener('click', function() {
            input.focus();
          });
        }

        window.onload = setupTerminal;
      </script>
    </head>
    <body>
      <div class="terminal-container">
        <div id="terminal">
          <div id="prompt" class="input-line">
            <span># </span><input id="input" type="text">
          </div>
        </div>
      </div>
    </body>
    </html>
  )rawliteral";
}

#endif
